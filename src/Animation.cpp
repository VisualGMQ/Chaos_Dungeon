#include "Animation.hpp"

Frame::Frame():delaytime(0){}

Frame::Frame(Texture tex, int delay):texture(tex),delaytime(delay){}

Frame::Frame(string filename, int delay):delaytime(delay){
    texture.Load(filename);
}

IAnimation::IAnimation():cur_frame(0),isplaying(false),count(0),isloop(false){}

void IAnimation::EnableLoop(){
    isloop = true;
}

void IAnimation::DisableLoop(){
    isloop = false;
}

bool IAnimation::IsLoop() const{
    return isloop;
}

void IAnimation::Play(){
    isplaying = true;
}

void IAnimation::Stop(){
    isplaying = false;
    count = 0;
    cur_frame = 0;
}

void IAnimation::Pause(){
    isplaying = false;
}

int IAnimation::GetDelayTime(int idx) const{
    return delaytime.at(idx);
}

Animation::Animation(vector<Frame> frame){
    frames = frame;
}

Animation::Animation(initializer_list<Frame> frames){
    for(auto it=frames.begin();it!=frames.end();it++)
        AddFrame(*it);
}

void Animation::AddFrame(string filename, int delay){
    AddFrame(std::move(Frame(filename.c_str(), delay)));
}

void Animation::AddFrame(Texture texture, int delay){
    AddFrame(std::move(Frame(texture, delay)));
}

void Animation::AddFrame(Frame f){
    frames.push_back(f);
}

size_t Animation::Size() const{
    return frames.size();
}

Frame& Animation::GetCurrentFrame(){
    return frames.at(cur_frame);
}

Texture& Animation::GetCurrentTexture(){
    return GetCurrentFrame().texture;
}

Frame& Animation::operator[](int idx){
    return frames.at(idx);
}

bool Animation::Valid() const{
    return !frames.empty();
}

void Animation::Update(){
    if(isplaying){
        count++;
        if(count>GetCurrentFrame().delaytime){
            cur_frame++;
            if(cur_frame>=frames.size()){
                if(IsLoop()){
                    Stop();
                    Play();
                }else{
                    Pause();
                    cur_frame--;
                }
            }else{
                count = 0;
            }
        }
    }
}

void Animation::Draw(int x, int y, int w, int h, float degree, FlipFlag flipflag) {
    GetCurrentFrame().texture.Draw(x, y, w, h, degree, flipflag);
}

AnimationS::AnimationS(string filename, int c, int r, vector<int> delay){
    Set(filename, c, r, delay);
}

AnimationS::AnimationS(TextureSheet texsheet, vector<int> delay){
    this->texsheet = texsheet;
    delaytime = delay;
}

void AnimationS::Set(string filename, int c, int r, vector<int> delay){
    texsheet.Load(filename, c, r);
    delaytime = delay;
}

void AnimationS::SetSheet(TextureSheet ts){
    texsheet = ts;
}

void AnimationS::SetDelayTimes(vector<int> delay){
    delaytime = delay;
}

size_t AnimationS::Size() const{
    return texsheet.Col();
}

bool AnimationS::Valid() const{
    return texsheet.Valid();
}

void AnimationS::Update(){
    if(isplaying){
        count++;
        if(count>delaytime[cur_frame]){
            cur_frame++;
            if(cur_frame>=texsheet.Col()){
                if(IsLoop()){
                    Stop();
                    Play();
                }else{
                    Pause();
                    cur_frame--;
                }
            }else{
                count = 0;
            }
        }
    }
}

SDL_Rect AnimationS::GetCurrentRect() const{
    return texsheet.Get(cur_frame, 0);
}

TextureSheet& AnimationS::GetSheet(){
    return texsheet;
}

void AnimationS::Draw(int x, int y, int w, int h, float degree, FlipFlag flipflag) {
    SDL_DrawTextureFromSheet(texsheet, cur_frame, 0, x, y, w, h, degree, flipflag);
}

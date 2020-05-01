#include "Animation.hpp"

Frame::Frame():delaytime(0){}

Frame::Frame(Texture texture, int delay){
    this->texture = texture;
    delaytime = delay;
}

Animation::Animation():state(AniPlayState::STOPING),isloop(false),cur_frame(0),time_count(0){}

Animation::Animation(vector<Frame> frame_list):Animation(){
    Load(frame_list);
}

void Animation::Load(vector<Frame> frame_list){
    this->frames = frame_list;  
}

Animation::Animation(initializer_list<Frame> frame_list):Animation(){
    for(auto it=frame_list.begin();it!=frame_list.end();it++)
        frames.push_back(*it);
}

Animation::Animation(TextureSheet& sheet, vector<int> delay, int begin, int end):Animation(){
    Load(sheet, delay, begin, end);
}

void Animation::Replay(){
    Stop();
    BackToFirstFrame();
    Play();
}

void Animation::Load(TextureSheet& sheet, vector<int> delay, int begin, int end){
    if(end==-1)
        end = sheet.Size();
    int j = 0;
    for(int i=0;i<end;i++,j++)
        frames.push_back(Frame(sheet.Get(i, 0), delay[j]));
}

bool Animation::Valid() const{
    return !frames.empty();
}

void Animation::BackToFirstFrame(){
    cur_frame = 0;
}

size_t Animation::Size() const{
    return frames.size();
}

int Animation::CurrentIdx() const{
    return cur_frame;
}

void Animation::Play(){
    state = AniPlayState::PLAYING;
}

void Animation::Stop(){
    state = AniPlayState::STOPING;
    time_count = 0;
}

void Animation::Pause(){
    state = AniPlayState::PAUSING;
}

AniPlayState Animation::State() const{
    return state;
}

void Animation::EnableLoop(){
    isloop = true;
}

void Animation::DisableLoop(){
    isloop = false;
}

void Animation::Scale(float sx, float sy){
    for(int i=0;i<frames.size();i++)
        frames[i].texture.Scale(sx, sy);
}

Frame& Animation::CurrentFrame(){
    return frames.at(cur_frame);
}

bool Animation::IsLooping() const{
    return isloop;
}

void Animation::Update(){
    if(Valid() && state==AniPlayState::PLAYING){
        time_count++;
        if(time_count>=frames[cur_frame].delaytime){
            time_count = 0;
            cur_frame++;
        }
        if(cur_frame>=frames.size()){
            cur_frame = frames.size()-1;
            if(isloop){
                Stop();
                BackToFirstFrame();
                Play();
            }else
                Stop();
        }
    }
}

void Animation::Draw(float x, float y, float degree, FlipFlag flag) {
    CurrentFrame().texture.Draw(x, y, degree, flag);
}

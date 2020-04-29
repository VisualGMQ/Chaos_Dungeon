#include "Sprite/ColliAnimation.hpp"

ColliRange::ColliRange():lower(0),upper(0),damage(0){}

bool ColliRange::Valid() const{
    return lower>upper || lower<0 || upper<0;
}

ColliAnimation::ColliAnimation(vector<Frame> frame_list):Animation(frame_list){
    prop = nullptr;
    changed_to_colli = false;
}

ColliAnimation::ColliAnimation(initializer_list<Frame> frame_list):Animation(frame_list){
    prop = nullptr;
    changed_to_colli = false;
}

ColliAnimation::ColliAnimation():prop(nullptr),changed_to_colli(false){}

ColliAnimation::ColliAnimation(TextureSheet& sheet, vector<int> delay, int begin, int end):Animation(sheet, delay, begin, end){}

void ColliAnimation::SetColliRange(int lower, int upper, int damage){
    range.lower = lower;
    range.upper = upper;
    range.damage = damage;
}

bool ColliAnimation::Valid() const{
    return Animation::Valid() && prop;
}

void ColliAnimation::BindProp(BasicProp* p){
    if(p==nullptr)
        cerr<<"warning: BasicProp is nullptr in BindProp()"<<endl;
    prop = p;
}

void ColliAnimation::Pause() {
    Animation::Pause();
    changed_to_colli = false;
}

void ColliAnimation::Stop() {
    Animation::Stop();
    changed_to_colli = false;
}


void ColliAnimation::Update(){
    Animation::Update();
    if(State()==AniPlayState::PLAYING){
        if(CurrentIdx()>=range.lower && CurrentIdx()<=range.upper){
            if(!changed_to_colli){
                prop->damage = range.damage;
                prop->can_damage = true;
                changed_to_colli = true;
            }
        }else{
            prop->can_damage = false;
        }
    }
}

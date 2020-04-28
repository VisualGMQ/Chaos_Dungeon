#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "TextureSheet.hpp"
#include <initializer_list>
using namespace std;

struct Frame{
    Frame();
    Frame(Texture texture, int delay);
    Texture texture;
    int delaytime; /** 以帧计 */
};

enum class AniPlayState{
    PLAYING,
    PAUSING,
    STOPING
};

class Animation : public Drawable{
public:
    Animation();
    Animation(vector<Frame> frame_list);
    Animation(initializer_list<Frame> frame_list);
    /**
     * @brief 通过图像表构建动画。
     * @warn 图像表必须是一行的
     * @param begin 从图像的哪一列开始,默认从第一列开始
     * @param end 到图像的那一列结束，默认最后结束
     * @param delay 单个图像延时时间，以帧计
     */
    Animation(TextureSheet& sheet, vector<int> delay, int begin = 0, int end = -1);
    void Load(vector<Frame> frame_list);
    void Load(TextureSheet& sheet, vector<int> delay, int begin = 0, int end = -1);
    bool Valid() const;
    size_t Size() const;
    int CurrentIdx() const;
    bool IsPlaying() const;
    void Play();
    void Stop();
    void Pause();
    void Scale(float sx, float sy);
    AniPlayState State() const; 
    bool IsLooping() const;
    void EnableLoop();
    void DisableLoop();
    Frame& CurrentFrame();
    void Update();
    void Draw(float x, float y, float degree = 0, FlipFlag flag = FlipFlag::NONE) override;
    ~Animation() = default;
private:
    vector<Frame> frames;
    AniPlayState state;
    bool isloop;
    int cur_frame;
    int time_count;
};

#endif

#ifndef DOOR_SWITCH_HPP
#define DOOR_SWITCH_HPP

#include "engine.hpp"
#include "animation.hpp"
#include "game_object.hpp"
#include "audio.hpp"
#include "progress_bar.hpp"

using namespace engine;

class DoorSwitch: public GameObject{
public:
    DoorSwitch(std::string objectName, double positionX, double positionY, int width, int height);
    ~DoorSwitch();
    void update(double timeElapsed);
    void draw();
    void init();
    Animation * getAnimation();
    void animate();
    void Stop_Animation();
    bool Is_Pressed();
    void Play_Effect();
    void Stop_Effect();
    double Get_Hacking_Bar_Percent();
    void Reset_Hacking_Progress();
protected:
    bool Pressed;
    Animation* Animator;
private:
    Audio *Hacking_Effect;
    Progress_Bar *Hacking_Bar;
};

#endif

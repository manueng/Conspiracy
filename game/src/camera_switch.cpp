#include "camera_switch.hpp"

using namespace engine;

#define file_name "assets/sprites/cenary/switch_cameras(14X16).png"
#define width 14
#define heigh 16
#define adjust_x 10
CameraSwitch::CameraSwitch(double position_x, double position_y, std::string direction) : GameObject(file_name,position_x -adjust_x,position_y - ADJUSTX,
                                                                     width+adjust_x*2, heigh+adjust_x*2){
    animator = new Animation(FILENAME, 1, 2, 0.1);
    switchEfffect = new Audio("assets/sounds/TURNOFFCAMERA.wav", "EFFECT", 128);

    animator->addAction("on", 0,0);
    animator->addAction("off",1,1);
    animator->setInterval("on");
    direction = direction;
    working = true;
}

void CameraSwitch::draw(){
    animator->draw_instant(getPositionX()+ADJUSTX, getPositionY()+ADJUSTX);
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void CameraSwitch::update(double time_elapsed){
    time_elapsed = time_elapsed;
    animator->update();
}

bool CameraSwitch::isWorking(){
    return working;
}

void CameraSwitch::turnOff(){
    if(animator->getInterval().first!="off"){
        working = false;
        animator->setInterval("off");
        switchEfffect->play(0);
    }
}

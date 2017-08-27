#include "camera_switch.hpp"

using namespace engine;

#define FILENAME "assets/sprites/cenary/switch_cameras(14X16).png"
#define width 14
#define heigh 16
#define adjust_x 10
CameraSwitch::CameraSwitch(double positionX, double positionY, std::string direction) : GameObject(fileName,positionX - adjustX,positionY - adjustX,
                                                                     width+adjustX*2, heigh+adjustX*2){
    animator = new Animation(file_name, 1, 2, 0.1);
    switchEfffect = new Audio("assets/sounds/TURNOFFCAMERA.wav", "EFFECT", 128);

    animator->addAction("on", 0,0);
    animator->addAction("off",1,1);
    animator->setInterval("on");
    direction = direction;
    working = true;
}

void CameraSwitch::draw(){
    animator->draw_instant(getPositionX()+adjust_x, getPositionY()+adjust_x);
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void CameraSwitch::update(double timeElapsed){
    timeElapsed = timeElapsed;
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

#include "door_switch.hpp"

Door_Switch::Door_Switch(std::string objectName, double positionX, double positionY,
                                     int width, int height) : GameObject(objectName,
                                                                         positionX,
                                                                         positionY,
                                                                         width, height){
    animator = new Animation(objectName, 1, 6, 0.5);

    hacking_effect = new Audio("assets/sounds/PCNOISE.wav", "EFFECT", 60);
    hacking_bar = new ProgressBar(positionX-7, positionY-10, 45, 5, 0.002);

    animator->addAction("beingHacked", 1,5);
    animator->addAction("idle", 0, 0);
    pressed = false;
}

Door_Switch::Door_Switch(){}

void Door_Switch::update(double timeElapsed){
    timeElapsed = timeElapsed;
    animator->update();
    if(isPressed()){
        hacking_bar->update(timeElapsed);
    }
}

void Door_Switch::draw(){
    INFO("DoorSwitch DRAW");
    if(isPressed()){
        animator->setInterval("beingHacked");
        AnimationManager::instance.addProgressBar(hacking_bar);
        if(hacking_bar->getPercent() <= 0.0){
            pressed = false;
            setEnabled(false);
        }
    }else{
        animator->setInterval("idle");
    }
    animator->draw(getPositionX(), getPositionY());
}

Animation * DoorSwitch::getAnimation(){
  return animator;
}

void DoorSwitch::animate(){
    pressed = true;
}

void Door_Switch::stopAnimation(){
    pressed = false;
}

bool Door_Switch::isPressed(){
    return pressed;
}

void Door_Switch::Play_Effect(){
    hacking_effect->play(2);
}

void Door_Switch::Stop_Effect(){
    hacking_effect->stop();
}

double Door_Switch::Get_Hacking_Bar_Percent(){
    return hacking_bar->getPercent();
}

void Door_Switch::Reset_Hacking_Progress(){
    hacking_bar->resetPercent();
}

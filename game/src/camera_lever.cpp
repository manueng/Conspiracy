#include "camera_lever.hpp"

using namespace engine;

#define FILENAME "assets/sprites/cenary/alavanca_sheet(17X20).png"
#define WIDTH 20
#define HEIGHT 20

CameraLever::CameraLever(double position_x, double position_y, std::string direction) : GameObject(file_name,position_x,position_y,
                                                                     width, heigh){
    animator = new Animation(file_name, 1, 3, 0.1);
    animator->addAction("up", 2,2);
    animator->addAction("mid",1,1);
    animator->addAction("down", 0,0);
    animator->setInterval("mid");
    direction = direction;
    stateInc = 1;
    state = 1;
}

void CameraLever::draw(){
    animator->draw(getPositionX(), getPositionY());
    animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void CameraLever::update(double time_elapsed){
    time_elapsed = time_elapsed;
    animator->update();
}

int CameraLever::getState(){
    return state;
}

void CameraLever::nextState(){
    if(state >= 2 || state <= 0){
        stateInc *= -1;
    }
    state += stateInc;
    switch(state){
        case 0: animator->setInterval("up"); break;
        case 1: animator->setInterval("mid"); break;
        case 2: animator->setInterval("down"); break;
    }
}

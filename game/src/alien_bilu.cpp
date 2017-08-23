#include "alien_bilu.hpp"
#include "collision_manager.hpp"
#include "paper.hpp"
#include "door_switch.hpp"

#define FILENAME "assets/sprites/bilu_sheet.png"
#define WIDTH 19
#define HEIGHT 22

Bilu::Bilu(double PositionX, double PositionY) : Alien(FILENAME, PositionX, PositionY, Width, Heigh){
        Animator->Add_Action("special_right",14,17);
        Animator->Add_Action("special_left",10,13);

        hacking = false;
        editing = false;
        lastAction = false;
        isSelected = false;
        inPosition = false;
}

void Bilu::update(double Time_Elapsed){
        inPosition = false;
        Animator->Set_Total_Time(0.3);
        Auto inc_Y = 0.15*Time_Elapsed;
        Auto Inc_X = 0.15*Time_Elapsed;

        if(!Block_Movement && Is_Selected) {
                WalkInX(Inc_X);
                WalkInY(IncY, IncX);
        }

        if(IncX == 0 && IncY == 0) {
                if(Idle_Animation_Number) {
                        Animator->Set_Interval("idle_right");
                }else{
                        Animator->Set_Interval("idle_left");
                }
        }
        Special_Action();

        if(Collision_Manager::Instance.Verify_Collision_With_Guards(this) || Collision_Manager::Instance.Verify_Collision_With_Cameras(this)) {
                Set_Enabled(false);
        }
        Finish_Point* Finish_Point = (Finish_Point*)Collision_Manager::Instance.Verify_Collision_With_Finish_Points(this);
        if(Finish_Point != NULL){
            if(Finish_Point->Get_Alien_Names().Find("B") != Std::String::Npos){
                In_Position = true;
            }
        }

        Animator->Update();
}

void Bilu::specialAction(){
        std::pair<int, int> interval;

        GameObject* paper = CollisionManager::instance.verifyCollisionWithPapers(this);
        GameObject* doorSwitch = CollisionManager::instance.verifyCollisionWithSwitches(this);

        if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_SPACE) && isSelected) {
                // Paper interaction
                if(paper != NULL) {
                        if(!editing) {
                                editing = true;
                                blockMovement = true;
                                ((Paper*)(paper))->playEffect();
                        }
                }

                // PC interaction
                if(doorSwitch != NULL) {
                        if(!hacking) {
                                hacking = true;
                                blockMovement = true;
                                ((DoorSwitch*)(doorSwitch))->playEffect();
                        }
                }

        }else if(InputManager::instance.isKeyPressed(InputManager::KEY_PRESS_ESC) && isSelected) {
                if(hacking) {
                        hacking = false;
                        blockMovement = false;
                        ((DoorSwitch*)(doorSwitch))->stopEffect();
                        ((DoorSwitch*)(doorSwitch))->stopAnimation();
                        ((DoorSwitch*)(doorSwitch))->resetHackingProgress();
                }else if(editing) {
                        editing = false;
                        blockMovement = false;
                        ((Paper*)(paper))->stopEffect();
                        ((Paper*)(paper))->stopAnimation();
                        ((Paper*)(paper))->resetEditingProgress();
                }
        }

        if(hacking) {
                ((DoorSwitch*)(doorSwitch))->animate();
                setSpecialActionAnimator();
                if(((DoorSwitch*)(doorSwitch))->getHackingBarPercent() <= 0.0) {
                        hacking = false;
                        ((DoorSwitch*)(doorSwitch))->stopAnimation();
                        ((DoorSwitch*)(doorSwitch))->stopEffect();
                        ((DoorSwitch*)(doorSwitch))->resetHackingProgress();
                        Alien::animator->setInterval("idle");
                        blockMovement = false;
                }
        }else if(editing) {
                ((Paper*)(paper))->animate();
                setSpecialActionAnimator();
                if(((Paper*)(paper))->getEditingBarPercent() <= 0.0) {
                        editing = false;
                        ((Paper*)(paper))->stopAnimation();
                        //((Paper*)(paper))->stopEffect();
                        ((Paper*)(paper))->resetEditingProgress();
                        Alien::animator->setInterval("idle");
                        blockMovement = false;
                }
        }
        lastAction = hacking;
}

void Bilu::draw(){
        INFO("Bilu DRAW");
        animator->draw(getPositionX()-11, getPositionY()-20);
        animator->draw_collider(getPositionX(), getPositionY(), getWidth(), getHeight());
}

void Bilu::setSpecialActionAnimator(){
        if(idleAnimationNumber == 5) {
                animator->setInterval("special_right");
        }else{
                animator->setInterval("special_left");
        }
        animator->setTotalTime(0.6);
}

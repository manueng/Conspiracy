#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "alien.hpp"
#include "alien_bilu.hpp"
#include "alien_etemer.hpp"
#include "alien_varginha.hpp"
#include "input_manager.hpp"
#include "engine.hpp"

using namespace engine;

class Player: public GameObject{
public:
    Player(std::pair<int, int> biluPosition, std::pair<int, int> etemerPosition,
          std::pair<int,int> varginhaPosition);
    ~Player();
    void update(double timeElapsed);
    void draw();
    bool isDead();

private:
    Alien *bilu, *varginha, *etemer;
    int selectedAlien;
    void idleAnimation(Alien * alien);
    void waitAnimation(int beforeAlien);
};
#endif
#ifndef ALIEN_BILU_HPP
#define ALIEN_BILU_HPP

#include "alien.hpp"

class Bilu: public Alien{
public:
    Bilu(double PositionX, double positionY);
    void Draw();
    void Update(double timeElapsed);

protected:
    void Special_Action();

private:
    bool Hacking;
    bool Editing;
    bool LastAction;
    void SetSpecialActionAnimator();
};

#endif

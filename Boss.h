
#ifndef BOSS_H
#define BOSS_H
#include "Window.h"

class Boss {
public:
    Boss();
    ~Boss();

    void move();

private:
    SDL_Rect rect;
    int health;
    int attackPower;
};

#endif

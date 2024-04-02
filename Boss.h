
#ifndef BOSS_H
#define BOSS_H
#include "Window.h"

class Boss {
public:
    Boss();
    ~Boss();

    SDL_Rect move();
    SDL_Rect HealthBar();

private:
    SDL_Rect rect;
    int health;
    int attackPower;
};

#endif


#ifndef BOSS_H
#define BOSS_H
#include "Window.h"

class Boss {
public:
    Boss();
    ~Boss();

    SDL_Rect GetBoss();
    void Move();
    SDL_Rect HealthBar();
    int Health();

private:
    SDL_Rect rect;
    int health;
    int attackPower;
};

#endif

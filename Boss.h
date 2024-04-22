
#ifndef BOSS_H
#define BOSS_H
#include "Window.h"

class Boss {
public:
    Boss();

    void Reset();
    SDL_Rect GetBoss();
    void Move();

private:
    SDL_Rect rect;
    int velocityX = 1,velocityY = 1;
};

#endif

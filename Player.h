#ifndef PLAYER_H
#define PLAYER_H
#include "SDL.h"
class Player {
public:
    Player();
    int GetX() const { return x; }
    int GetY() const { return y; }
    void Move(SDL_Event& event);
protected:
    int x;
    int y;
    int w;
    int h;
};

#endif // PLAYER_H

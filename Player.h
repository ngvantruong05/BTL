#ifndef PLAYER_H
#define PLAYER_H
#include "SDL.h"
class Player {
public:
    Player();
    ~Player();
    int GetX() const { return x; }
    int GetY() const { return y; }
    void SetX(int newX) { x = newX; }
    void SetY(int newY) { y = newY; }
    void SetPosition(int x, int y);
    void Move(SDL_Event& event);
protected:
    int x;
    int y;
    int w;
    int h;

    SDL_Rect rect_;
};

#endif // PLAYER_H

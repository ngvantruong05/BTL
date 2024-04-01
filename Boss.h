
#ifndef BOSS_H_
#define BOSS_H_TH
#include "CommonFunction.h"
#include "BaseObject.h"

#include <vector>

class Boss {
public:
    Boss();
    ~Boss();
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    void Boss::Move();
    const std::vector<SDL_Rect>& GetBullets() const;

private:
    int x;
    int y;
    int w;
    int h;
    SDL_Rect* Boss_;
};

#endif // MAIN_OBJECT_H_


#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_TH
#include "CommonFunction.h"
#include "BaseObject.h"
#include <vector>

class MainObject {
public:
    MainObject();
    ~MainObject();
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool Check(int x, int y, int w, int h);

    void MoveBullets();
    void MoveChickens();
    void Movelever();
    void MoveEggs();

    void AddBullet(int x, int y);
    void AddEggBelowChicken(const SDL_Rect& chickenRect);

    const std::vector<SDL_Rect>& GetBullets() const;
    const std::vector<SDL_Rect>& GetChickens() const;
    const std::vector<SDL_Rect>& GetEggs() const;

private:
    int x;
    int y;
    int w;
    int h;
    int number;
    int diem, demga, d;
    vector<SDL_Rect> bullets_;
    vector<SDL_Rect> chickens_;
    vector<SDL_Rect> eggs_;
};

#endif // MAIN_OBJECT_H_

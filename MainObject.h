
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
    void MoveBullets();
    void MoveChickens();
    void AddBullet(int x, int y);
    bool Check(int x, int y, int w, int h);
    const std::vector<SDL_Rect>& GetBullets() const;
    const std::vector<SDL_Rect>& GetChickens() const;

private:
    int x;
    int y;
    vector<SDL_Rect> bullets_;
    vector<SDL_Rect> chickens_;

};

#endif // MAIN_OBJECT_H_

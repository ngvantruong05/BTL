#ifndef FIGURE_H_
#define FIGURE_H_

#include "Window.h"
#include "Player.h"
#include <vector>

class Figure {
public:
    Figure();
    ~Figure();
    int GetDiem() const {return diem;}
    int SetDiem(int diem_){ diem = diem_; }
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool Check(int x, int y, int w, int h);
    int CheckBoss(SDL_Rect& bossRect);

    void MoveBullets();
    void MoveChickens();
    void Movelever();
    void MoveEggs();

    void AddBullet(int x, int y);
    void AddEgg(const SDL_Rect& chickenRect);

    const std::vector<SDL_Rect>& GetBullets() const;
    const std::vector<SDL_Rect>& GetChickens() const;
    const std::vector<SDL_Rect>& GetEggs() const;
    const std::vector<int>& Gethealth() const;

private:
    int x, y, w, h;
    int number, bulletdelay,numBullets;
    int diem, demga, d;
    std::vector <int> healths_;
    std::vector<SDL_Rect> bullets_;
    std::vector<SDL_Rect> chickens_;
    std::vector<SDL_Rect> eggs_;
};

#endif // FIGURE_H_

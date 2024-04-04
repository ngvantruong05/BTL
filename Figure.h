#ifndef FIGURE_H_
#define FIGURE_H_

#include "Window.h"
#include "Player.h"
#include <vector>

class Figure {
public:
    Figure();
    ~Figure();
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
    const std::vector<int>& Gethealth() const;

private:
    int x;
    int y;
    int w;
    int h;
    int number, bulletdelay;
    int diem, demga, d;
    std::vector <int> healths_;
    std::vector<SDL_Rect> bullets_;
    std::vector<SDL_Rect> chickens_;
    std::vector<SDL_Rect> eggs_;
};

#endif // FIGURE_H_

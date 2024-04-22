#ifndef FIGURE_H_
#define FIGURE_H_

#include "Window.h"
#include "Player.h"
#include <vector>

class Figure {
public:
    Figure();
    int GetScore() const {return score;}
    int GetTime() const {return Time;}
    int GetNumBullets() const {return numBullets;}
    void SetScore(int score_){ score = score_; }
    void SetLevel(int level_){ level = level_; }
    void SetTime(int Time_){ Time = Time_; }
    void SetNumBullets(int numBullets_){ numBullets = numBullets_; }

    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    bool AppearChicken();
    int Check(int x, int y, int w, int h);
    bool CheckChickens()    {return(chickens_.size()==0);}
    int CheckBoss(SDL_Rect& bossRect);
    void CheckFigure();

    void MoveBullets();
    void MoveChickens1();
    void MoveChickens2();
    void MoveEggs();
    void MoveItems();

    void AddBullet(int x, int y);
    void AddEgg(const SDL_Rect& chickenRect);
    void AddItem(const std::string& itemType, int x, int y, int h);

    const std::vector<SDL_Rect>& GetBullets() const;
    const std::vector<SDL_Rect>& GetChickens() const;
    const std::vector<SDL_Rect>& GetEggs() const;
    const std::vector<int>& Gethealth() const;
    void rendItem();

    void Clear();

private:
    int x, y, w, h;
    int bulletDelay,numBullets;
    int score, Time, level;
    std::vector <int> healths_;
    std::vector<SDL_Rect> bullets_;
    std::vector<SDL_Rect> chickens_;
    std::vector<SDL_Rect> eggs_;
    std::vector<std::pair<std::string, SDL_Rect>> items_;
};

#endif // FIGURE_H_

#include <vector>
#include "Figure.h"
#include "Window.h"
#define fi first
#define se second
using namespace std;
Figure::Figure() {
    score = 0;
    demga = -20;
    number = 700;
    bulletDelay = 0;
    numBullets = 1;
    d = 5;
    srand(time(NULL));
}

Figure::~Figure() {}

void Figure::MoveBullets() {
    if (bulletDelay > 0) {
        bulletDelay--;
    }
    for (int i = 0; i < bullets_.size(); ++i) {
        bullets_[i].y -= SPEED/10;
        if (bullets_[i].y + BULLET_HEIGHT < 0) {
            bullets_.erase(bullets_.begin() + i);
        }
    }
}
void Figure::MoveItems() {
    for (int i = 0; i < items_.size(); ++i) {
        items_[i].se.y += SPEED / 20;
        if (items_[i].se.y > SCREEN_HEIGHT) {
            items_.erase(items_.begin() + i);
        }
    }
}

void Figure::MoveChickens2() {
    if (demga % 50 == 0){
       x = 0;
       y = 0;
       SDL_Rect chicken = {0,0,0,0};
       chickens_.push_back(chicken);
       healths_.push_back(MAX_HEALTH);
    }
    for (int i = 0; i < chickens_.size(); i++){
        if (chickens_[i].w == 0)
            chickens_[i].x += SPEED/20;
        else
            chickens_[i].x -= SPEED/20;
        if (chickens_[i].x >= SCREEN_WIDTH){
            if (chickens_[i].y > 300)
                continue;
            chickens_[i].y += 120;
            chickens_[i].w = 1;
        }else   if (chickens_[i].x <= -50){
            if (chickens_[i].y > 300)
                continue;
            chickens_[i].y += 120;
            chickens_[i].w = 0;
        }
    }
    if (demga <= 600)
        demga ++;
}

void Figure::MoveChickens1() {
//    if (score >= d){
//        if (chickens_.size()!=0&&number != 700)
//            for (int i = 0; i < chickens_.size(); i++){
//                chickens_[i].y += SPEED/40;
//            }
//        else{
//            Figure::Movelever();
//            if (chickens_.size()==0&&demga >600)
//                d = 100000;
//            number = 700;
//        }
//    }
//    else{
    if (rand() % number < 5) {
        int x = rand() % (SCREEN_WIDTH - CHICKEN_WIDTH);
        int y = - 100;
        SDL_Rect chickenRect = {x, y, CHICKEN_WIDTH, CHICKEN_HEIGHT};
        bool collided = false;
        for (const auto& existingChicken : chickens_) {
            if (CheckCollision(chickenRect, existingChicken)) {
                collided = true;
                break;
            }
        }
        if (!collided) {
            chickens_.push_back(chickenRect);
            healths_.push_back(MAX_HEALTH);
        }
        if (number > 100)
            number -= 1;
    }
    for (int i = 0; i < chickens_.size();i++)
        chickens_[i].y += SPEED/40;
}
void Figure::CheckFigure(){
    for (int i = 0; i < chickens_.size(); i++){
        SDL_Rect chicken = {chickens_[i].x,chickens_[i].y,CHICKEN_WIDTH,CHICKEN_HEIGHT};
        for (int j = 0; j < bullets_.size(); j++) {
            if (CheckCollision(chicken, bullets_[j])) {
                healths_[i] -= 1;
                bullets_.erase(bullets_.begin() + j);
                if (healths_[i] == 0){
                    if (rand() % 100 < 100){
                        int t = rand() % 3 + 1;
                        string s;
                        if ( t == 1)
                            s = "BLOOD";
                        else    if (t == 2)
                            s = "AMMO";
                        else    if (t == 3)
                            s = "SHIELD";
                        AddItem(s, chickens_[i].x, chickens_[i].y,t);
                    }
                    chickens_.erase(chickens_.begin() + i);
                    healths_.erase(healths_.begin() + i);
                    score ++;
                }
            }
        }
        if (rand() % 5000 < chickens_.size()) {
            Figure::AddEgg({chickens_[i].x + (CHICKEN_WIDTH - EGG_WIDTH) / 2,chickens_[i].y + CHICKEN_HEIGHT,chickens_[i].w,chickens_[i].h});
        }
        if (chickens_[i].y > SCREEN_HEIGHT) {
            chickens_.erase(chickens_.begin() + i);
            healths_.erase(healths_.begin() + i);
        }
    }
}

void Figure::MoveEggs() {
    for (int i = 0; i < eggs_.size(); ++i) {
        eggs_[i].y += SPEED/20;
        if (eggs_[i].y > SCREEN_HEIGHT) {
            eggs_.erase(eggs_.begin() + i);
        }
    }
}

bool Figure::AppearChicken(){
    if (chickens_.size()!=0){
        for (int i = 0; i < chickens_.size(); i++)
            chickens_[i].y += SPEED/40;
        return false;
    }
    if (eggs_.size()!=0){
        for (int i = 0; i < eggs_.size(); i++)
            eggs_[i].y += SPEED/20;
        return false;
    }
    if (eggs_.size()!=0){
        for (int i = 0; i < bullets_.size(); ++i)
            bullets_[i].y -= SPEED/10;
        return false;
    }
    if (items_.size()!=0){
        for (int i = 0; i < items_.size(); i++)
            items_[i].se.y += SPEED/20;
        return false;
    }
    return true;
}
int Figure::Check(int x, int y,int w, int h)
{
    Window::RenderText(to_string(score), 0, 1);
    SDL_Rect planeR = {x,y,w,h};
    for (int i = 0; i < chickens_.size(); i++) {
        if (CheckCollision(chickens_[i], planeR)) {
            chickens_.erase(chickens_.begin() + i);
            healths_.erase(healths_.begin() + i);
            return 1;
        }
    }
    for (int i = 0; i < eggs_.size(); ++i) {
        if (CheckCollision(eggs_[i], planeR)) {
            eggs_.erase(eggs_.begin() + i);
            return 1;
        }
    }
    for (int i = 0; i < items_.size(); i++){
        SDL_Rect itemRect = {items_[i].se.x, items_[i].se.y, 80, 15};
        if (CheckCollision(itemRect, planeR)){
            if (items_[i].fi == "BLOOD"){
                items_.erase(items_.begin() + i);
                return 2;
            }else   if (items_[i].fi == "AMMO"){
                numBullets ++;
                items_.erase(items_.begin() + i);
            }else{
                items_.erase(items_.begin() + i);
                return 3;
            }
        }
    }
    return 0;
}
int Figure::CheckBoss(SDL_Rect& bossRect){
    int sum = 0;
    for (int i = 0; i < bullets_.size(); i++) {
        if (CheckCollision(bossRect, bullets_[i])) {
            sum ++;
            bullets_.erase(bullets_.begin() + i);
        }
    }
    return sum;
}

bool Figure::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
    bool xOverlap = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yOverlap = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return xOverlap && yOverlap;
}

void Figure::AddBullet(int x,int y) {
    if (bulletDelay == 0)
    {
        int bulletOffset = 50 / (numBullets+1);
        if (numBullets == 1){
            SDL_Rect bullet = {x + bulletOffset - BULLET_WIDTH / 2, y - 10, BULLET_WIDTH, BULLET_HEIGHT};
            bullets_.push_back(bullet);
        }
        else
            for (int i = 1; i <= numBullets; ++i) {
                SDL_Rect bullet = {x + i * bulletOffset - BULLET_WIDTH / 2, y - 10, BULLET_WIDTH, BULLET_HEIGHT};
                bullets_.push_back(bullet);
            }
        bulletDelay = 20;
    }
}
void Figure::AddEgg(const SDL_Rect& chickenRect) {
    int eggX = chickenRect.x ;
    int eggY = chickenRect.y ;
    SDL_Rect eggRect = {eggX, eggY, EGG_WIDTH, EGG_HEIGHT};
    eggs_.push_back(eggRect);
}

void Figure::AddItem(const std::string& itemType, int x, int y, int h) {
    SDL_Rect itemRect = {x, y, w, h};
    items_.push_back(std::make_pair(itemType, itemRect));
}

const std::vector<SDL_Rect>& Figure::GetBullets() const {
    return bullets_;
}
const std::vector<SDL_Rect>& Figure::GetChickens() const {
    return chickens_;
}
const std::vector<SDL_Rect>& Figure::GetEggs() const {
    return eggs_;
}
const std::vector<int>& Figure::Gethealth() const {
    return healths_;
}
void Figure::rendItem(){
    for (int i = 0; i < items_.size(); i ++)
        Window::RenderItem(items_[i].fi, items_[i].se.x, items_[i].se.y, items_[i].se.h);
}

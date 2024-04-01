
#include "MainObject.h"

MainObject::MainObject() {
    diem = 0;
    demga = -20;
    number = 700;
    d = 5;
    srand(time(NULL));
}

MainObject::~MainObject() {}

void MainObject::MoveBullets() {
    for (int i = 0; i < bullets_.size(); ++i) {
        bullets_[i].y -= SPEED/20;
        if (bullets_[i].y + HEIGHT_MAIN_OBJECT < 0) {
            bullets_.erase(bullets_.begin() + i);
        }
    }
}

void MainObject::Movelever() {
    if (demga % 50 == 0)
    {
       x = 0;
       y = 0;
       SDL_Rect chicken = {0,0,0,0};
       chickens_.push_back(chicken);
    }
    for (int i = 0; i < chickens_.size(); i++)
    {
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
    for (int i = 0; i < chickens_.size(); i++){
        SDL_Rect chicken = {chickens_[i].x,chickens_[i].y,CHICKEN_WIDTH,CHICKEN_HEIGHT};
        for (int j = 0; j < bullets_.size(); j++) {
            if (CheckCollision(chicken, bullets_[j])) {
                chickens_.erase(chickens_.begin() + i);
                bullets_.erase(bullets_.begin() + j);
                diem ++;
            }
        }
        if (rand() % 2000 < 5) {
            MainObject::AddEggBelowChicken(chickens_[i]);
        }
        if (chickens_[i].y > SCREEN_HEIGHT) {
            chickens_.erase(chickens_.begin() + i);
        }
    }
    if (demga <= 600)
        demga ++;
}



void MainObject::MoveChickens() {
    if (diem >= d){
        if (chickens_.size()!=0&& number != 700)
        {
            for (int i = 0; i < chickens_.size(); ++i) {
                chickens_[i].y += SPEED/40;
                if (chickens_[i].y > SCREEN_HEIGHT) {
                    chickens_.erase(chickens_.begin() + i);
                }
                for (int j = 0; j < bullets_.size(); j++) {
                    if (CheckCollision(chickens_[i], bullets_[j])) {
                        chickens_.erase(chickens_.begin() + i);
                        bullets_.erase(bullets_.begin() + j);
                        diem ++;
                    }
                }
                if (rand() % 2000 < 5) {
                    MainObject::AddEggBelowChicken(chickens_[i]);
                }
            }
        }else{
            MainObject::Movelever();
            if (chickens_.size()==0&&demga >600)
                d = 10000;
            number = 700;
        }
        cout << d << '\n';
    }
    else{
    cout << d << " 100\n";
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
        }
        if (number > 200)
            number -= 1;
    }
    for (int i = 0; i < chickens_.size(); ++i) {
        chickens_[i].y += SPEED/40;
        if (chickens_[i].y > SCREEN_HEIGHT) {
            chickens_.erase(chickens_.begin() + i);
        }
        for (int j = 0; j < bullets_.size(); j++) {
            if (CheckCollision(chickens_[i], bullets_[j])) {
                chickens_.erase(chickens_.begin() + i);
                bullets_.erase(bullets_.begin() + j);
                diem ++;
            }
        }
        if (rand() % 2000 < 5) {
            MainObject::AddEggBelowChicken(chickens_[i]);
        }
    }
}
}

void MainObject::MoveEggs() {
    for (int i = 0; i < eggs_.size(); ++i) {
        eggs_[i].y += SPEED/20;
        if (eggs_[i].y > SCREEN_HEIGHT) {
            eggs_.erase(eggs_.begin() + i);
        }
    }
}

bool MainObject::Check(int x, int y,int w, int h)
{
    CommonFunction::renderText(to_string(diem), 0, 1);
    SDL_Rect planeR = {x,y,w,h};
    for (int i = 0; i < chickens_.size(); i++) {
        if (CheckCollision(chickens_[i], planeR)) {
            chickens_.erase(chickens_.begin() + i);
            return true;
        }
    }
    return false;
}

bool MainObject::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
    bool xOverlap = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool yOverlap = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return xOverlap && yOverlap;
}

void MainObject::AddBullet(int x,int y) {
    SDL_Rect bullet = {x - WIDTH_MAIN_OBJECT / 2, y - 10, WIDTH_MAIN_OBJECT / 2, HEIGHT_MAIN_OBJECT};
    bullets_.push_back(bullet);
}

void MainObject::AddEggBelowChicken(const SDL_Rect& chickenRect) {
    int eggX = chickenRect.x + (CHICKEN_WIDTH - EGG_WIDTH) / 2;
    int eggY = chickenRect.y + CHICKEN_HEIGHT;
    SDL_Rect eggRect = {eggX, eggY, EGG_WIDTH, EGG_HEIGHT};
    eggs_.push_back(eggRect);
}

const std::vector<SDL_Rect>& MainObject::GetBullets() const {
    return bullets_;
}
const std::vector<SDL_Rect>& MainObject::GetChickens() const {
    return chickens_;
}
const std::vector<SDL_Rect>& MainObject::GetEggs() const {
    return eggs_;
}

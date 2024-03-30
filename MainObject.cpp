
#include "MainObject.h"

MainObject::MainObject() {
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

void MainObject::MoveChickens() {
    if (rand() % 1000 < 5) {
        int x = rand() % (SCREEN_WIDTH - CHICKEN_WIDTH);
        cout << x << '\n';
        int y = -HEIGHT_MAIN_OBJECT - 100;
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
    }

    for (int i = 0; i < chickens_.size(); ++i) {
        chickens_[i].y += SPEED/20;
        if (chickens_[i].y > SCREEN_HEIGHT) {
            chickens_.erase(chickens_.begin() + i);
        }
        for (int j = 0; j < bullets_.size(); j++) {
            if (CheckCollision(chickens_[i], bullets_[j])) {
                chickens_.erase(chickens_.begin() + i);
                bullets_.erase(bullets_.begin() + j);
            }
        }
    }
}

bool MainObject::Check(int x, int y,int w, int h)
{
    SDL_Rect planeR = {x,y,w,h};
    for (const auto& existingChicken : chickens_) {
            if (CheckCollision(planeR, existingChicken)) {
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

const std::vector<SDL_Rect>& MainObject::GetBullets() const {
    return bullets_;
}
const std::vector<SDL_Rect>& MainObject::GetChickens() const {
    return chickens_;
}

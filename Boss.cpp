#include "Boss.h"
#include <SDL_image.h>

Boss::Boss() {
    srand(time(NULL));
    rect.x = (SCREEN_WIDTH - BOSS_WIDTH) / 2;
    rect.y = 50;
    rect.w = BOSS_WIDTH;
    rect.h = BOSS_HEIGHT;
    health = 100;
    attackPower = 20;
}

Boss::~Boss() {}

void Boss::Move() {
    if (rand() % 2 == 0){
        rect.x += BOSS_SPEED;
        std::cout << "..." << '\n';
    }
    else
        rect.x -= BOSS_SPEED;
    if (rand() % 2 == 0){
        rect.y += BOSS_SPEED;
        std::cout << "aaa" << '\n';
    }
    else
        rect.y -= BOSS_SPEED;
    if (rect.x < 0)
        rect.x = 0;
    else if (rect.x + BOSS_WIDTH > SCREEN_WIDTH)
        rect.x = SCREEN_WIDTH - BOSS_WIDTH;
    if (rect.y < 0)
        rect.y = 0;
    else if (rect.y + BOSS_HEIGHT > SCREEN_HEIGHT) {
        rect.y = SCREEN_HEIGHT - BOSS_HEIGHT;
    }
}

SDL_Rect Boss::GetBoss(){
    return rect;
}



SDL_Rect Boss::HealthBar() {
    SDL_Rect healthBar;
    healthBar.x = rect.x;
    healthBar.y = rect.y - 20;
    healthBar.w = (health * BOSS_WIDTH) / 200;
    healthBar.h = 10;
    return healthBar;
}
int Boss::Health() {
    return health;
}

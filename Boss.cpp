#include <bits/stdc++.h>
#include <algorithm>
#include "Boss.h"
#include <SDL_image.h>
#include "Figure.h"

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
    rect.x += velocityX ;
    rect.y += velocityY ;
    if (rect.x <= 0 || rect.x + BOSS_WIDTH >= SCREEN_WIDTH) {
        rect.x = std::max(0,rect.x);
        rect.x = std::min(rect.x, SCREEN_WIDTH - BOSS_WIDTH);
        velocityX = rand() % 3 - 1;
        velocityY = rand() % 3 - 1;
    }
    if (rect.y <= 30 || rect.y + BOSS_HEIGHT >= SCREEN_HEIGHT) {
        rect.y = std::max(30,rect.y);
        rect.y = std::min(rect.y, SCREEN_HEIGHT - BOSS_HEIGHT);
        velocityX = rand() % 3 - 1;
        velocityY = rand() % 3 - 1;
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

void Boss::Reset(){
    rect.x = (SCREEN_WIDTH - BOSS_WIDTH) / 2;
    rect.y = 50;
}

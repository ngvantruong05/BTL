//#include "Boss.h"
//#include <SDL_image.h>
//
//Boss::Boss() {
//    rect.x = (SCREEN_WIDTH - BOSS_WIDTH) / 2;
//    rect.y = 50;
//    rect.w = BOSS_WIDTH;
//    rect.h = BOSS_HEIGHT;
//    health = 200;
//    attackPower = 20;
//}
//
//Boss::~Boss() {}
//
//void Boss::move() {
//    rect.x += BOSS_SPEED;
//    if (rect.x <= 0 || rect.x + rect.w >= SCREEN_WIDTH) {
//        BOSS_SPEED = -BOSS_SPEED;
//    }
//}
//
//SDL_Rect Boss::HealthBar() {
//    SDL_Rect healthBar;
//    healthBar.x = rect.x;
//    healthBar.y = rect.y - 20;
//    healthBar.w = (health * BOSS_WIDTH) / 200;
//    healthBar.h = 10;
//    return healthBar;
//}

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
    int direction = rand() % 4;
    // Di chuyển boss dựa trên giá trị ngẫu nhiên được tạo ra
    switch (direction) {
        case 0: // Di chuyển boss sang phải
            rect.x += BOSS_SPEED;
            break;
        case 1: // Di chuyển boss sang trái
            rect.x -= BOSS_SPEED;
            break;
        case 2: // Di chuyển boss xuống
            rect.y += BOSS_SPEED;
            break;
        case 3: // Di chuyển boss lên
            rect.y -= BOSS_SPEED;
            break;
        default:
            break;
    }
//    if (rand() % 2 == 0){
//        rect.x += BOSS_SPEED;
//    }
//    else
//        rect.x -= BOSS_SPEED;
//    if (rand() % 2 == 0){
//        rect.y += BOSS_SPEED;
//    }
//    else
//        rect.y -= BOSS_SPEED;
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

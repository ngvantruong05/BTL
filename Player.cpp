#include "Player.h"
#include "Window.h"

Player::Player() : x(0), y(0), w(50), h(100) {}

Player::~Player() {}

void Player::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::Move(SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_LEFT) {
        x -= SPEED;
    } else if (event.key.keysym.sym == SDLK_RIGHT) {
        x += SPEED;
    } else if (event.key.keysym.sym == SDLK_UP) {
        y -= SPEED/2;
    } else if (event.key.keysym.sym == SDLK_DOWN) {
        y += SPEED/2;
    }

    if (x < 0) {
        x = 0;
    } else if (x + w > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - w;
    }

    if (y < SCREEN_HEIGHT/2) {
        y = SCREEN_HEIGHT/2;
    } else if (y + h > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - h;
    }
}

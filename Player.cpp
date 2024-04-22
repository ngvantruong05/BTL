#include "Player.h"
#include "Window.h"

Player::Player() : x((SCREEN_WIDTH - 100) / 2), y( SCREEN_HEIGHT - 100), w(50), h(100) {}

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

    if (y < 0) {
        y = 0;
    } else if (y + h > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - h;
    }
}

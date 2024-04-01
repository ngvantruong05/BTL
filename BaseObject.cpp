
#include "BaseObject.h"
#include "CommonFunction.h"

BaseObject::BaseObject() : x(0), y(0), width(50), height(100) {}

BaseObject::~BaseObject() {}

void BaseObject::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void BaseObject::Move(SDL_Event& event) {
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
    } else if (x + width > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - width;
    }

    if (y < SCREEN_HEIGHT/2) {
        y = SCREEN_HEIGHT/2;
    } else if (y + height > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - height;
    }
}


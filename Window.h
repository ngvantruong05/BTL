#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const int CHICKEN_WIDTH = 50;
const int CHICKEN_HEIGHT = 100;
const int EGG_WIDTH = 10;
const int EGG_HEIGHT = 30;
const int BOSS_WIDTH = 300;
const int BOSS_HEIGHT = 300;
const int BOSS_HEALTH = 100;
const int BULLET_WIDTH = 8;
const int BULLET_HEIGHT = 20;
const int MAX_HEALTH = 3;
const int SPEED = 40;
const int BOSS_SPEED = 10;

static SDL_Window* gWindow = NULL;

static SDL_Texture* backgroundTexture = NULL;
static SDL_Renderer* gRenderer = NULL;
static TTF_Font* gFont = NULL;

namespace Window
{
    bool init();
    SDL_Texture* LoadTexture(const std::string& filePath);
    void RenderTexture(SDL_Texture* texture, int x, int y, int w, int h);
    void RenderTextures(SDL_Texture* texture, int x, int y, int w, int h);
    void show();
    void close();
    void RenderText(const std::string& text, int x, int y);
    void RenderHPBar(int x, int y, int width, int height, int currentHP, int maxHP);
}
#endif

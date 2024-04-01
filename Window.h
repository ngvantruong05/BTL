#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CHICKEN_WIDTH = 50;
const int CHICKEN_HEIGHT = 100;
const int EGG_WIDTH = 10;
const int EGG_HEIGHT = 30;
const int BOSS_WIDTH = 10;
const int BOSS_HEIGHT = 30;
const int WIDTH_MAIN_OBJECT = 5;
const int HEIGHT_MAIN_OBJECT = 2;
const int SPEED = 40;

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
    void renderText(const std::string& text, int x, int y);
}
#endif

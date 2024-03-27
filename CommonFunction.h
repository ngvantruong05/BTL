
#ifndef COMMONFUNCTION_H_
#define COMMONFUNCTION_H_
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int RECT_WIDTH = 50;
const int RECT_HEIGHT = 50;
const int SPEED = 10;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

static SDL_Texture* backgroundTexture = NULL;
static SDL_Texture* chickenTexture = NULL;

namespace CommonFunction
{
    bool init();
    void close();
    void render(int x, int y);
}
#endif


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
const int WIDTH_MAIN_OBJECT = 5;
const int HEIGHT_MAIN_OBJECT = 2;
const int SPEED = 20;

static SDL_Window* gWindow = NULL;

static SDL_Texture* backgroundTexture = NULL;
static SDL_Renderer* gRenderer = NULL;
namespace CommonFunction
{

    bool init();
    SDL_Texture* LoadTexture(const string& filePath);
    void RenderTexture(SDL_Texture* texture, int x, int y, int w, int h);
    void show();
    void close();
}
#endif

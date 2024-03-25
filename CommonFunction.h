

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
const string WINDOW_TITLE = "SDL_test";

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;

static SDL_Texture* backgroundTexture = NULL;
static SDL_Texture* birdTexture = NULL;
static SDL_Texture* pipeTexture = NULL;

//namespace COMMONFUNCTION
    bool init();
    void close();
    void render();

#endif

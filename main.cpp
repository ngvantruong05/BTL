#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "CommonFunction.h"

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46
using namespace std;

//bool init() {
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    gWindow = SDL_CreateWindow("...", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (gWindow == NULL) {
//        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
//    if (gRenderer == NULL) {
//        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        return false;
//    }
//
//    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//    SDL_Surface* backgroundSurface = IMG_Load("vutru.jpg");
//    if (backgroundSurface == NULL) {
//        std::cout << "Failed to load background image! SDL_Error: " << IMG_GetError() << std::endl;
//        return false;
//    }
//    backgroundTexture = SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
//    SDL_FreeSurface(backgroundSurface);
//
//    SDL_Surface* birdSurface = IMG_Load("plane.png");
//    if (birdSurface == NULL) {
//        std::cout << "Failed to load bird image! SDL_Error: " << IMG_GetError() << std::endl;
//        return false;
//    }
//    chickenTexture = SDL_CreateTextureFromSurface(gRenderer, birdSurface);
//    SDL_FreeSurface(birdSurface);
//
////    SDL_Surface* pipeSurface = IMG_Load("chicken.jpg");
////    if (pipeSurface == NULL) {
////        std::cout << "Failed to load pipe image! SDL_Error: " << IMG_GetError() << std::endl;
////        return false;
////    }
////    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
////    SDL_FreeSurface(pipeSurface);
//    return true;
//}

//int main(int argc, char* args[]) {
//    if (!init()) {
//        std::cout << "Failed to initialize!" << std::endl;
//        return -1;
//    }
////    bool quit = false;
////    while (!quit) {
////        handleEvents(quit);
////        update();
////        render();
////        SDL_Delay(10);
////    }
//    close();
//    return 0;
//}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("...", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Surface* backgroundSurface = IMG_Load("vutru.jpg");
    if (backgroundSurface == NULL) {
        std::cout << "Failed to load background image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    SDL_Surface* birdSurface = IMG_Load("plane.png");
    if (birdSurface == NULL) {
        std::cout << "Failed to load bird image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    chickenTexture = SDL_CreateTextureFromSurface(gRenderer, birdSurface);
    SDL_FreeSurface(birdSurface);

    return true;
}

int main(int argc, char* argv[]) {
    init();

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        CommonFunction::render();
    }

    CommonFunction::close();
    return 0;
}


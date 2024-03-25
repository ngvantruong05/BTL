
#include "CommonFunction.h"
using namespace std;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    // Load background image
    SDL_Surface* backgroundSurface = IMG_Load("vutru.jpg");
    if (backgroundSurface == NULL) {
        std::cout << "Failed to load background image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Load bird image
    SDL_Surface* birdSurface = IMG_Load("plane.png");
    if (birdSurface == NULL) {
        std::cout << "Failed to load bird image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    birdTexture = SDL_CreateTextureFromSurface(gRenderer, birdSurface);
    SDL_FreeSurface(birdSurface);

    // Load pipe image
    SDL_Surface* pipeSurface = IMG_Load("chicken.jpg");
    if (pipeSurface == NULL) {
        std::cout << "Failed to load pipe image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

void close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void render() {
    SDL_RenderClear(gRenderer);
    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, &backgroundRect);
//    SDL_Rect birdRect = { bird.x, bird.y, BIRD_WIDTH, BIRD_HEIGHT };
//    SDL_RenderCopy(gRenderer, birdTexture, NULL, &birdRect);
}


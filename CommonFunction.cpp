
#include "CommonFunction.h"
#include "BaseObject.h"
using namespace std;

bool CommonFunction::init() {
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

    SDL_Surface* planeSurface = IMG_Load("plane.png");
    if (planeSurface == NULL) {
        std::cout << "Failed to load bird image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    planeTexture = SDL_CreateTextureFromSurface(gRenderer, planeSurface);
    SDL_FreeSurface(planeSurface);
    return true;
}

void CommonFunction::render(int x, int y) {
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, backgroundTexture, nullptr, nullptr);
    SDL_Rect planeRect = { x, y, 100, 100};
    SDL_RenderCopy(gRenderer, planeTexture, nullptr, &planeRect);
    SDL_RenderPresent(gRenderer);
}

void CommonFunction::close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(planeTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}


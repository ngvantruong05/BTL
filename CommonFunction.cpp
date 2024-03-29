
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
    backgroundTexture = LoadTexture("vutru.jpg");


    return true;
}

SDL_Texture* CommonFunction::LoadTexture(const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cout << "Failed to load texture: " << filePath << ". SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void CommonFunction::RenderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, backgroundTexture, nullptr, nullptr);
    SDL_Rect destRect = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, nullptr, &destRect);
    SDL_RenderPresent(gRenderer);
}


//void CommonFunction::render(int x, int y) {
//    SDL_RenderClear(gRenderer);
//    SDL_RenderCopy(gRenderer, backgroundTexture, nullptr, nullptr);
//    SDL_Rect planeRect = { x, y, 100, 100};
//    SDL_RenderCopy(gRenderer, planeTexture, nullptr, &planeRect);
//    SDL_RenderPresent(gRenderer);
//}
//
void CommonFunction::close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}


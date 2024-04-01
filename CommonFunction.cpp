
#include "CommonFunction.h"
#include "BaseObject.h"
using namespace std;

bool CommonFunction::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Bắn gà", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    gFont = TTF_OpenFont("diem.ttf", 29);
    if (gFont == NULL) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    backgroundTexture = LoadTexture("vutru.jpg");

    SDL_RenderCopy(gRenderer, backgroundTexture, nullptr, nullptr);
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
     SDL_RenderClear(gRenderer);
    return texture;
}

void CommonFunction::RenderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect destRect = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, nullptr, &destRect);
}
void CommonFunction::show()
{
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, backgroundTexture, nullptr, nullptr);
}

void CommonFunction::close() {
    TTF_CloseFont(gFont);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void CommonFunction::renderText(const std::string& text, int x, int y) {
    SDL_Color textColor = {255, 0, 0};
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    if (textSurface == NULL) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    } else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (texture == NULL) {
            std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        } else {
            SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
            SDL_RenderCopy(gRenderer, texture, NULL, &renderQuad);
            SDL_DestroyTexture(texture);
        }

        SDL_FreeSurface(textSurface);
    }
}


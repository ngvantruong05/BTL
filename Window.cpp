#include "Window.h"
#include "Player.h"

namespace Window
{
    bool init() {
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

    SDL_Texture* LoadTexture(const std::string& filePath) {
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

    void RenderTexture(SDL_Texture* texture, int x, int y, int w, int h) {
        SDL_Rect destRect = {x, y, w, h};
        SDL_RenderCopy(gRenderer, texture, nullptr, &destRect);
    }

    void show(){
        SDL_RenderPresent(gRenderer);
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, backgroundTexture, nullptr, nullptr);
    }

    void close() {
        TTF_CloseFont(gFont);
        SDL_DestroyTexture(backgroundTexture);
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        IMG_Quit();
        SDL_Quit();
        TTF_Quit();
    }

    void RenderText(const std::string& text, int x, int y) {
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
    void RenderBloodBar(int x, int y, int width, int height, int currentHP, int maxHP) {
        SDL_Rect outlineRect = { x, y, width, height};
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        int innerWidth = (currentHP * width) / maxHP;

        SDL_Rect fillRect = { x + 1, y + 1, innerWidth - 1, height - 1 };
        SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
        SDL_RenderFillRect(gRenderer, &fillRect);
    }
    void RenderItem(const std::string& text, int x, int y, int number){
        SDL_Color textColor;
        SDL_Color backgroundColor;
        if (number == 1){
            textColor = {255, 255, 0, 255};
            backgroundColor = {255, 0, 0, 255};
        }   else    if (number == 2){
            textColor = {255, 0, 0, 255};
            backgroundColor = {0, 255, 0, 255};
        }   else{
            textColor = {0, 0, 0, 255};
            backgroundColor = {255, 255, 255, 255};
        }

        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
        if (textSurface == NULL) {
            std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (textTexture == NULL) {
            std::cerr << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(textSurface);
            return;
        }

        SDL_Rect backgroundRect = {x, y, textSurface->w, textSurface->h};
        SDL_SetRenderDrawColor(gRenderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
        SDL_RenderFillRect(gRenderer, &backgroundRect);

        SDL_Rect renderRect = {x, y, textSurface->w, textSurface->h};
        SDL_RenderCopy(gRenderer, textTexture, NULL, &renderRect);

        SDL_DestroyTexture(textTexture);
    }
}


#include "CommonFunction.h"
using namespace std;

void CommonFunction::close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

//void render() {
//    SDL_RenderClear(gRenderer);
//    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
//    SDL_RenderPresent(gRenderer);
//    SDL_Delay(3000);
//}
void CommonFunction::render() {
//    SDL_RenderClear(gRenderer);
//    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
//    SDL_RenderPresent(gRenderer);
//
//    SDL_RenderClear(gRenderer);
//
//    // Vẽ gà ở giữa màn hình
//    SDL_Rect chickenRect = { (SCREEN_WIDTH - 100) / 2, (SCREEN_HEIGHT - 100) / 2, 100, 100 };
//    SDL_RenderCopy(gRenderer, chickenTexture, nullptr, &chickenRect);
//
//    SDL_RenderPresent(gRenderer);
//
//
//    SDL_Delay(3000);
    SDL_RenderClear(gRenderer);
    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
    SDL_RenderPresent(gRenderer);

    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, backgroundTexture, nullptr, nullptr);

    // Vẽ gà ở giữa màn hình
    SDL_Rect chickenRect = { (SCREEN_WIDTH - 100) / 2, (SCREEN_HEIGHT - 100) / 2, 100, 100 };
    SDL_RenderCopy(gRenderer, chickenTexture, nullptr, &chickenRect);

    SDL_RenderPresent(gRenderer);

    SDL_Delay(3000);
}

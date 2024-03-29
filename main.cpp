#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "CommonFunction.h"
#include "BaseObject.h"

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46
using namespace std;

SDL_Texture* planeTexture = NULL;
SDL_Texture* bulletTexture = NULL;
SDL_Texture* chickenTexture = NULL;

//void text();
void text()
{
    planeTexture = CommonFunction::LoadTexture("plane.png");
    bulletTexture = CommonFunction::LoadTexture("laser.png");
    //chickenTexture = CommonFunction::LoadTexture("chicken.png");
}
void close()
{
    SDL_DestroyTexture(planeTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(chickenTexture);
}

int main(int argc, char* argv[]) {
    if (!CommonFunction::init()) {
        cout << "Failed to initialize!" << std::endl;
        return -1;
    }
    text();
    BaseObject plane;
    plane.SetPosition((SCREEN_WIDTH - 100)/2,SCREEN_HEIGHT - 100);

    BaseObject bullets;
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)!=0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else
                plane.Move(event);
        }
        CommonFunction::RenderTexture(planeTexture,plane.GetX(),plane.GetY(),100,100);
    }
    close();
    CommonFunction::close();
    return 0;
}


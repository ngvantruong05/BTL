
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "MainObject.h"


#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46
using namespace std;
SDL_Texture* planeTexture = NULL;
SDL_Texture* bulletTexture = NULL;
SDL_Texture* chickenTexture = NULL;
SDL_Texture* hpTexture = NULL;

void text()
{
    planeTexture = CommonFunction::LoadTexture("ok.png");
    bulletTexture = CommonFunction::LoadTexture("laser.png");
    chickenTexture = CommonFunction::LoadTexture("chicken.png");
    hpTexture = CommonFunction::LoadTexture("hp.png");
}
void close()
{
    SDL_DestroyTexture(planeTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(hpTexture);
}

int main(int argc, char* argv[]) {
    if (!CommonFunction::init()) {
        cout << "Failed to initialize!" << std::endl;
        return -1;
    }
    text();
    int hp = 3;
    BaseObject plane;
    plane.SetPosition((SCREEN_WIDTH - 100)/2,SCREEN_HEIGHT - 100);
    MainObject mainObject;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)!=0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    mainObject.AddBullet(plane.GetX() + 25, plane.GetY());
                }
                else
                plane.Move(event);
            }
        }

        mainObject.MoveBullets();
        mainObject.MoveChickens();

        CommonFunction::RenderTexture(planeTexture, plane.GetX(), plane.GetY(), 50, 100);
        const vector<SDL_Rect>& bullets = mainObject.GetBullets();
        for (const auto& bullet : bullets) {
            CommonFunction::RenderTexture(bulletTexture, bullet.x, bullet.y, WIDTH_MAIN_OBJECT/10, HEIGHT_MAIN_OBJECT/2);
        }
        const vector<SDL_Rect>& chickens = mainObject.GetChickens();
        for (const auto& chicken : chickens) {
            CommonFunction::RenderTexture(chickenTexture, chicken.x, chicken.y, 50, 100);
        }
        for (int i = 1; i <= hp; i++)
        {
            CommonFunction::RenderTexture(hpTexture,SCREEN_WIDTH - 30*i,0,30,30);
        }
        CommonFunction::renderText("123", 0, 1);

        CommonFunction::show();
        SDL_Delay(10);
    }
    close();
    CommonFunction::close();
    return 0;
}


#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "CommonFunction.h"
#include "BaseObject.h"
#include "MainObject.h"

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
    MainObject mainObject; // Tạo đối tượng MainObject

    BaseObject plane;
    plane.SetPosition((SCREEN_WIDTH - 100)/2,SCREEN_HEIGHT - 100);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)!=0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    // Thêm đạn từ vị trí giữa máy bay
                    mainObject.AddBullet(plane.GetX() + 50, plane.GetY());
                }
                else
                plane.Move(event);
            }

        }

        mainObject.MoveBullets();
        mainObject.MoveChickens();

        CommonFunction::RenderTexture(planeTexture, plane.GetX(), plane.GetY(), 100, 100);

        const std::vector<SDL_Rect>& bullets = mainObject.GetBullets();
        for (const auto& bullet : bullets) {
            CommonFunction::RenderTexture(bulletTexture, bullet.x, bullet.y, WIDTH_MAIN_OBJECT, HEIGHT_MAIN_OBJECT);
        }

        CommonFunction::show();
        SDL_Delay(10);
    }
    close();
    CommonFunction::close();
    return 0;
}

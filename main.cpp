#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Player.h"
#include "Figure.h"
#include "Boss.h"

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46

SDL_Texture* planeTexture = NULL;
SDL_Texture* bulletTexture = NULL;
SDL_Texture* chickenTexture = NULL;
SDL_Texture* eggTexture = NULL;
SDL_Texture* hpTexture = NULL;
SDL_Texture* bossTexture = NULL;

void text()
{
    planeTexture = Window::LoadTexture("ok.png");
    bulletTexture = Window::LoadTexture("sphere.png");
    chickenTexture = Window::LoadTexture("chicken.png");
    eggTexture = Window::LoadTexture("egg.png");
    hpTexture = Window::LoadTexture("hp.png");
    bossTexture = Window::LoadTexture("boss.png");
}

void close()
{
    SDL_DestroyTexture(planeTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(hpTexture);
}

int main(int argc, char* argv[]) {
    if (!Window::init()) {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }

    text();

    int hp = 3;
    Player plane;
    plane.SetPosition((SCREEN_WIDTH - 100) / 2, SCREEN_HEIGHT - 100);
    Figure figure;
    Boss boss;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    figure.AddBullet(plane.GetX() + 25, plane.GetY());
                }
                else
                    plane.Move(event);
            }
        }

        figure.MoveBullets();
        figure.MoveChickens();
        figure.MoveEggs();

        Window::RenderTexture(planeTexture, plane.GetX(), plane.GetY(), 50, 100);

        const std::vector<SDL_Rect>& bullets = figure.GetBullets();
        for (const auto& bullet : bullets) {
            Window::RenderTexture(bulletTexture, bullet.x, bullet.y, WIDTH_MAIN_OBJECT / 10, HEIGHT_MAIN_OBJECT / 2);
        }
        const std::vector<SDL_Rect>& chickens = figure.GetChickens();
        for (const auto& chicken : chickens) {
            Window::RenderTexture(chickenTexture, chicken.x, chicken.y, CHICKEN_WIDTH, CHICKEN_HEIGHT);
        }
        const std::vector<SDL_Rect>& eggs = figure.GetEggs();
        for (const auto& egg : eggs) {
            Window::RenderTexture(eggTexture, egg.x, egg.y, EGG_WIDTH, EGG_HEIGHT);
        }

        SDL_Rect bossRect = boss.move();
        //Window::RenderTexture(bossTexture,bossRect.x,bossRect.y,BOSS_WIDTH,BOSS_HEIGHT);

        if (figure.Check(plane.GetX(), plane.GetY(), 50, 100))
            hp--;
        if (hp == 0)
        {
            Window::renderText("Game Over", (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
            Window::show();
            SDL_Delay(3000);
            break;
        }
        for (int i = 1; i <= hp; i++)
        {
            Window::RenderTexture(hpTexture, SCREEN_WIDTH - 30 * i, 0, 30, 30);
        }

        Window::show();
        SDL_Delay(10);
    }

    close();
    Window::close();
    return 0;
}

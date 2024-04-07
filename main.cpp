#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Window.h"
#include "Player.h"
#include "Figure.h"
#include "Boss.h"

SDL_Texture* planeTexture = NULL;
SDL_Texture* bulletTexture = NULL;
SDL_Texture* chickenTexture = NULL;
SDL_Texture* eggTexture = NULL;
SDL_Texture* bloodTexture = NULL;
SDL_Texture* bossTexture = NULL;
SDL_Texture* khienTexture = NULL;
int bossHealth = 0, level = 1;
void text()
{
    planeTexture = Window::LoadTexture("plane.png");
    bulletTexture = Window::LoadTexture("sphere.png");
    chickenTexture = Window::LoadTexture("chicken.png");
    eggTexture = Window::LoadTexture("egg.png");
    bloodTexture = Window::LoadTexture("blood.png");
    bossTexture = Window::LoadTexture("boss.png");
    khienTexture = Window::LoadTexture("khien.png");
}

void close()
{
    SDL_DestroyTexture(planeTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(bloodTexture);
}

int main(int argc, char* argv[]) {
    if (!Window::init()) {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }

    text();

    int blood = 3;
    Player plane;
    plane.SetPosition((SCREEN_WIDTH - 100) / 2, SCREEN_HEIGHT - 100);
    Figure figure;
    Boss boss;

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        if (blood == 0)
        {
            Window::RenderText("Game Over", (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
            Window::show();
            SDL_Delay(3000);
            break;
        }
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    figure.AddBullet(plane.GetX(), plane.GetY());
                }
                else
                    plane.Move(event);
            }
        }

        figure.MoveBullets();
        figure.MoveChickens();
        figure.MoveEggs();

        //Window::RenderTexture(khienTexture, plane.GetX() - 5, plane.GetY() - 5, 60, 105);
        Window::RenderTexture(planeTexture, plane.GetX(), plane.GetY(), 50, 100);

        const std::vector<SDL_Rect>& bullets = figure.GetBullets();
        for (const auto& bullet : bullets) {
            Window::RenderTexture(bulletTexture, bullet.x, bullet.y,  BULLET_WIDTH, BULLET_HEIGHT);
        }
        const std::vector<SDL_Rect>& chickens = figure.GetChickens();
        const std::vector<int>& health = figure.Gethealth();
        for (int i = 0; i < chickens.size();i++) {
            Window::RenderTexture(chickenTexture, chickens[i].x, chickens[i].y, CHICKEN_WIDTH, CHICKEN_HEIGHT);
            Window::RenderBloodBar(chickens[i].x + CHICKEN_WIDTH/4, chickens[i].y + 5 + CHICKEN_HEIGHT, CHICKEN_WIDTH/2, 2,health[i],MAX_HEALTH);
        }
        const std::vector<SDL_Rect>& eggs = figure.GetEggs();
        for (const auto& egg : eggs) {
            Window::RenderTexture(eggTexture, egg.x, egg.y, EGG_WIDTH, EGG_HEIGHT);
        }
        if (figure.GetScore() % 30 == 0 && figure.GetScore() != 0)
        {
            bossHealth = BOSS_HEALTH * level;
        }
        if (bossHealth > 0){
            boss.Move();
            SDL_Rect bossRect = boss.GetBoss();
            SDL_Rect planeRect = {plane.GetX(), plane.GetY(), 50, 100};
//            if (figure.CheckCollision(bossRect,planeRect))
//                blood--;
            bossHealth -= figure.CheckBoss(bossRect);
            if (bossHealth <= 0){
                figure.SetScore(figure.GetScore() + 30 * level);
                level ++;
            }
            if (rand() % 500 < 2) {
                figure.AddEgg({bossRect.x + (BOSS_WIDTH - EGG_WIDTH) / 2,bossRect.y + BOSS_HEIGHT - 50,bossRect.w,bossRect.h});
            }
            Window::RenderBloodBar(100,10,SCREEN_WIDTH-200,30,bossHealth,BOSS_HEALTH * level);
            Window::RenderTexture(bossTexture,bossRect.x,bossRect.y,BOSS_WIDTH,BOSS_HEIGHT);
        }
        if (figure.Check(plane.GetX(), plane.GetY(), 50, 100))
            blood--;
        for (int i = 1; i <= blood; i++)
            Window::RenderTexture(bloodTexture, SCREEN_WIDTH - 30 * i, 0, 30, 30);

        Window::show();
        SDL_Delay(10);
    }

    close();
    Window::close();
    return 0;
}

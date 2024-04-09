#include <bits/stdc++.h>
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
SDL_Texture* laserTexture = NULL;
SDL_Texture* chickenTexture = NULL;
SDL_Texture* eggTexture = NULL;
SDL_Texture* bloodTexture = NULL;
SDL_Texture* bossTexture = NULL;
SDL_Texture* shieldTexture = NULL;
void text(){
    planeTexture = Window::LoadTexture("plane.png");
    bulletTexture = Window::LoadTexture("sphere.png");
    laserTexture = Window::LoadTexture("laser.png");
    chickenTexture = Window::LoadTexture("chicken.png");
    eggTexture = Window::LoadTexture("egg.png");
    bloodTexture = Window::LoadTexture("blood.png");
    bossTexture = Window::LoadTexture("boss.png");
    shieldTexture = Window::LoadTexture("shield.png");
}
void close(){
    SDL_DestroyTexture(planeTexture);
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(chickenTexture);
    SDL_DestroyTexture(bloodTexture);
}
bool menu(SDL_Event& event, bool& quit, bool& play, bool& rankings) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
            return false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 && y <= SCREEN_HEIGHT / 3 + 50) {
                play = true;
                return false;
            } else if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 100 && y <= SCREEN_HEIGHT / 3 + 150) {
                rankings = true;
                return false;
            } else if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 200 && y <= SCREEN_HEIGHT / 3 + 250) {
                quit = true;
                return false;
            }
        }
    }

    Window::RenderMenu("Play", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3, 300 , 50);
    Window::RenderMenu("Score Rankings", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 100, 300 , 50);
    Window::RenderMenu("Exit", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 200, 300 , 50);
    Window::show();

    return true;
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
    Uint32 startTime = SDL_GetTicks();
    Uint32 endTime = SDL_GetTicks();
    Uint32 man1Time = SDL_GetTicks();
    int countshield = 10;
    int bossHealth = 0, level = 1;

    bool quit = false, iscout = false, isshield = false, check = false, inMenu = true;
    bool play = false;
    bool rankings = false;

    SDL_Event event;
    while (!quit) {
        if (inMenu){
            inMenu = menu(event, quit, play, rankings);
//            Window::RenderMenu("Play", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3, 300 , 50);
//            Window::RenderMenu("Score Rankings", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 100, 300 , 50);
//            Window::RenderMenu("Exit", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 200, 300 , 50);
//            Window::show();
//            SDL_Delay(10);
        }

        if (blood == 0){
            Window::RenderText("Game Over", (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
            Window::show();
            SDL_Delay(3000);
            break;
        }
        if (play){
            if (blood == 0){
                play = false;
                continue;
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

            int man = level % 3;
            if (man == 1)
            {
                if (iscout){
                    iscout = false;
                    std::string s = "Man " + std::to_string(level);
                    Window::RenderText(s, (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
                    Window::show();
                    man1Time = SDL_GetTicks();
                    SDL_Delay(3000);
                }
                endTime = SDL_GetTicks();
                if (endTime - man1Time >= 20000){
                    check = figure.AppearChicken();
                    if (check){
                        level ++;
                        iscout = true;
                        check = false;
                    }
                }else
                    figure.MoveChickens1();
            }else   if (man == 2){
                if (iscout){
                    iscout = false;
                    std::string s = "Man " + std::to_string(level);
                    Window::RenderText(s, (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
                    Window::show();
                    SDL_Delay(3000);
                }
                figure.MoveChickens2();
                if (figure.CheckChickens() && figure.Getdemga() >= 600){
                    check = figure.AppearChicken();
                    if (check){
                        figure.SetDemga(-20);
                        level ++;
                        iscout = true;
                        check = false;
                    }
                }
            }else{
                if (iscout){
                    bossHealth = BOSS_HEALTH * level / 3;
                    iscout = false;
                    std::string s = "BOSS " + std::to_string(level / 3);
                    Window::RenderText(s, (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
                    Window::show();
                    SDL_Delay(3000);
                }
                if (bossHealth > 0){
                    boss.Move();
                    SDL_Rect bossRect = boss.GetBoss();
                    SDL_Rect planeRect = {plane.GetX(), plane.GetY(), 50, 100};
                    if (figure.CheckCollision(bossRect,planeRect)){
                        if (countshield > 3 && isshield == false){
                            blood--;
                            figure.SetNumBullets(1);
                            isshield = true;
                        }
                    }
                    bossHealth -= figure.CheckBoss(bossRect);
                    if (rand() % 500 < 5) {
                        figure.AddEgg({bossRect.x + (BOSS_WIDTH - EGG_WIDTH) / 2,bossRect.y + BOSS_HEIGHT - 50,bossRect.w,bossRect.h});
                    }
                    Window::RenderBloodBar(100,10,SCREEN_WIDTH-200,30,bossHealth,BOSS_HEALTH * level / 3);
                    Window::RenderTexture(bossTexture,bossRect.x,bossRect.y,BOSS_WIDTH,BOSS_HEIGHT);
                }
                if (bossHealth <= 0){
                    check = figure.AppearChicken();
                    if (check){
                        figure.SetScore(figure.GetScore() + 30 * level / 3);
                        figure.SetLevel(level / 3 + 1);
                        level ++;
                        iscout = true;
                        check = false;
                    }
                }
            }
            figure.MoveBullets();
            figure.MoveEggs();
            figure.MoveItems();
            figure.CheckFigure();

            const std::vector<SDL_Rect>& bullets = figure.GetBullets();
            for (const auto& bullet : bullets) {
                if (bullet.h == 0)
                    Window::RenderTexture(laserTexture, bullet.x, bullet.y,  BULLET_WIDTH, BULLET_HEIGHT);
                else
                    Window::RenderTexture(bulletTexture, bullet.x, bullet.y,  BULLET_WIDTH, BULLET_HEIGHT);
            }
            const std::vector<SDL_Rect>& chickens = figure.GetChickens();
            const std::vector<int>& health = figure.Gethealth();
            for (int i = 0; i < chickens.size();i++) {
                Window::RenderTexture(chickenTexture, chickens[i].x, chickens[i].y, CHICKEN_WIDTH, CHICKEN_HEIGHT);
                Window::RenderBloodBar(chickens[i].x + CHICKEN_WIDTH/4, chickens[i].y + 5 + CHICKEN_HEIGHT, CHICKEN_WIDTH/2, 2,health[i],MAX_HEALTH * ((level + 2)/ 3));
            }
            const std::vector<SDL_Rect>& eggs = figure.GetEggs();
            for (const auto& egg : eggs) {
                Window::RenderTexture(eggTexture, egg.x, egg.y, EGG_WIDTH, EGG_HEIGHT);
            }

            if (isshield){
                endTime = SDL_GetTicks();
                Window::RenderTexture(shieldTexture, plane.GetX() - 5, plane.GetY() - 5, 60, 105);
                if (endTime - startTime >= 2000){
                    isshield = false;
                    startTime = SDL_GetTicks();
                    countshield = 1;
                }
            }
            if (countshield <= 3){
                endTime = SDL_GetTicks();
                if (endTime - startTime <= 500){
                    Window::RenderTexture(shieldTexture, plane.GetX() - 5, plane.GetY() - 5, 60, 105);
                }else   if (endTime - startTime > 1000){
                    startTime = endTime;
                    countshield ++;
                }
            }
            Window::RenderTexture(bloodTexture, SCREEN_WIDTH - 30, 0, 30, 40);
            std::string s = std::to_string(blood);
            Window::RenderText(s, SCREEN_WIDTH - s.size() * 15 - 30, 1);
            Window::RenderTexture(planeTexture, plane.GetX(), plane.GetY(), 50, 100);

            figure.rendItem();
            int t = figure.Check(plane.GetX(), plane.GetY(), 50, 100);
            if (t == 1 && countshield > 3 && isshield == false){
                blood--;
                figure.SetNumBullets(1);
                isshield = true;
            }else   if (t == 2)
                blood++;
            else    if (t == 3){
                isshield = true;
                startTime = SDL_GetTicks();
            }

            Window::show();
            SDL_Delay(10);
        }
    }

    close();
    Window::close();
    return 0;
}


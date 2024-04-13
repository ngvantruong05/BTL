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

int main(int argc, char* argv[]) {
    if (!Window::init()) {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }
    text();

    Player plane;
    Figure figure;
    Boss boss;
    SDL_Rect bkground = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    Uint32 startTime = SDL_GetTicks();
    Uint32 endTime = SDL_GetTicks();
    Uint32 man1Time = SDL_GetTicks();
    int bossHealth = 0, level = 1, blood = 3, countshield = 10;
    std::string yourname="";

    bool quit = false, iscout = false, isshield = false, check = false, menu = true, endgame = false;
    bool play = false, rankings = false, sname = false;

    SDL_Event event;
    while (!quit) {
        if (menu){
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                    menu = false;
                    continue;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 && y <= SCREEN_HEIGHT / 3 + 50) {
                        Window::Mixer("click.wav");
                        sname = true;
                        menu = false;
                        figure.Clear();
                        level = 1;
                        blood = 3;
                        iscout = true;
                        continue;
                    } else if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 100 && y <= SCREEN_HEIGHT / 3 + 150) {
                        Window::Mixer("click.wav");
                        rankings = true;
                        menu = false;
                        continue;
                    } else if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 200 && y <= SCREEN_HEIGHT / 3 + 250) {
                        Window::Mixer("click.wav");
                        quit = true;
                        continue;
                    }
                }
            }

            Window::RenderMenu("Play", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3, 300 , 50);
            Window::RenderMenu("Score Rankings", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 100, 300 , 50);
            Window::RenderMenu("Exit", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 200, 300 , 50);
            Window::show();
        }

        if (rankings){
            std::ifstream file(SCORES_FILE);
            std::string player[10];
            int score, i = 0, scores[10];
            if (file.is_open()) {
                std::string name;
                while (file >> name >> score) {
                    player[i] = name;
                    scores[i++] = score;
                }
                file.close();
            } else {
                std::cerr << "Failed to open file for reading!" << std::endl;
                rankings = false;
                quit = true;
            }

            Window::RenderFrame(SCREEN_WIDTH / 4 - 10, 165 , SCREEN_WIDTH / 2 + 25,180);
            Window::RenderMenu("Ranking score", SCREEN_WIDTH / 2 - 150, 120, 300,45);
            for (int i = 0; i < 5; i++){
                Window::RenderText(player[i],SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4 + 30 * i);
            }
            for (int i = 0; i < 5; i++){
                std::string stringscore = std::to_string(scores[i]);
                Window::RenderText(stringscore,3*SCREEN_WIDTH / 4 - stringscore.size() * 15,SCREEN_HEIGHT / 4 + 30 * i);
            }
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                    menu = false;
                    continue;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 150 && y <= SCREEN_HEIGHT / 3 + 200) {
                        Window::Mixer("click.wav");
                        menu = true;
                        rankings = false;
                        continue;
                    }else   if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 225 && y <= SCREEN_HEIGHT / 3 + 275) {
                        Window::Mixer("click.wav");
                        quit = true;
                        rankings = false;
                        continue;
                    }
                }
            }
            Window::RenderMenu("Menu", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 150, 300 , 50);
            Window::RenderMenu("Exit", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 225, 300 , 50);
            Window::show();
        }

        if (endgame){
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                    endgame = false;
                    continue;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 100 && y <= SCREEN_HEIGHT / 3 + 150) {
                        Window::Mixer("click.wav");
                        sname = true;
                        blood = 3;
                        level = 1;
                        endgame = false;
                        iscout = true;
                        figure.Clear();
                        continue;
                    } else  if (x >= SCREEN_WIDTH / 2 - 150 && x <= SCREEN_WIDTH / 2 + 150 && y >= SCREEN_HEIGHT / 3 + 200 && y <= SCREEN_HEIGHT / 3 + 250) {
                        Window::Mixer("click.wav");
                        menu = true;
                        endgame = false;
                        continue;
                    }
                }
            }

            std::string s = "Your score is " + std::to_string(figure.GetScore());
            Window::RenderText(s, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3);
            Window::RenderMenu("Play again", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 100, 300 , 50);
            Window::RenderMenu("Menu", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 200, 300 , 50);
            Window::show();
        }

        if (sname){
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }else   if (event.type == SDL_TEXTINPUT) {
                    yourname += event.text.text;
                }else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_BACKSPACE && !yourname.empty()) {
                        yourname.pop_back();
                    }else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                        if (yourname.find(' ') < yourname.size() || yourname.size() > 10){
                            yourname = "";
                            continue;
                        }
                        play = true;
                        sname = false;
                    }
                }
            }
            if (yourname.size() > 10)
                if (yourname.size() > 15)
                    yourname = "";
                else
                    Window::RenderText("Your name cannot exceed 10 characters", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3);
            else    if (yourname.find(' ') < yourname.size())
                Window::RenderText("The name cannot contain spaces", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3);
            else
                Window::RenderText("Please enter your name", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3);
            if (yourname.size() > 0)
                Window::RenderMenu(yourname, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 100, 300 , 50);
            else
                Window::RenderFrame(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 3 + 100, 300 , 50);
            Window::show();
        }

        if (play){
            if (blood == 0){
                Window::resetRanking(yourname,figure.GetScore());
                yourname = "";
                play = false;
                endgame = true;
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
                    std::string s = "Level " + std::to_string(level);
                    Window::RenderText(s, (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
                    Window::show();
                    man1Time = SDL_GetTicks();
                    SDL_Delay(3000);
                }
                endTime = SDL_GetTicks();
                if (endTime - man1Time >= 20000){
                    check = figure.AppearChicken();
                    if (check){
                        SDL_Delay(500);
                        level ++;
                        iscout = true;
                        check = false;
                    }
                }else
                    figure.MoveChickens1();
            }else   if (man == 2){
                if (iscout){
                    iscout = false;
                    std::string s = "Level " + std::to_string(level);
                    figure.SetTime(-20);
                    Window::RenderText(s, (SCREEN_WIDTH - 150) / 2, (SCREEN_HEIGHT - 50) / 2);
                    Window::show();
                    SDL_Delay(3000);
                }
                figure.MoveChickens2();
                if (figure.CheckChickens() && figure.GetTime() >= MAX_TIME){
                    check = figure.AppearChicken();
                    if (check){
                        SDL_Delay(500);
                        level ++;
                        iscout = true;
                        check = false;
                    }
                }
            }else{
                if (iscout){
                    bossHealth = BOSS_HEALTH * level / 3;
                    boss.Reset();
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
                            if (blood > 0)
                                isshield = true;
                        }
                    }
                    bossHealth -= figure.CheckBoss(bossRect);
                    if (bossHealth <= 0)
                        Window::Mixer("boss.wav");
                    if (rand() % 500 < 5) {
                        figure.AddEgg({bossRect.x + (BOSS_WIDTH - EGG_WIDTH) / 2,bossRect.y + BOSS_HEIGHT - 50,bossRect.w,bossRect.h});
                    }
                    Window::RenderBloodBar(100,10,SCREEN_WIDTH-200,30,bossHealth,BOSS_HEALTH * level / 3);
                    Window::RenderTexture(bossTexture,bossRect.x,bossRect.y,BOSS_WIDTH,BOSS_HEIGHT);
                }
                if (bossHealth <= 0){
                    check = figure.AppearChicken();
                    if (check){
                        SDL_Delay(500);
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
                if (blood > 0)
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


#ifndef WINDOW_H_
#define WINDOW_H_
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <bits/stdc++.h>
#include <ctime>
#include <cstdlib>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const int CHICKEN_WIDTH = 50;
const int CHICKEN_HEIGHT = 100;
const int EGG_WIDTH = 10;
const int EGG_HEIGHT = 30;
const int BOSS_WIDTH = 300;
const int BOSS_HEIGHT = 300;
const int BOSS_HEALTH = 30;
const int BULLET_WIDTH = 8;
const int BULLET_HEIGHT = 20;
const int MAX_HEALTH = 1;
const int SPEED = 40;
const int BOSS_SPEED = 5;
const int MAX_TIME = 600;
const std::string SCORES_FILE = "rankscore.txt";

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Texture* backgroundTexture = NULL;
static TTF_Font* gFont = NULL;
static Mix_Chunk *soundEffect;

namespace Window
{
    bool init();
    SDL_Texture* LoadTexture(const std::string& filePath);
    void Mixer(const std::string& text);
    void RenderTexture(SDL_Texture* texture, int x, int y, int w, int h);
    void show();
    void close();
    void RenderText(const std::string& text, int x, int y);
    void RenderFrame(int x, int y, int w, int h);
    void RenderBloodBar(int x, int y, int width, int height, int currentHP, int maxHP);
    void RenderMenu(const std::string& text, int x, int y, int w, int h);
    void RenderItem(const std::string& text, int x, int y, int number);
    void resetRanking(std::string newname, int score);
}
#endif

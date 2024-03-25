
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BIRD_WIDTH = 50;
const int BIRD_HEIGHT = 50;
const int PIPE_WIDTH = 100;
const int MIN_PIPE_HEIGHT = 50; // Chiều cao tối thiểu của ống
const int MAX_PIPE_HEIGHT = 300; // Chiều cao tối đa của ống
const int PIPE_GAP = 250; // Khoảng cách giữa các cặp ống nước
const int PIPE_SPEED = 3;
const int GRAVITY = 1;  //
const int JUMP_FORCE = 10;

struct Bird {
    int x, y;
    int velocity;
    bool pause;
};

struct Pipe {
    int x, y;
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Bird bird;
Pipe pipes[2];
int score;
SDL_Texture* backgroundTexture = NULL;
SDL_Texture* birdTexture = NULL;
SDL_Texture* pipeTexture = NULL;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Load background image
    SDL_Surface* backgroundSurface = IMG_Load("background.jpg");
    if (backgroundSurface == NULL) {
        std::cout << "Failed to load background image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    backgroundTexture = SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Load bird image
    SDL_Surface* birdSurface = IMG_Load("plane.png");
    if (birdSurface == NULL) {
        std::cout << "Failed to load bird image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    birdTexture = SDL_CreateTextureFromSurface(gRenderer, birdSurface);
    SDL_FreeSurface(birdSurface);

    // Load pipe image
    SDL_Surface* pipeSurface = IMG_Load("chicken.jpg");
    if (pipeSurface == NULL) {
        std::cout << "Failed to load pipe image! SDL_Error: " << IMG_GetError() << std::endl;
        return false;
    }
    pipeTexture = SDL_CreateTextureFromSurface(gRenderer, pipeSurface);
    SDL_FreeSurface(pipeSurface);
    bird.x = SCREEN_WIDTH / 4;
    bird.y = SCREEN_HEIGHT / 2;
    bird.velocity = 0;
    bird.pause = false;
    pipes[0].x = SCREEN_WIDTH;
    pipes[1].x = SCREEN_WIDTH + SCREEN_WIDTH / 2; // Tạo ống thứ hai ở xa hơn
    pipes[0].y = rand() % (SCREEN_HEIGHT - MAX_PIPE_HEIGHT - MIN_PIPE_HEIGHT) + MIN_PIPE_HEIGHT; // Tạo ống ngẫu nhiên
    pipes[1].y = rand() % (SCREEN_HEIGHT - MAX_PIPE_HEIGHT - MIN_PIPE_HEIGHT) + MIN_PIPE_HEIGHT;
    score = 0;
    return true;
}

void close() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE) {
                bird.velocity = -JUMP_FORCE;
                bird.pause = true;
            }
        }
    }
}

void update() {
    if (!bird.pause){
        return;
    }
    bird.velocity += GRAVITY;
    bird.y += bird.velocity;
    for (int i = 0; i < 2; ++i) {
        pipes[i].x -= PIPE_SPEED;
        if (pipes[i].x < -PIPE_WIDTH) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].y = rand() % (SCREEN_HEIGHT - MAX_PIPE_HEIGHT - MIN_PIPE_HEIGHT) + MIN_PIPE_HEIGHT; // Tạo lại ống ngẫu nhiên
            score++;
        }
    }

    if (bird.y < 0 || bird.y > SCREEN_HEIGHT - BIRD_HEIGHT) {
        std::cout << "Game Over! Score: " << score << std::endl;
        SDL_Delay(2000);
        exit(0);
    }

    for (int i = 0; i < 2; ++i) {
        if ((bird.x + BIRD_WIDTH > pipes[i].x && bird.x < pipes[i].x + PIPE_WIDTH) &&
            (bird.y < pipes[i].y || bird.y + BIRD_HEIGHT > pipes[i].y + PIPE_GAP)) {
            std::cout << "Game Over! Score: " << score << std::endl;
            SDL_Delay(2000);
            exit(0);
        }
    }
}

void render() {
    SDL_RenderClear(gRenderer);

    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, &backgroundRect);

    SDL_Rect birdRect = { bird.x, bird.y, BIRD_WIDTH, BIRD_HEIGHT };
    SDL_RenderCopy(gRenderer, birdTexture, NULL, &birdRect);

    for (int i = 0; i < 2; ++i) {
        SDL_Rect upperPipeRect = { pipes[i].x, 0, PIPE_WIDTH, pipes[i].y };
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &upperPipeRect);

        SDL_Rect lowerPipeRect = { pipes[i].x, pipes[i].y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - pipes[i].y - PIPE_GAP };
        SDL_RenderCopy(gRenderer, pipeTexture, NULL, &lowerPipeRect);
        }

        SDL_RenderPresent(gRenderer);
    }

int main(int argc, char* args[]) {
        if (!init()) {
            std::cout << "Failed to initialize!" << std::endl;
            return -1;
        }
        bool quit = false;
        while (!quit) {
            handleEvents(quit);
            update();
            render();
            SDL_Delay(10);
        }

        close();
        return 0;
    }

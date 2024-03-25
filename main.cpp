#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "CommonFunction.h"

#define WIDTH_MAIN_OBJECT 80
#define HEIGHT_MAIN_OBJECT 46
using namespace std;

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

#include <iostream>
#include "renderer.h"
#include "controller.h"
#include "game.h"
#include <ctime>
#include <chrono>

int main(){
    //values for the game
    srand((unsigned) time(0));
    constexpr std::size_t KFps {60};
    constexpr std::size_t KMsPerFrame {1000/ KFps};
    constexpr std::size_t KScreen_width{640};
    constexpr std::size_t KScreen_height{640};
    constexpr std::size_t KGrid_width{32};
    constexpr std::size_t KGrid_height{32};

    Renderer renderer(KScreen_width, KScreen_width, KGrid_width, KGrid_width);
    Controller controller;
    Game game(KGrid_width, KGrid_height);
    game.Run(controller, renderer, KMsPerFrame);
    return 0;
}


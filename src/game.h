#ifndef GAME_H
#define GAME_H

#define     WALKERS     20

#include "character.h"
#include "renderer.h"
#include "controller.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <memory>



class Game {
    public:
        Game(std::size_t grid_width, std::size_t grid_height);
        ~Game();
        void Run(Controller const &controller,
               Renderer &renderer,
               std::size_t frame_duration);
        std::size_t GetWidth() {return grid_width;}
        std::size_t GetHeight() {return grid_height;}
        bool position_used(int x, int y);
        

    private:
        void Update();
        Character* character;
        std::vector<   std::unique_ptr<Walker>   > walker_vector;
        std::size_t grid_width;
        std::size_t grid_height;

};

#endif
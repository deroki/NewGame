#ifndef CHARACTER_H
#define CHARACTER_H

class Game;

#include "SDL.h"

class Character{
    public:
        enum class Direction { KUp, KDown, KLeft, KRight};
        Character(int grid_width, int grid_height, Game* game);
        SDL_Point GetPosition() {return position;}
        void move(Direction direction);


        //float speed{0.1f};

    private:
        void Impact();
        SDL_Point position;
        Game* _game;

};

#endif
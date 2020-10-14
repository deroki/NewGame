#ifndef CHARACTER_H
#define CHARACTER_H

#include "SDL.h"

class Character{
    public:
        enum class Direction { KUp, KDown, KLeft, KRight};
        Character(int grid_width, int grid_height);
        SDL_Point GetPosition() {return position;}
        void move(Direction direction);


        //float speed{0.1f};

    private:
        void Impact();
        SDL_Point position;

};

#endif
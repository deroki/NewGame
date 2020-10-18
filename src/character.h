#ifndef CHARACTER_H
#define CHARACTER_H

class Game;

#include "SDL.h"
#include <thread>


#define     FORWARD     1
#define     BACKWARD    2    


class Character{
    public:
        enum class Direction { KUp, KDown, KLeft, KRight};
        Character(Game* game);
        SDL_Point GetPosition() {return position;}
        void move(Direction direction);


        //float speed{0.1f};

    protected:
        SDL_Point position;
        Game* _game;
    
    private:
        int score;
};

class Walker : public Character{
    public: 
        Walker(Game* game);
        ~Walker();
        void Start_walking_thread();

    private:
        std::thread* Movement_Thread;
        void Walking_loop();
        void Random_movement();
        void walk_steps_to_direction(int num_steps, Direction direction);

};
#endif
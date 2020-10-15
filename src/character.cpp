#include "character.h"
#include "game.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

Character::Character(Game* game){
    position.x = game->GetHeight() / 2;
    position.y = game->GetWidth() / 2;
    _game = game;
}

//TODO: check if the char impacts against another characters
void Character::move(Direction direction){
    int height = static_cast<int>(_game->GetHeight());
    int  width = static_cast<int>(_game->GetWidth());
    switch (direction)
    {
    case Direction::KUp:
        if (position.y >= 1 )
            position.y--;
        break;
    case Direction::KDown:
        if ( position.y < height - 1 ){
            position.y++;
        }
        break;
    case Direction::KLeft:
        if (position.x >= 1 )
            position.x--;
        break;
    case Direction::KRight:
        if (position.x < width - 1 )
            position.x++;
        break;
    
    default:
        break;
    }
}

// =================================== WALKER ================================== //
// we call the character mother class constructor in a initialized class
Walker::Walker(Game* game):Character(game){
    //random initial position
    srand((unsigned) time(0));
    int x = ( rand() % game->GetHeight() ) + 1;
    int y = ( rand() % game->GetWidth() ) + 1;
    position.x = x;
    position.y = y;
    _game = game;
}

Walker::~Walker(){
}

void Walker::Start_walking_thread(){
    Movement_Thread = new std::thread(&Walker::Walking_loop, this);
}

void Walker::Walking_loop(){
    while(true){
        Random_movement();
    }
}

void Walker::Random_movement(){
    srand((unsigned) time(0));
    int random_number = (rand() % 4) + 1;
    int random_steps = (rand() % 4) + 1;
    switch(random_number){
        case 1:
            walk_steps_to_direction(random_steps, Direction::KUp);
            break;
        case 2:
            walk_steps_to_direction(random_steps, Direction::KDown);
            break;
        case 3:
            walk_steps_to_direction(random_steps, Direction::KLeft);
            break;
        case 4:
            walk_steps_to_direction(random_steps, Direction::KRight);
            break;
        default:
            break;
    }
}

//TODO does it moves ok in the edges?
void Walker::walk_steps_to_direction(int num_steps, Direction direction){
    for (int i = 0; i < num_steps; i++){
        switch(direction){
            case Direction::KUp:
                position.y--;
                break;
            case Direction::KDown:
                position.y++;
                break;
            case Direction::KLeft:
                position.x--;
                break;
            case Direction::KRight:
                position.x++;
                break;
        }
        if (direction == Direction::KDown || direction == Direction::KUp){
            if (position.y == _game->GetHeight() + 1 ) 
                position.y = 1;
            if (position.y == -1) 
                position.y = _game->GetHeight();
        }   
        if (direction == Direction::KLeft || direction == Direction::KRight){
            if (position.x == _game->GetWidth() + 1 ) 
                position.x = 1;
            if (position.x == -1) 
                position.x = _game->GetWidth();
        }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
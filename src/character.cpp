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
    int x = position.x;
    int y = position.y;

    switch (direction)
    {
    case Direction::KUp:
        if (y >= 1 )
            y--;
        break;
    case Direction::KDown:
        if ( y < height - 1 ){
            y++;
        }
        break;
    case Direction::KLeft:
        if (x >= 1 )
            x--;
        break;
    case Direction::KRight:
        if (x < width - 1 )
            x++;
        break;
    
    default:
        break;
    }
    if( !_game->position_used(x, y)){
        position.x = x;
        position.y = y;
    }
}



// =================================== WALKER ================================== //
// we call the character mother class constructor in a initialized class
Walker::Walker(Game* game):Character(game){
    int x = ( rand() % game->GetHeight() ) + 1;
    int y = ( rand() % game->GetWidth() ) + 1;
    position.x = x;
    position.y = y;
    _game = game;
}

Walker::~Walker(){
    delete Movement_Thread;
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
    int x = position.x;
    int y = position.y;
    for (int i = 0; i < num_steps; i++){
        switch(direction){
            case Direction::KUp:
                y--;
                break;
            case Direction::KDown:
                y++;
                break;
            case Direction::KLeft:
                x--;
                break;
            case Direction::KRight:
                x++;
                break;
        }
        if (direction == Direction::KDown || direction == Direction::KUp){
            if (y == _game->GetHeight() + 1 ) 
                y = 1;
            if (y == -1) 
                y = _game->GetHeight();
        }   
        if (direction == Direction::KLeft || direction == Direction::KRight){
            if (x == _game->GetWidth() + 1 ) 
                x = 1;
            if (x == -1) 
                x = _game->GetWidth();
        }
        if( !_game->position_used(x, y)) {
        position.x = x;
        position.y = y;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
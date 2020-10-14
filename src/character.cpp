#include "character.h"

Character::Character(int grid_width, int grid_height){
    //TODO change initial the position 
    position.x = grid_width / 2;
    position.y = grid_height / 2;
}

//TODO: check if the char impacts against another characters
void Character::move(Direction direction){
    switch (direction)
    {
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
    
    default:
        break;
    }
}
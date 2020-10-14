#include "character.h"
#include "game.h"

Character::Character(int grid_width, int grid_height, Game* game){
    //TODO change initial the position 
    position.x = grid_width / 2;
    position.y = grid_height / 2;
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
        if ( position.y <= height - 1 ){
            position.y++;
        }
        break;
    case Direction::KLeft:
        if (position.x >= 1 )
            position.x--;
        break;
    case Direction::KRight:
        if (position.x <= width - 1 )
            position.x++;
        break;
    
    default:
        break;
    }
}
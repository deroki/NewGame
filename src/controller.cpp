#include "controller.h"
#include "character.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(Character &character, bool &running) const
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                character.move(Character::Direction::KUp);
                break;

            case SDLK_DOWN:
                character.move(Character::Direction::KDown);
                break;

            case SDLK_LEFT:
                character.move(Character::Direction::KLeft);
                break;

            case SDLK_RIGHT:
                character.move(Character::Direction::KRight);
                break;
            }
        }
    }
}

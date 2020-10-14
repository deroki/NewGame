#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : grid_height(grid_height),
      grid_width(grid_width)
    {character = new Character(this);
    }

void Game::Run(Controller const &controller,
               Renderer &renderer,
               std::size_t frame_duration){
                   
    bool running = true;

    while(running){
        Uint32 start_time = SDL_GetTicks();
        //control - update - render  Loop
        controller.HandleInput(*character, running);
        Update();
        renderer.Render(*character);
        Uint32 end_time = SDL_GetTicks();
        //wait if the loop run faster than the fps desired
        Uint32 dif_time = end_time - start_time;
        if( dif_time < frame_duration){
            SDL_Delay(frame_duration - dif_time);
        }

    }
}

void Game::Update(){

}
#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
                                                            : grid_height(grid_height),
                                                            grid_width(grid_width)
    {
        character = new Character(this);
        //add walkers
        for (int i=0; i<WALKERS; i++){
            std::unique_ptr<Walker> newWalker (new Walker(this));
            newWalker->Start_walking_thread();
            walker_vector.emplace_back(std::move(newWalker));
        }

    }

Game::~Game(){
    delete character;
}


void Game::Run(Controller const &controller,
               Renderer &renderer,
               std::size_t frame_duration){
                   
    bool running = true;

    while(running){
        Uint32 start_time = SDL_GetTicks();
        //control - update - render  Loop
        controller.HandleInput(*character, running);
        renderer.Render(*character, walker_vector) ;
        Uint32 end_time = SDL_GetTicks();
        //wait if the loop run faster than the fps desired
        Uint32 dif_time = end_time - start_time;
        if( dif_time < frame_duration){
            SDL_Delay(frame_duration - dif_time);
        }

    }
}

bool Game::position_used(int x, int y){
    if ( x == character->GetPosition().x && y == character->GetPosition().y ) {
        return true;
    } else {
        for ( std::unique_ptr<Walker>& walker : walker_vector){
            if ( x == walker->GetPosition().x && y == walker->GetPosition().y ){
                return true;
            }
        }
    }
}
#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
                                                            : grid_height(grid_height),
                                                            grid_width(grid_width)
    {
        character = new Character(this);
        //add walkers
        int walkers = user_input();
        for (int i=0; i<walkers; i++){
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
        renderer.UpdateWindowTitle(score);
        Uint32 start_time = SDL_GetTicks();
        //control - update - render  Loop
        controller.HandleInput(*character, running);
        renderer.Render(*character, walker_vector) ;
        //Here we calculate the time passed til the score calculation
        //TODO: every second not every loop cycle
        calculate_health((float)frame_duration/1000.0f);
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
    return false;
}

void Game::calculate_health(float seconds){
    std::vector<std::thread> thread_vector;
    for (auto& walker_ptr : walker_vector){
        std::thread score_th(&Game::calculate_health_thread, this, walker_ptr->GetPosition().x,
                                walker_ptr->GetPosition().y, seconds);
        thread_vector.emplace_back(std::move(score_th));
    }
    //wait til all finish
    for (auto& th : thread_vector){
        th.join();
    }

}

void Game::calculate_health_thread(int x, int y, float delta_time){
    float partial_score;
    int x_dif = character->GetPosition().x - x;
    int y_dif = character->GetPosition().y - y;
    float distance = sqrt( pow(x_dif, 2) + pow(y_dif, 2) );
    partial_score = CONSTANT * delta_time/pow(distance, 2);
    score = score + partial_score;
}

int Game::user_input(){
    int walkers;
     std::cout << "   _____  _______ __   _ ______  _______ _______ _____ _______       ______  _____   _____  _______ \n";
     std::cout << "   |_____] |_____| | \\  | |     \\ |______ |  |  |   |   |            |_____/ |     | |     | |  |  |\n";
     std::cout << "   |       |     | |  \\_| |_____/ |______ |  |  | __|__ |_____       |    \\_ |_____| |_____| |  |  |\n";
     std::cout << "\n\n\n";
     std::cout << "Insert the number of walkers";
     std::cout << "\n\n\n";
     std::cin >> walkers;
     return walkers;

                                                                                          
}
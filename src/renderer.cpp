#include "renderer.h"
#include <iostream>
#include <string>
#include "character.h"
#include "renderer.h"


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width,
                   const std::size_t grid_height):
                   // initialization list
                   screen_width(screen_width),
                   screen_heigth(screen_height),
                   grid_width(grid_width),
                   grid_height(grid_height)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Pandemic room", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}                


Renderer::~Renderer(){
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Character character,  std::vector< std::unique_ptr<Walker> >& walker_vec){
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_heigth / grid_height;

     // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    //render my character
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    block.x = character.GetPosition().x * block.w;
    block.y = character.GetPosition().y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    //render walker vector
    for (auto &walker : walker_vec){
      SDL_SetRenderDrawColor(sdl_renderer, 255, 233, 0, 0xFF);
      block.x = walker->GetPosition().x * block.w;
      block.y = walker->GetPosition().y * block.h;
      SDL_RenderFillRect(sdl_renderer, &block);

    }

    //Update Screen
    SDL_RenderPresent(sdl_renderer);

}

void Renderer::UpdateWindowTitle(float score, int fps){
    std::string title{"Viral load" + std::to_string(score) + "FPS" + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::UpdateWindowTitle(float score){
    std::string title{"Viral load    " + std::to_string(score)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}
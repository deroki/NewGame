#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "character.h"

class Renderer {
    public:
        Renderer(const std::size_t screen_width, const std::size_t screen_height,
                 const std::size_t grid_width, const std::size_t grid_height);
        ~Renderer();

        void Render(Character character, std::vector< std::unique_ptr<Walker> >& walker_vec);
        void UpdateWindowTitle(float score, int fps);
        void UpdateWindowTitle(float score);

    private:
        SDL_Window* sdl_window;
        SDL_Renderer* sdl_renderer;

        const std::size_t screen_width;
        const std::size_t screen_heigth;
        const std::size_t grid_width;
        const std::size_t grid_height;
};


#endif
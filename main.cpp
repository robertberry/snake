#define SDL_MAIN_HANDLED

#include <iostream>
#include <random>
#include <string>
#include <SDL2/SDL.h>

#include "constants.h"
#include "SnakeRenderer.h"
#include "Vector2i.h"

constexpr int kFps = 60;
constexpr int kMsPerFrame = 1000 / kFps;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool done = false;
    SDL_Event e;

    snake::GameState game_state = snake::GameState::Init();
    const snake::SnakeRenderer snake_renderer(*renderer, game_state);

    while (!done) {
        const Uint32 frame_start = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                done = true;
            }

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        game_state.set_requested_direction(UP);
                        break;
                    case SDLK_DOWN:
                        game_state.set_requested_direction(DOWN);
                        break;
                    case SDLK_LEFT:
                        game_state.set_requested_direction(LEFT);
                        break;
                    case SDLK_RIGHT:
                        game_state.set_requested_direction(RIGHT);
                        break;
                    default:
                        // Do nothing.
                            ;
                }
            }
        }

        game_state.Tick();
        snake_renderer.Draw();

        if (const Uint32 time_spent = SDL_GetTicks() - frame_start; time_spent < kMsPerFrame) {
            SDL_Delay(kMsPerFrame - time_spent);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

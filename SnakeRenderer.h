#ifndef SNAKERENDERER_H
#define SNAKERENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GameState.h"

namespace snake {

// Handles rendering the GameState to the SDL buffer.
class SnakeRenderer {
  public:
    SnakeRenderer(SDL_Renderer& renderer, GameState& game_state, TTF_Font& game_over_font) :
        renderer_(renderer), game_state_(game_state), game_over_font_(game_over_font) {}

    // Should be called every frame to update the screen.
    void Draw() const;

 private:
    void DrawGrid() const;
    void DrawSnake() const;
    void DrawFood() const;
    void DrawGameOver() const;

    SDL_Renderer& renderer_;
    TTF_Font& game_over_font_;
    GameState& game_state_;
};

}  // namespace snake

#endif //SNAKERENDERER_H

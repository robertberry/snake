#ifndef SNAKERENDERER_H
#define SNAKERENDERER_H

#include <SDL2/SDL.h>

#include "GameState.h"

namespace snake {

class SnakeRenderer {
  public:
    SnakeRenderer(SDL_Renderer& renderer, GameState& game_state) : renderer_(renderer), game_state_(game_state) {}

    void Draw() const;

 private:
    void DrawGrid() const;
    void DrawSnake() const;
    void DrawFood() const;

    SDL_Renderer& renderer_;
    GameState& game_state_;
};

}  // namespace snake

#endif //SNAKERENDERER_H

#include "SnakeRenderer.h"

namespace snake {

void SnakeRenderer::Draw() const {
    SDL_RenderClear(&renderer_);
    DrawGrid();
    DrawSnake();
    DrawFood();
    SDL_RenderPresent(&renderer_);
}

void SnakeRenderer::DrawGrid() const {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (const Cell cell = game_state_.grid_[i][j]; cell == Cell::WALL) {
                SDL_SetRenderDrawColor(&renderer_, 0, 30, 255, 255);
            } else {
                SDL_SetRenderDrawColor(&renderer_, 0, 0, 0, 255);
            }
            SDL_Rect rect = {.x = j * CELL_WIDTH, .y = i * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH };
            SDL_RenderFillRect(&renderer_, &rect);
        }
    }
}

void SnakeRenderer::DrawSnake() const {
    for (auto segment : game_state_.snake_) {
        SDL_Rect rect = {.x = segment.x() * CELL_WIDTH, .y = segment.y() * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH };
        SDL_SetRenderDrawColor(&renderer_, 200, 0, 0, 255);
        SDL_RenderFillRect(&renderer_, &rect);
    }
}

void SnakeRenderer::DrawFood() const {
    const Vector2i& food_pos = game_state_.food_pos_;
    const SDL_Rect rect = {.x = food_pos.x() * CELL_WIDTH, .y = food_pos.y() * CELL_WIDTH, .w = CELL_WIDTH, .h = CELL_WIDTH };
    SDL_SetRenderDrawColor(&renderer_, 0, 155, 0, 255);
    SDL_RenderFillRect(&renderer_, &rect);
}

}  // namespace snake

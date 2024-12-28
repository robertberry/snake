#include "SnakeRenderer.h"

namespace snake {

void SnakeRenderer::Draw() const {
    SDL_RenderClear(&renderer_);
    DrawGrid();
    DrawSnake();
    DrawFood();
    if (game_state_.is_game_over_) {
        DrawGameOver();
    }
    SDL_RenderPresent(&renderer_);
}

void SnakeRenderer::DrawGameOver() const {
    SDL_Surface* message_surface = TTF_RenderText_Solid(&game_over_font_, "Game Over", SDL_Color{255, 255, 255});
    SDL_Texture* message_texture = SDL_CreateTextureFromSurface(&renderer_, message_surface);
    const int left = (SCREEN_WIDTH - message_surface->w) / 2;
    const int top = (SCREEN_HEIGHT - message_surface->h) / 2;
    const SDL_Rect message_rect = {left, top, message_surface->w, message_surface->h};
    SDL_RenderCopy(&renderer_, message_texture, /*srcrect=*/ nullptr, &message_rect);
    SDL_FreeSurface(message_surface);
    SDL_DestroyTexture(message_texture);
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

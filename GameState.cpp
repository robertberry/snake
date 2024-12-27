#include "GameState.h"

#include <bitset>
#include <optional>
#include <random>
#include <vector>

#include "Vector2i.h"

namespace snake {

GameState GameState::Init() {
    Snake snake;
    constexpr Vector2i center = Vector2i(/*x=*/ COLUMNS / 2, /*y=*/ ROWS / 2);
    snake.push_front(center);
    const Grid grid = MakeGrid();
    GameState state = {grid, snake, center};
    state.MoveFoodToRandomSpace();
    return state;
}

std::vector<Vector2i> GameState::GetEmptySpaces() {
    std::bitset<ROWS * COLUMNS> candidates;
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (grid_[y][x] == Cell::EMPTY) {
                candidates[y * COLUMNS + x] = true;
            } else {
                candidates[y * COLUMNS + x] = false;
            }
        }
    }
    for (const auto segment : snake_) {
        candidates[segment.y() * COLUMNS + segment.x()] = false;
    }
    std::vector<Vector2i> empty_spaces;
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            if (candidates[y * COLUMNS + x]) {
                empty_spaces.emplace_back(x, y);
            }
        }
    }
    return empty_spaces;
}

std::optional<Vector2i> GameState::GetRandomEmptySpace() {
    const std::vector<Vector2i> empty_spaces = GetEmptySpaces();
    if (empty_spaces.empty()) {
        return std::nullopt;
    }
    std::random_device rng;
    std::mt19937 generator(rng());
    std::uniform_int_distribution<int> distribution(0, empty_spaces.size() - 1);
    const int random_index = distribution(generator);
    return empty_spaces[random_index];
}

void GameState::MoveFoodToRandomSpace() {
    // TODO: Handle case when there are no empty spaces. This will currently crash.
    food_pos_ = *GetRandomEmptySpace();
}

Vector2i GameState::NextPositionOfHead() const {
    // Crash OK: Snake should never be empty.
    const auto segment = *snake_.front();
    return {/*x=*/ segment.x() + direction_.x(), /*y=*/ segment.y() + direction_.y()};
}

bool GameState::WillHaveDeadlyCollision() {
    const Vector2i next_position_of_head = NextPositionOfHead();
    for (auto segment : snake_) {
        if (next_position_of_head == segment) {
            return true;
        }
    }
    return grid_[next_position_of_head.y()][next_position_of_head.x()] == Cell::WALL;
}

void GameState::MoveSnake() {
    if (snake_.empty()) {
        return;
    }
    const auto segment = *snake_.front();
    if (is_growing_) {
        is_growing_ = false;
    } else {
        snake_.pop_back();
    }
    snake_.push_front(Vector2i(segment.x() + direction_.x(), segment.y() + direction_.y()));
}

void GameState::IncreaseMovementSpeed() {
    if (const int frames_per_movement = movement_timer_.get_frames_per_event(); frames_per_movement > MIN_FRAMES_PER_MOVEMENT) {
        movement_timer_.set_frames_per_event(frames_per_movement - 1);
    }
}

void GameState::Tick() {
    if (is_dead_) {

    } else if (movement_timer_.Tick()) {
        // The snake can only turn to its left or right, not do a full 180 in a frame.
        if (requested_direction_ != direction_.negative()) {
            direction_ = requested_direction_;
        }
        if (WillHaveDeadlyCollision()) {
            is_dead_ = true;
        } else {
            MoveSnake();
            if (snake_.front() == food_pos_) {
                // Grow next movement tick
                is_growing_ = true;
                MoveFoodToRandomSpace();
                IncreaseMovementSpeed();
            }
        }
    }
}

}  // namespace snake

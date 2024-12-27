#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "FrameTimer.h"
#include "Grid.h"
#include "Snake.h"
#include "Vector2i.h"

namespace snake {

constexpr int INITIAL_FRAMES_PER_MOVEMENT = 20;
constexpr int MIN_FRAMES_PER_MOVEMENT = 5;

class SnakeRenderer;

class GameState {
public:

  // Called once per frame.
  void Tick();

  void set_requested_direction(Vector2i direction) {
    requested_direction_ = direction;
  }

  static GameState Init();

  friend class SnakeRenderer;

private:
  GameState(const Grid &grid, Snake snake, const Vector2i food_pos) :
    grid_(grid), snake_(snake), food_pos_(food_pos), requested_direction_(UP), direction_(UP), movement_timer_(INITIAL_FRAMES_PER_MOVEMENT) {}

  std::vector<Vector2i> GetEmptySpaces();
  std::optional<Vector2i> GetRandomEmptySpace();
  void MoveFoodToRandomSpace();

  [[nodiscard]] Vector2i NextPositionOfHead() const;
  bool WillHaveDeadlyCollision();
  void MoveSnake();
  void IncreaseMovementSpeed();

  FrameTimer movement_timer_;
  Grid grid_;
  Snake snake_;
  Vector2i food_pos_;
  Vector2i requested_direction_;
  Vector2i direction_;
  bool is_growing_ = false;
  bool is_dead_ = false;
};

}  // namespace snake

#endif //GAMESTATE_H

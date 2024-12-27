#ifndef SNAKE_H
#define SNAKE_H

#include "constants.h"
#include "RingBuffer.h"
#include "Vector2i.h"

using Snake = snake::RingBuffer<Vector2i, COLUMNS * ROWS>;

#endif //SNAKE_H

#ifndef GRID_H
#define GRID_H

#include <array>

#include "constants.h"

enum class Cell {
    EMPTY,
    WALL,
};

using Grid = std::array<std::array<Cell, COLUMNS>, ROWS>;

inline Grid MakeGrid() {
    Grid grid {};
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (i == 0 || j == 0 || i == ROWS - 1 || j == COLUMNS - 1) {
                grid[i][j] = Cell::WALL;
            } else {
                grid[i][j] = Cell::EMPTY;
            }
        }
    }
    return grid;
}

#endif //GRID_H

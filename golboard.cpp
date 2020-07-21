#include <cassert>
#include <iostream>
#include "golboard.h"

// parameterized constructor
GOLBoard::GOLBoard(int height, int width, bool* board) {
    this->height = height;
    this->width = width;
    this->board = board;
    this->gen = 0;
}
// destructor
GOLBoard::~GOLBoard() {
    this->height = 38;
    this->width = 38;
    this->gen = 0;

    bool *board;
    board = new bool[38*38];
    this->board = board;
}

// private member return functions
int GOLBoard::get_height() {
    return this->height;
}
int GOLBoard::get_width() {
    return this->width;
}
int GOLBoard::get_generation() {
    return this->gen;
}
bool* GOLBoard::get_board() {
    return this->board;
}
bool GOLBoard::get_cell(int i, int j) {
    return this->board[(j * this->width) + i];
}

// private member setter functions
void GOLBoard::set_height(int height) {
    this->height = height;
}
void GOLBoard::set_width(int width) {
    this->width = width;
}
void GOLBoard::set_generation(int gen) {
    this->gen = gen;
}
void GOLBoard::set_board(bool* board) {
    this->board = board;
}
void GOLBoard::set_cell(int i, int j, bool cell) {
    this->board[(j * this->width) + i] = cell;
}

int GOLBoard::_neighbors(int i, int j) {
    int n = 0;

    // from i-1 to i+1
    for (int x = i-1; x <= i+1; x++) {
        // from j-1 to j+1
        for (int y = j-1; y <= j+1; y++) {
            // excluding (i, j)
            if (!(x == i && y == j)) {
                // if i is within the board bounds
                if (x >= 0 && x < this->width) {
                    // and if j is within the board bounds
                    if (y >= 0 && y < this->height) {
                        // check neightbor status and increment
                        if (this->get_cell(x, y)) { n++; }
                    }
                }
            }
        }
    }

    return n;
}

void GOLBoard::_update(int i, int j, int height, int width) {
    // exit condition once the board has been iterated through
    if (j == this->height) { return; }
    
    // assert that the given indecies are within game bounds
    assert(i >= 0 && i < width);
    assert(j >= 0 && j < height);

    // get number of neighbors and life status
    int neighbors = _neighbors(i, j);
    bool alive = this->board[(j * width) + i];

    // recurse to next cell
    if (i ==  width - 1) {
        _update(0, j+1, height, width);
    } else {
        _update(i+1, j, height, width);
    }

    // update current cell
    if (alive) {
        if (neighbors < 2 || neighbors > 3) {
            this->board[(j * width) + i] = false;
        }
    } else {
        if (neighbors == 3) {
            this->board[(j * width) + i] = true;
        }
    }

    return;
}

// board update for next generation
void GOLBoard::update() {
    _update(0, 0, this->height, this->width);
    this->gen = this->gen + 1;
    return;
}

// output the board to stdout
void GOLBoard::print_board() {
    int o;
    for (int j = 0; j < this->height; j++) {
        for (int i = 0; i < this->width; i++) {
            o = get_cell(i, j);
            if (o == 1) {
                std::cout << "O" << " ";
            } else {
                std::cout << " " << " ";
            }
        } std::cout << std::endl;
    }
    return;
}
//
// movegen.h
//
// Handles the move generation.
//

#pragma once

#include <cstdio>
#include <cinttypes>
#include <string>
#include <vector>
#include "board.h"

std::vector<struct Move> generateHorizontalRay(int square_key, bool piece_color, char piece_type); // piece_color = 0 if piece is white
std::vector<struct Move> generateVerticalRay(int square_key, bool piece_color, char piece_type);
std::vector<struct Move> generateSouthwestToNortheastRay(int square_key, bool piece_color, char piece_type); // use compass to distinguish diagonal rays
std::vector<struct Move> generateSoutheastToNorthwestRay(int square_key, bool piece_color, char piece_type);

std::vector<struct Move> generateMoves(struct Game *game);

bool isCheck(struct Game *game); // returns 1 if side to move is in check

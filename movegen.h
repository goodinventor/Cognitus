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
#include <algorithm>
#include "board.h"

std::vector<struct Move> generateHorizontalRay(int square_key, bool piece_color, char piece_type); // piece_color = 0 if piece is white
std::vector<struct Move> generateVerticalRay(int square_key, bool piece_color, char piece_type);
std::vector<struct Move> generateSouthwestToNortheastRay(int square_key, bool piece_color, char piece_type); // use compass to distinguish diagonal rays
std::vector<struct Move> generateSoutheastToNorthwestRay(int square_key, bool piece_color, char piece_type);

std::vector<struct Move> generateMoves(struct Game *game);

bool isCheck(struct Game *game); // returns 1 if side to move is in check

bool kingCastleInCheckPred(struct Game& game, const struct Move& move); // predicate for checking that king cannot castle in check for legalizeMoves()
bool kingInCheckAfterMovePred(struct Game& game, const struct Move& move); // predicate for checking whether king is in check after a move for legalizeMoves()

std::vector<struct Move> legalizeMoves(struct Game *game, std::vector<struct Move> moves_list);

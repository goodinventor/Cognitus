//
// uci.h
//
// Handles the UCI protocol.
//

#pragma once

#include <cstring>
#include <string>
#include "board.h"

void importFEN(char* fen, struct Game *game);
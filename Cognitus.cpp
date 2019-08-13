//
// Cognitus 2019
//
// programmed by George Andrews
//
// This is a first attempt to program a complete chess engine from scratch. Previous work involved improving an existing chess engine.
//

#include <cstdio>
#include <cstring>
#include <string>
#include <cinttypes>
#include <vector>
#include "board.h"
#include "uci.h"
#include "movegen.h"

int main() {
	Game *myGame = new Game;
	const char* fen = "rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq - 0 1";
	char* pos = _strdup(fen);

	importFEN(pos, myGame); // initialize position

	displayBitboards();

	bool check = isCheck(myGame);

	if (check) printf("The king is in check!");
	else printf("The king is not in check.");
	
	return 0;
}

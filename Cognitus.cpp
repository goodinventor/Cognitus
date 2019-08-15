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
	const char* fen = "rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1";
	char* pos = _strdup(fen);

	importFEN(pos, myGame); // initialize position

	displayBitboards();

	std::vector<struct Move> myMoves = generateMoves(myGame);
	legalizeMoves(myGame, myMoves);

	for (int i = 0; i < myMoves.size(); ++i) {
		printf(myMoves.at(i).Move[0]);
		printf(myMoves.at(i).Move[1]);
		printf("\n");
	}

	return 0;
}

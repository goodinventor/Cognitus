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

	std::vector<struct Move> myMoves = generateMoves(myGame);

	// loop through the generated moves and print
	for (int i = 0; i < myMoves.size(); ++i) {
		// get constants to pass to printf
		const char* startSquare = myMoves.at(i).Move[0];
		const char* endSquare = myMoves.at(i).Move[1];

		std::printf(startSquare);
		std::printf(endSquare);
		std::printf("\n");
	}

	return 0;
}
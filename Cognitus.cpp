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
#include <algorithm>
#include "board.h"
#include "uci.h"
#include "movegen.h"

int main() {
	Game *myGame = new Game;
	const char* fen = "rnb1kbnr/pppp1ppp/8/4p3/4PP1q/8/PPPP2PP/RNBQKBNR w KQkq - 0 1";
	char* pos = _strdup(fen);

	importFEN(pos, myGame); // initialize position

	displayBitboards();

	std::vector<struct Move> myMoves = generateMoves(myGame);

	std::vector<struct Move> legalMoves = legalizeMoves(myGame, myMoves);

	for (int i = 0; i < legalMoves.size(); ++i) {
		std::printf(legalMoves.at(i).Move[0]);
		std::printf(legalMoves.at(i).Move[1]);
		std::printf("\n");
	}

	return 0;
}

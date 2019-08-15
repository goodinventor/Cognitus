//
// board.cpp
//
// Implements the board representation.
//

#include <cstdio>
#include <cinttypes>
#include <string>
#include "board.h"

unsigned long long int Bitboard::whitePawnBitboard = 0;
unsigned long long int Bitboard::whiteKnightBitboard = 0;
unsigned long long int Bitboard::whiteBishopBitboard = 0;
unsigned long long int Bitboard::whiteRookBitboard = 0;
unsigned long long int Bitboard::whiteQueenBitboard = 0;
unsigned long long int Bitboard::whiteKingBitboard = 0;
unsigned long long int Bitboard::blackPawnBitboard = 0;
unsigned long long int Bitboard::blackKnightBitboard = 0;
unsigned long long int Bitboard::blackBishopBitboard = 0;
unsigned long long int Bitboard::blackRookBitboard = 0;
unsigned long long int Bitboard::blackQueenBitboard = 0;
unsigned long long int Bitboard::blackKingBitboard = 0;

const char* Board64Strings[8][8] = { {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"},
									{"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"},
									{"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"},
									{"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"},
									{"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"},
									{"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"},
									{"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"},
									{"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"} };

const char* Board64Strings1D[64] = { "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
									"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
									"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
									"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
									"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
									"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
									"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
									"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8" };

void initPos(struct Game *game) {
	Bitboard::whitePawnBitboard = 0x000000000000FF00;
	Bitboard::whiteKnightBitboard = 0x0000000000000042;
	Bitboard::whiteBishopBitboard = 0x0000000000000024;
	Bitboard::whiteRookBitboard = 0x0000000000000081;
	Bitboard::whiteQueenBitboard = 0x0000000000000008;
	Bitboard::whiteKingBitboard = 0x0000000000000010;
	Bitboard::blackPawnBitboard = 0xFF00000000000000;
	Bitboard::blackKnightBitboard = 0x4200000000000000;
	Bitboard::blackBishopBitboard = 0x2400000000000000;
	Bitboard::blackRookBitboard = 0x8100000000000000;
	Bitboard::blackQueenBitboard = 0x0800000000000000;
	Bitboard::blackKingBitboard = 0x1000000000000000;

	game->SideToMove = 0;
	game->CanCastleQueensideWhite = 1;
	game->CanCastleKingsideWhite = 1;
	game->CanCastleQueensideBlack = 1;
	game->CanCastleKingsideBlack = 1;
}

// tested -> works
void displayBitboards() {
	std::printf("whitePawnBitboard: %" PRIx64 "\n", Bitboard::whitePawnBitboard);
	std::printf("whiteKnightBitboard: %" PRIx64 "\n", Bitboard::whiteKnightBitboard);
	std::printf("whiteBishopBitboard: %" PRIx64 "\n", Bitboard::whiteBishopBitboard);
	std::printf("whiteRookBitboard: %" PRIx64 "\n", Bitboard::whiteRookBitboard);
	std::printf("whiteQueenBitboard: %" PRIx64 "\n", Bitboard::whiteQueenBitboard);
	std::printf("whiteKingBitboard: %" PRIx64 "\n", Bitboard::whiteKingBitboard);
	std::printf("blackPawnBitboard: %" PRIx64 "\n", Bitboard::blackPawnBitboard);
	std::printf("blackKnightBitboard: %" PRIx64 "\n", Bitboard::blackKnightBitboard);
	std::printf("blackBishopBitboard: %" PRIx64 "\n", Bitboard::blackBishopBitboard);
	std::printf("blackRookBitboard: %" PRIx64 "\n", Bitboard::blackRookBitboard);
	std::printf("blackQueenBitboard: %" PRIx64 "\n", Bitboard::blackQueenBitboard);
	std::printf("blackKingBitboard: %" PRIx64 "\n", Bitboard::blackKingBitboard);
}

unsigned long long int UCISquareToBitboard(char* square) {
	std::string square_string(square);
	int row;
	int column;

	for (unsigned int i = 0; i < square_string.length(); ++i) {
		if (square_string.at(i) == 'a') {
			column = 0;
		}
		else if (square_string.at(i) == 'b') {
			column = 1;
		}
		else if (square_string.at(i) == 'c') {
			column = 2;
		}
		else if (square_string.at(i) == 'd') {
			column = 3;
		}
		else if (square_string.at(i) == 'e') {
			column = 4;
		}
		else if (square_string.at(i) == 'f') {
			column = 5;
		}
		else if (square_string.at(i) == 'g') {
			column = 6;
		}
		else if (square_string.at(i) == 'h') {
			column = 7;
		}
		else if (square_string.at(i) == '1') {
			row = 0;
		}
		else if (square_string.at(i) == '2') {
			row = 1;
		}
		else if (square_string.at(i) == '3') {
			row = 2;
		}
		else if (square_string.at(i) == '4') {
			row = 3;
		}
		else if (square_string.at(i) == '5') {
			row = 4;
		}
		else if (square_string.at(i) == '6') {
			row = 5;
		}
		else if (square_string.at(i) == '7') {
			row = 6;
		}
		else if (square_string.at(i) == '8') {
			row = 7;
		}
		else {
			return 0x0; // edge case for debugging and also addresses FEN en passant square symbol '-'
		}
	}

	return SquareOffsets[row][column];
}

unsigned char UCISquareTo64(char* square) {
	std::string square_string(square);
	int row;
	int column;

	for (unsigned int i = 0; i < square_string.length(); ++i) {
		if (square_string.at(i) == 'a') {
			column = 0;
		}
		else if (square_string.at(i) == 'b') {
			column = 1;
		}
		else if (square_string.at(i) == 'c') {
			column = 2;
		}
		else if (square_string.at(i) == 'd') {
			column = 3;
		}
		else if (square_string.at(i) == 'e') {
			column = 4;
		}
		else if (square_string.at(i) == 'f') {
			column = 5;
		}
		else if (square_string.at(i) == 'g') {
			column = 6;
		}
		else if (square_string.at(i) == 'h') {
			column = 7;
		}
		else if (square_string.at(i) == '1') {
			row = 0;
		}
		else if (square_string.at(i) == '2') {
			row = 1;
		}
		else if (square_string.at(i) == '3') {
			row = 2;
		}
		else if (square_string.at(i) == '4') {
			row = 3;
		}
		else if (square_string.at(i) == '5') {
			row = 4;
		}
		else if (square_string.at(i) == '6') {
			row = 5;
		}
		else if (square_string.at(i) == '7') {
			row = 6;
		}
		else if (square_string.at(i) == '8') {
			row = 7;
		}
		else {
			return 0x0; // edge case for debugging and also addresses FEN en passant square symbol '-'
		}
	}

	return Board64[row][column];
}

bool getBit(unsigned long long int bitboard, unsigned char bitNumber) {
	bool bit = (bitboard >> bitNumber) & 1;
	return bit;
}

unsigned char offsetsTo64(unsigned long long offset) {
	for (unsigned char i = 0; i < 8; ++i) {
		for (unsigned char j = 0; j < 8; ++j) {
			if (offset == SquareOffsets[i][j]) return Board64[i][j];
		}
	}

	return 0; // return 0 if no match found (i.e. inputted offset is invalid)
}

unsigned long long board64ToOffset(unsigned char bitNumber) {
	for (unsigned char i = 0; i < 8; ++i) {
		for (unsigned char j = 0; j < 8; ++j) {
			if (bitNumber == Board64[i][j]) return SquareOffsets[i][j];
		}
	}

	return 0; //return 0 if no match found (i.e. inputed square is invalid)
}

void makeMove(char* move, struct Game *game) {
	// We check the length of the string, then split it into 2 or 3 parts.
	std::string move_string(move);
	std::string start_square = move_string.substr(0, 2);
	std::string end_square = move_string.substr(2, 2);
	std::string promotion_piece;
	// Compute offsets. Start offset will be subtracted from the corresponding piece bitboard and end offset will be added similarly.
	unsigned long long int start_offset = UCISquareToBitboard(_strdup(start_square.c_str()));
	unsigned long long int end_offset = UCISquareToBitboard(_strdup(end_square.c_str()));

	// find which piece inhabits the starting square by testing the offset with each piece bitboard
	if (getBit(Bitboard::whitePawnBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// white pawn is on starting square; subtract and add offsets from/to bitboard
		Bitboard::whitePawnBitboard -= start_offset;

		if (move_string.length() == 4) Bitboard::whitePawnBitboard += end_offset; // no promotion; add pawn back on ending square
		if (move_string.length() == 5) {
			// break into three parts (add third part)
			promotion_piece = move_string.substr(4, 1);

			if (promotion_piece == "n") Bitboard::whiteKnightBitboard += end_offset;
			if (promotion_piece == "b") Bitboard::whiteBishopBitboard += end_offset;
			if (promotion_piece == "r") Bitboard::whiteRookBitboard += end_offset;
			if (promotion_piece == "q") Bitboard::whiteQueenBitboard += end_offset;
		}

		// check if there's any other (black) piece on the ending square and delete the piece if so
		if ((end_offset == (start_offset << 7)) || (end_offset == (start_offset << 9))) { // check if there's a capture (including en passant)
			if (getBit(Bitboard::blackPawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackPawnBitboard -= end_offset;
			else if (getBit(Bitboard::blackKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackKnightBitboard -= end_offset;
			else if (getBit(Bitboard::blackBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackBishopBitboard -= end_offset;
			else if (getBit(Bitboard::blackRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackRookBitboard -= end_offset;
			else if (getBit(Bitboard::blackQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackQueenBitboard -= end_offset;
			else { // no piece in end square; must be en passant capture
				// get square behind game->EnPassantTargetSquare
				unsigned long long enPassantCapturedPieceSquare = game->EnPassantTargetSquare >> 8; // go back a rank (e.g. 2 -> 1)
				// update black pawn bitboard
				Bitboard::blackPawnBitboard -= enPassantCapturedPieceSquare;
			}
		}
		

		// update struct Game variables
		game->SideToMove = 1;

		// Check if pawn has moved forward two squares. In that case, set the en passant target square.
		if (end_offset == start_offset << (8 * 2)) {
			game->EnPassantTargetSquare = start_offset << (8 * 1); // en passant square is directly behind the end square or in front of
																   // the start square
		}

		game->NumHalfMovesFiftyMovesRule = 0; // pawn has been moved; reset 50 moves rule counter
	}
	else if (getBit(Bitboard::blackPawnBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// black pawn is on starting square; subtract and add offsets from/to bitboard
		Bitboard::blackPawnBitboard -= start_offset;

		if (move_string.length() == 4) Bitboard::blackPawnBitboard += end_offset; // no promotion; add pawn back on ending square
		if (move_string.length() == 5) {
			// break into three parts (add third part)
			promotion_piece = move_string.substr(4, 1);

			if (promotion_piece == "n") Bitboard::blackKnightBitboard += end_offset;
			if (promotion_piece == "b") Bitboard::blackBishopBitboard += end_offset;
			if (promotion_piece == "r") Bitboard::blackRookBitboard += end_offset;
			if (promotion_piece == "q") Bitboard::blackQueenBitboard += end_offset;
		}

		// check if there's any other (black) piece on the ending square and delete the piece if so
		if ((end_offset == (start_offset >> 7)) || (end_offset == (start_offset >> 9))) { // check if there's a capture (including en passant)
			if (getBit(Bitboard::whitePawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whitePawnBitboard -= end_offset;
			else if (getBit(Bitboard::whiteKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteKnightBitboard -= end_offset;
			else if (getBit(Bitboard::whiteBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteBishopBitboard -= end_offset;
			else if (getBit(Bitboard::whiteRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteRookBitboard -= end_offset;
			else if (getBit(Bitboard::whiteQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteQueenBitboard -= end_offset;
			else { // no piece in end square; must be en passant capture
				// get square behind game->EnPassantTargetSquare
				unsigned long long enPassantCapturedPieceSquare = game->EnPassantTargetSquare << 8; // go back a rank (e.g. 1 -> 2)
				// update white pawn bitboard
				Bitboard::whitePawnBitboard -= enPassantCapturedPieceSquare;
			}
		}

		// update struct Game variables
		game->SideToMove = 0;

		// Check if pawn has moved forward two squares. In that case, set the en passant target square.
		if (end_offset == start_offset >> (8 * 2)) {
			game->EnPassantTargetSquare = start_offset >> (8 * 1); // en passant square is directly behind the end square or in front of
																   // the start square
		}

		game->NumHalfMovesFiftyMovesRule = 0; // pawn has been moved; reset 50 moves rule counter
		game->MoveNumber++; // black has moved; update move number
	}
	else if (getBit(Bitboard::whiteKnightBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// white knight is on starting square; subtract and add offsets from/to bitboard
		Bitboard::whiteKnightBitboard -= start_offset;
		Bitboard::whiteKnightBitboard += end_offset;
	
		// check if there's any other (black) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::blackPawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackPawnBitboard -= end_offset;
		if (getBit(Bitboard::blackKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackKnightBitboard -= end_offset;
		if (getBit(Bitboard::blackBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackBishopBitboard -= end_offset;
		if (getBit(Bitboard::blackRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackRookBitboard -= end_offset;
		if (getBit(Bitboard::blackQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 1;
		game->NumHalfMovesFiftyMovesRule++;
	}
	else if (getBit(Bitboard::blackKnightBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// black knight is on starting square; subtract and add offsets from/to bitboard
		Bitboard::blackKnightBitboard -= start_offset;
		Bitboard::blackKnightBitboard += end_offset;

		// check if there's any other (white) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::whitePawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whitePawnBitboard -= end_offset;
		if (getBit(Bitboard::whiteKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteKnightBitboard -= end_offset;
		if (getBit(Bitboard::whiteBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteBishopBitboard -= end_offset;
		if (getBit(Bitboard::whiteRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteRookBitboard -= end_offset;
		if (getBit(Bitboard::whiteQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 0;
		game->NumHalfMovesFiftyMovesRule++;
		game->MoveNumber++;
	}
	else if (getBit(Bitboard::whiteBishopBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// white bishop is on starting square; subtract and add offsets from/to bitboard
		Bitboard::whiteBishopBitboard -= start_offset;
		Bitboard::whiteBishopBitboard += end_offset;

		// check if there's any other (black) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::blackPawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackPawnBitboard -= end_offset;
		if (getBit(Bitboard::blackKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackKnightBitboard -= end_offset;
		if (getBit(Bitboard::blackBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackBishopBitboard -= end_offset;
		if (getBit(Bitboard::blackRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackRookBitboard -= end_offset;
		if (getBit(Bitboard::blackQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 1;
		game->NumHalfMovesFiftyMovesRule++;
	}
	else if (getBit(Bitboard::blackBishopBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// black bishop is on starting square; subtract and add offsets from/to bitboard
		Bitboard::blackBishopBitboard -= start_offset;
		Bitboard::blackBishopBitboard += end_offset;

		// check if there's any other (white) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::whitePawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whitePawnBitboard -= end_offset;
		if (getBit(Bitboard::whiteKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteKnightBitboard -= end_offset;
		if (getBit(Bitboard::whiteBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteBishopBitboard -= end_offset;
		if (getBit(Bitboard::whiteRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteRookBitboard -= end_offset;
		if (getBit(Bitboard::whiteQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 0;
		game->NumHalfMovesFiftyMovesRule++;
		game->MoveNumber++;
	}
	else if (getBit(Bitboard::whiteRookBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// white rook is on starting square; subtract and add offsets from/to bitboard
		Bitboard::whiteRookBitboard -= start_offset;
		Bitboard::whiteRookBitboard += end_offset;

		// check if there's any other (black) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::blackPawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackPawnBitboard -= end_offset;
		if (getBit(Bitboard::blackKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackKnightBitboard -= end_offset;
		if (getBit(Bitboard::blackBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackBishopBitboard -= end_offset;
		if (getBit(Bitboard::blackRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackRookBitboard -= end_offset;
		if (getBit(Bitboard::blackQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 1;
		game->NumHalfMovesFiftyMovesRule++;
	}
	else if (getBit(Bitboard::blackRookBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// black rook is on starting square; subtract and add offsets from/to bitboard
		Bitboard::blackRookBitboard -= start_offset;
		Bitboard::blackRookBitboard += end_offset;

		// check if there's any other (white) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::whitePawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whitePawnBitboard -= end_offset;
		if (getBit(Bitboard::whiteKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteKnightBitboard -= end_offset;
		if (getBit(Bitboard::whiteBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteBishopBitboard -= end_offset;
		if (getBit(Bitboard::whiteRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteRookBitboard -= end_offset;
		if (getBit(Bitboard::whiteQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 0;
		game->NumHalfMovesFiftyMovesRule++;
		game->MoveNumber++;
	}
	else if (getBit(Bitboard::whiteQueenBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// white queen is on starting square; subtract and add offsets from/to bitboard
		Bitboard::whiteQueenBitboard -= start_offset;
		Bitboard::whiteQueenBitboard += end_offset;
		
		// check if there's any other (black) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::blackPawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackPawnBitboard -= end_offset;
		if (getBit(Bitboard::blackKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackKnightBitboard -= end_offset;
		if (getBit(Bitboard::blackBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackBishopBitboard -= end_offset;
		if (getBit(Bitboard::blackRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackRookBitboard -= end_offset;
		if (getBit(Bitboard::blackQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackQueenBitboard -= end_offset;
		
		// update struct Game variables
		game->SideToMove = 1;
		game->NumHalfMovesFiftyMovesRule++;
	}
	else if (getBit(Bitboard::blackQueenBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// black queen is on starting square; subtract and add offsets from/to bitboard
		Bitboard::blackQueenBitboard -= start_offset;
		Bitboard::blackQueenBitboard += end_offset;
		
		// check if there's any other (white) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::whitePawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whitePawnBitboard -= end_offset;
		if (getBit(Bitboard::whiteKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteKnightBitboard -= end_offset;
		if (getBit(Bitboard::whiteBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteBishopBitboard -= end_offset;
		if (getBit(Bitboard::whiteRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteRookBitboard -= end_offset;
		if (getBit(Bitboard::whiteQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteQueenBitboard -= end_offset;
		
		// update struct Game variables
		game->SideToMove = 0;
		game->NumHalfMovesFiftyMovesRule++;
		game->MoveNumber++;
	}
	else if (getBit(Bitboard::whiteKingBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// white king is on starting square; subtract and add offsets from/to bitboard
		Bitboard::whiteKingBitboard -= start_offset;
		Bitboard::whiteKingBitboard += end_offset;

		// check if there's any other (black) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::blackPawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackPawnBitboard -= end_offset;
		if (getBit(Bitboard::blackKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackKnightBitboard -= end_offset;
		if (getBit(Bitboard::blackBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackBishopBitboard -= end_offset;
		if (getBit(Bitboard::blackRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackRookBitboard -= end_offset;
		if (getBit(Bitboard::blackQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::blackQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 1;
		game->NumHalfMovesFiftyMovesRule++;

		// check if king has moves to squares (to castle) then update CanCastle variables and rook position accordingly
		if (end_offset == start_offset << 2) { // kingside castle
			// rook is on h1; move it to f1
			Bitboard::whiteRookBitboard -= SquareOffsets[0][7];
			Bitboard::whiteRookBitboard += SquareOffsets[0][5];

			// update CanCastle variables
			game->CanCastleKingsideWhite = 0;
			game->CanCastleQueensideWhite = 0;
		}
		if (end_offset == start_offset >> 2) { // queenside castle
			// rook is on a1; move it to d1
			Bitboard::whiteRookBitboard -= SquareOffsets[0][0];
			Bitboard::whiteRookBitboard += SquareOffsets[0][3];

			// update CanCastle variables
			game->CanCastleKingsideWhite = 0;
			game->CanCastleQueensideWhite = 0;
		}
	}
	else if (getBit(Bitboard::blackKingBitboard, UCISquareTo64(_strdup(start_square.c_str()))) == 1) {
		// black king is on starting square; subtract and add offsets from/to bitboard
		Bitboard::blackKingBitboard -= start_offset;
		Bitboard::blackKingBitboard += end_offset;

		// check if there's any other (white) piece on the ending square and delete the piece if so
		if (getBit(Bitboard::whitePawnBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whitePawnBitboard -= end_offset;
		if (getBit(Bitboard::whiteKnightBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteKnightBitboard -= end_offset;
		if (getBit(Bitboard::whiteBishopBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteBishopBitboard -= end_offset;
		if (getBit(Bitboard::whiteRookBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteRookBitboard -= end_offset;
		if (getBit(Bitboard::whiteQueenBitboard, UCISquareTo64(_strdup(end_square.c_str()))) == 1) Bitboard::whiteQueenBitboard -= end_offset;

		// update struct Game variables
		game->SideToMove = 0;
		game->NumHalfMovesFiftyMovesRule++;
		game->MoveNumber++;

		// check if king has moves to squares (to castle) then update CanCastle variables and rook position accordingly
		if (end_offset == start_offset << 2) { // kingside castle
			// rook is on h8; move it to f8
			Bitboard::blackRookBitboard -= SquareOffsets[7][7];
			Bitboard::blackRookBitboard += SquareOffsets[7][5];

			// update CanCastle variables
			game->CanCastleKingsideBlack = 0;
			game->CanCastleQueensideBlack = 0;
		}
		if (end_offset == start_offset >> 2) { // queenside castle
			// rook is on a1; move it to d1
			Bitboard::blackRookBitboard -= SquareOffsets[7][0];
			Bitboard::blackRookBitboard += SquareOffsets[7][3];

			// update CanCastle variables
			game->CanCastleKingsideBlack = 0;
			game->CanCastleQueensideBlack = 0;
		}
	}
}

void unmakeMove(struct Move move, struct Game* game) {
	// We check the length of the string, then split it into 2 or 3 parts.
	std::string start_square = move.Move[0];
	std::string end_square = move.Move[1];
	std::string promotion_piece(1, move.PromotionPiece);
	// Compute offsets. Start offset will be added to the corresponding piece bitboard and end offset will be subtracted similarly.
	unsigned long long int start_offset = UCISquareToBitboard(_strdup(start_square.c_str()));
	unsigned long long int end_offset = UCISquareToBitboard(_strdup(end_square.c_str()));

	// If piece is a pawn at the starting square of the move, we need to take into account the possibility of promotions.
	if ((move.Piece == 'P') || (move.Piece == 'p')) {
		switch (move.PromotionPiece) {
		case 'N':
			Bitboard::whiteKnightBitboard -= end_offset;
			Bitboard::whitePawnBitboard += start_offset;
			break;

		case 'B':
			Bitboard::whiteBishopBitboard -= end_offset;
			Bitboard::whitePawnBitboard += start_offset;
			break;

		case 'R':
			Bitboard::whiteRookBitboard -= end_offset;
			Bitboard::whitePawnBitboard += start_offset;
			break;

		case 'Q':
			Bitboard::whiteQueenBitboard -= end_offset;
			Bitboard::whitePawnBitboard += start_offset;
			break;

		case 'n':
			Bitboard::blackKnightBitboard -= end_offset;
			Bitboard::blackPawnBitboard += start_offset;
			break;

		case 'b':
			Bitboard::blackBishopBitboard -= end_offset;
			Bitboard::blackPawnBitboard += start_offset;
			break;

		case 'r':
			Bitboard::blackRookBitboard -= end_offset;
			Bitboard::blackPawnBitboard += start_offset;
			break;

		case 'q':
			Bitboard::blackQueenBitboard -= end_offset;
			Bitboard::blackPawnBitboard += start_offset;
			break;

		default: // no promotion
			if (move.Piece == 'P') {
				Bitboard::whitePawnBitboard -= end_offset;
				Bitboard::whitePawnBitboard += start_offset;
			}
			else {
				Bitboard::blackPawnBitboard -= end_offset;
				Bitboard::blackPawnBitboard += start_offset;
			}
			break;
		}
	}
	// The king can castle, which we need a special case for since UCI castling moves are expressed in terms of the king movement.
	else if ((move.Piece == 'K') || (move.Piece == 'k')) {
		Bitboard::whiteKingBitboard -= end_offset;
		Bitboard::whiteKingBitboard += start_offset;
			
		if (move.IsCastle && (move.Piece == 'K')) {
			// check king location to determine side of castling
			if (end_offset == 0x4) { // queenside castling
				Bitboard::whiteRookBitboard -= 0x8;
				Bitboard::whiteRookBitboard += 0x1;
				game->CanCastleQueensideWhite = 1;
			}
			else { // kingside castling
				Bitboard::whiteRookBitboard -= 0x20;
				Bitboard::whiteRookBitboard += 0x80;
				game->CanCastleKingsideWhite = 1;
			}
		}
		else if (move.IsCastle && (move.Piece == 'k')) {
			// check king location to determine side of castling
			if (end_offset == 0x4) { // queenside castling
				Bitboard::blackRookBitboard -= 0x800000000000000;
				Bitboard::blackRookBitboard += 0x100000000000000;
				game->CanCastleQueensideBlack = 1;
			}
			else { // kingside castling
				Bitboard::blackRookBitboard -= 0x2000000000000000;
				Bitboard::blackRookBitboard += 0x8000000000000000;
				game->CanCastleKingsideBlack = 1;
			}
		}

		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'N') {
		Bitboard::whiteKnightBitboard -= end_offset;
		Bitboard::whiteKnightBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'n') {
		Bitboard::blackKnightBitboard -= end_offset;
		Bitboard::blackKnightBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'B') {
		Bitboard::whiteBishopBitboard -= end_offset;
		Bitboard::whiteBishopBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'b') {
		Bitboard::blackBishopBitboard -= end_offset;
		Bitboard::blackBishopBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'R') {
		Bitboard::whiteRookBitboard -= end_offset;
		Bitboard::whiteRookBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'r') {
		Bitboard::blackRookBitboard -= end_offset;
		Bitboard::blackRookBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'Q') {
		Bitboard::whiteQueenBitboard -= end_offset;
		Bitboard::whiteQueenBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'q') {
		Bitboard::blackQueenBitboard -= end_offset;
		Bitboard::blackQueenBitboard += start_offset;
		game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'K') {
	Bitboard::whiteKingBitboard -= end_offset;
	Bitboard::whiteKingBitboard += start_offset;
	game->NumHalfMovesFiftyMovesRule--;
	}
	else if (move.Piece == 'k') {
	Bitboard::blackKingBitboard -= end_offset;
	Bitboard::blackKingBitboard += start_offset;
	game->NumHalfMovesFiftyMovesRule--;
	}

	// handle captures
	switch (move.CapturedPiece) {
	case 'P':
		Bitboard::whitePawnBitboard += end_offset;
		break;

	case 'N':
		Bitboard::whiteKnightBitboard += end_offset;
		break;

	case 'B':
		Bitboard::whiteBishopBitboard += end_offset;
		break;

	case 'R':
		Bitboard::whiteRookBitboard += end_offset;
		break;

	case 'Q':
		Bitboard::whiteQueenBitboard += end_offset;
		break;

	case 'p':
		Bitboard::blackPawnBitboard += end_offset;
		break;

	case 'n':
		Bitboard::blackKnightBitboard += end_offset;
		break;

	case 'b':
		Bitboard::blackBishopBitboard += end_offset;
		break;

	case 'r':
		Bitboard::blackRookBitboard += end_offset;
		break;

	case 'q':
		Bitboard::blackQueenBitboard += end_offset;
		break;
	}

	game->SideToMove = !game->SideToMove; // this was updated in makeMove() and we want to reverse it
	if (game->SideToMove == 1) game->MoveNumber--;
}

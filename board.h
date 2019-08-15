//
// board.h
//
// Implements the board representation.
//

#pragma once

#include <cstdio>
#include <cinttypes>
#include <string>

// bitboards for each type of piece
namespace Bitboard {
	extern unsigned long long int whitePawnBitboard;
	extern unsigned long long int whiteKnightBitboard;
	extern unsigned long long int whiteBishopBitboard;
	extern unsigned long long int whiteRookBitboard;
	extern unsigned long long int whiteQueenBitboard;
	extern unsigned long long int whiteKingBitboard;
	extern unsigned long long int blackPawnBitboard;
	extern unsigned long long int blackKnightBitboard;
	extern unsigned long long int blackBishopBitboard;
	extern unsigned long long int blackRookBitboard;
	extern unsigned long long int blackQueenBitboard;
	extern unsigned long long int blackKingBitboard;
}

// constant bitboard values for common setups
const unsigned long long int FileA = 0x0101010101010101;
const unsigned long long int FileB = FileA << 1;
const unsigned long long int FileC = FileA << 2;
const unsigned long long int FileD = FileA << 3;
const unsigned long long int FileE = FileA << 4;
const unsigned long long int FileF = FileA << 5;
const unsigned long long int FileG = FileA << 6;
const unsigned long long int FileH = FileA << 7;

const unsigned long long int Rank1 = 0xFF;
const unsigned long long int Rank2 = Rank1 << (8 * 1);
const unsigned long long int Rank3 = Rank1 << (8 * 2);
const unsigned long long int Rank4 = Rank1 << (8 * 3);
const unsigned long long int Rank5 = Rank1 << (8 * 4);
const unsigned long long int Rank6 = Rank1 << (8 * 5);
const unsigned long long int Rank7 = Rank1 << (8 * 6);
const unsigned long long int Rank8 = Rank1 << (8 * 7);

// for use in importFEN in uci.h for square offsets (to update bitboards)
const unsigned long long int SquareOffsets[8][8] = { {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80}, // rank 1, files A-H (in that order)
													{0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000},
													{0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000},
													{0x1000000, 0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000},
													{0x100000000, 0x200000000, 0x400000000, 0x800000000, 0x1000000000, 0x2000000000, 0x4000000000, 0x8000000000},
													{0x10000000000, 0x20000000000, 0x40000000000, 0x80000000000, 0x100000000000, 0x200000000000, 0x400000000000, 0x800000000000},
													{0x1000000000000, 0x2000000000000, 0x4000000000000, 0x8000000000000, 0x10000000000000, 0x20000000000000, 0x40000000000000, 0x80000000000000},
													{0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000} };

const unsigned char Board64[8][8] = { {0, 1, 2, 3, 4, 5, 6, 7}, // rank 1, files A-H (in that order)
									{8, 9, 10, 11, 12, 13, 14, 15},
									{16, 17, 18, 19, 20, 21, 22, 23},
									{24, 25, 26, 27, 28, 29, 30, 31},
									{32, 33, 34, 35, 36, 37, 38, 39},
									{40, 41, 42, 43, 44, 45, 46, 47},
									{48, 49, 50, 51, 52, 53, 54, 55},
									{56, 57, 58, 59, 60, 61, 62, 63} };

const unsigned char SouthwestToNortheastRayStartThresholds[64] = { 0, 1, 2, 3, 4, 5, 6, 7, // gets the start square of the ray
																  8, 0, 1, 2, 3, 4, 5, 6,
																  16, 8, 0, 1, 2, 3, 4, 5,
																  24, 16, 8, 0, 1, 2, 3, 4,
																  32, 24, 16, 8, 0, 1, 2, 3,
																  40, 32, 24, 16, 8, 0, 1, 2,
																  48, 40, 32, 24, 16, 8, 0, 1,
																  56, 48, 40, 32, 24, 16, 8, 0 };

const unsigned char SouthwestToNortheastRayEndThresholds[64] = { 63, 55, 47, 39, 31, 23, 15, 7, // gets the end square of the ray
																62, 63, 55, 47, 39, 31, 23, 15,
																61, 62, 63, 55, 47, 39, 31, 23,
																60, 61, 62, 63, 55, 47, 39, 31,
																59, 60, 61, 62, 63, 55, 47, 39,
																58, 59, 60, 61, 62, 63, 55, 47,
																57, 58, 59, 60, 61, 62, 63, 55,
																56, 57, 58, 59, 60, 61, 62, 63 };

const unsigned char SoutheastToNorthwestRayStartThresholds[64] = { 0, 1, 2, 3, 4, 5, 6, 7,
																  1, 2, 3, 4, 5, 6, 7, 15,
																  2, 3, 4, 5, 6, 7, 15, 23,
																  3, 4, 5, 6, 7, 15, 23, 31,
																  4, 5, 6, 7, 15, 23, 31, 39,
																  5, 6, 7, 15, 23, 31, 39, 47,
																  6, 7, 15, 23, 31, 39, 47, 55,
																  7, 15, 23, 31, 39, 47, 55, 63 };

const unsigned char SoutheastToNorthwestRayEndThresholds[64] = { 0, 8, 16, 24, 32, 40, 48, 56,
																8, 16, 24, 32, 40, 48, 56, 57,
																16, 24, 32, 40, 48, 56, 57, 58,
																24, 32, 40, 48, 56, 57, 58, 59,
																32, 40, 48, 56, 57, 58, 59, 60,
																40, 48, 56, 57, 58, 59, 60, 61,
																48, 56, 57, 58, 59, 60, 61, 62,
																56, 57, 58, 59, 60, 61, 62, 63 };

extern const char* Board64Strings[8][8];

extern const char* Board64Strings1D[64];

struct Game {
	bool SideToMove; // 0 if white to move, 1 if black to move
	bool CanCastleQueensideWhite = 0; // 1 if white can castle, 0 otherwise (does not take into account pieces that are in the way)
	bool CanCastleKingsideWhite = 0;
	bool CanCastleQueensideBlack = 0;
	bool CanCastleKingsideBlack = 0;
	unsigned long long EnPassantTargetSquare;
	int NumHalfMovesFiftyMovesRule;
	int MoveNumber;
};

struct Move {
	char* Move[2]; // move[0] -> starting square, move[1] -> ending square (e.g. move[0] = "e2", move[1] = "e4")
	char Piece; // options: kqrbnpKQRBNP (to avoid confusion with promotions this value always refers to the starting square piece)
	char CapturedPiece;
	bool IsCastle; // 1 if it is
	bool EnPassantCapture;
	char* EnPassantSquare; // set the en passant capture square if a pawn is moved forward two spaces
	bool IsPromotion; // 1 if it is
	char PromotionPiece; // options same as Piece
};

void initPos(struct Game *game);

// for debugging
void displayBitboards();

unsigned long long int UCISquareToBitboard(char* square);
unsigned char UCISquareTo64(char* square);
bool getBit(unsigned long long int bitboard, unsigned char bitNumber); // get a bit from the bitboard, starting with 0 = least significant bit
unsigned char offsetsTo64(unsigned long long offset); // converts offsets (e.g. from game->EnPassantTargetSquare) to the bit number from
													  // Board64[8][8]
unsigned long long board64ToOffset(unsigned char bitNumber); // reverse of offsetsTo64

void makeMove(char* move, struct Game *game);
void unmakeMove(struct Move move, struct Game* game);

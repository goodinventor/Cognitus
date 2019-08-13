//
// uci.h
//
// Handles the UCI protocol.
//

#include <cstring>
#include <string>
#include "board.h"
#include "uci.h"

void importFEN(char* fen, struct Game *game) {
	// Parse the string first. We use '/' as the delimiter directly from the FEN notation guidelines. The original FEN string will be split into 13 parts,
	// described by the following:
	//
	// 1-8. Describes the rank contents beginning with rank 8 and ending with rank 1. White pieces are denoted by capital letters, and black pieces by
	//      lowercase letters.
	//   9. States the next side to move. 'w' if white and 'b' if black.
	//  10. Describes castling availability. E.g. 'K' means white can castle kingside.
	//  11. Lists en passant target square. If there is none '-' is displayed.
	//  12. Lists the number of half moves since the last capture or pawn advance.
	//  13. Number of the full move, starting at 1, and incremented after black moves (white to move).
	//
	// E.g. the starting position FEN is: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

	//std::string split_tokens[13];
	char* split_tokens[13];
	char* fen_tokens = std::strtok(fen, " /");
	int counter = 0;

	// keep calling strtok to make sure we have all the info
	while (fen_tokens != NULL) {
		split_tokens[counter++] = fen_tokens;
		fen_tokens = std::strtok(NULL, " /");
	}

	//for (counter = 0; counter < 13; ++counter) std::printf("%s\n", split_tokens[counter]);

	// Use the first 8 tokens (indexes 0-7) to update the bitboards.
	unsigned long long int offset = 0;
	std::string split_token_ref[13];

	for (int i = 0; i < 13; ++i) {
		split_token_ref[i].assign(split_tokens[i]);
	}

	int file = 0;
	for (int j = 0; j < 8; ++j) {
		for (unsigned int k = 0; k < split_token_ref[j].length(); ++k) {
			// Find out the square and the corresponding value to be added to the piece bitboard, then find the piece type.
			// Note: j = 0 -> rank 8, j = 7 -> rank 1 from FEN notation
			offset = SquareOffsets[(-1 * j) + 7][file];

			// create string object referencing array member for easier manipulation
			//std::string split_token_ref(split_tokens[j]);

			if (split_token_ref[j].at(k) == 'P') {
				Bitboard::whitePawnBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'N') {
				Bitboard::whiteKnightBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'B') {
				Bitboard::whiteBishopBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'R') {
				Bitboard::whiteRookBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'Q') {
				Bitboard::whiteQueenBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'K') {
				Bitboard::whiteKingBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'p') {
				Bitboard::blackPawnBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'n') {
				Bitboard::blackKnightBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'b') {
				Bitboard::blackBishopBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'r') {
				Bitboard::blackRookBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'q') {
				Bitboard::blackQueenBitboard += offset;
				++file;
			}
			else if (split_token_ref[j].at(k) == 'k') {
				Bitboard::blackKingBitboard += offset;
				++file;
			}
			else { // text is a number; update k
				if (split_token_ref[j].at(k) == '1') file += 1;
				else if (split_token_ref[j].at(k) == '2') file += 2;
				else if (split_token_ref[j].at(k) == '3') file += 3;
				else if (split_token_ref[j].at(k) == '4') file += 4;
				else if (split_token_ref[j].at(k) == '5') file += 5;
				else if (split_token_ref[j].at(k) == '6') file += 6;
				else if (split_token_ref[j].at(k) == '7') file += 7;
				else if (split_token_ref[j].at(k) == '8') file += 8;
			}
		}

		file = 0; // reset at the end for the next rankwise iteration
	}
	
	// 9th token: side to move
	if (split_token_ref[8].at(0) == 'w') {
		game->SideToMove = 0;
	}
	else if (split_token_ref[8].at(0) == 'b') {
		game->SideToMove = 1;
	}

	// 10th token: castling availability
	split_token_ref[9].assign(split_tokens[9]);

	for (int i = 0; i < split_token_ref[9].length(); ++i) {
		if (split_token_ref[9].at(i) == 'Q') {
			game->CanCastleQueensideWhite = 1;
		}
		else if (split_token_ref[9].at(i) == 'K') {
			game->CanCastleKingsideWhite = 1;
		}
		else if (split_token_ref[9].at(i) == 'q') {
			game->CanCastleQueensideBlack = 1;
		}
		else if (split_token_ref[9].at(i) == 'k') {
			game->CanCastleKingsideBlack = 1;
		}
	}

	// 11th token: en passant target square
	char* en_passant_square;
	en_passant_square = new char[2];
	std::strcpy(en_passant_square, split_tokens[10]);
	game->EnPassantTargetSquare = UCISquareToBitboard(en_passant_square);

	// 12th token: number of half moves since last capture or pawn advance (used to evaluate 50 moves rule)
	game->NumHalfMovesFiftyMovesRule = std::stoi(split_tokens[11]);

	// 13th token: number of full move, incremented after black's move
	game->MoveNumber = std::stoi(split_tokens[12]);
}
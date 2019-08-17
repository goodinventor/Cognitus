//
// movegen.h
//
// Handles the move generation.
//

#include <cstdio>
#include <cinttypes>
#include <string>
#include <vector>
#include <algorithm>
#include "board.h"

std::vector<struct Move> generateHorizontalRay(int square_key, bool piece_color, char piece_type) {
	std::vector<struct Move> horizontal_ray_moves;

	// Set end_threshold to be the last square on the same rank as square_key and similarly set start_threshold to be the first such square.
	int start_threshold = -1;
	int end_threshold = -1;

	if ((square_key >= 0) && (square_key <= 7)) {
		start_threshold = 0;
		end_threshold = 7;
	}
	else if ((square_key >= 8) && (square_key <= 15)) {
		start_threshold = 8;
		end_threshold = 15;
	}
	else if ((square_key >= 16) && (square_key <= 23)) {
		start_threshold = 16;
		end_threshold = 23;
	}
	else if ((square_key >= 24) && (square_key <= 31)) {
		start_threshold = 24;
		end_threshold = 31;
	}
	else if ((square_key >= 32) && (square_key <= 39)) {
		start_threshold = 32;
		end_threshold = 39;
	}
	else if ((square_key >= 40) && (square_key <= 47)) {
		start_threshold = 40;
		end_threshold = 47;
	}
	else if ((square_key >= 48) && (square_key <= 55)) {
		start_threshold = 48;
		end_threshold = 55;
	}
	else if ((square_key >= 56) && (square_key <= 63)) {
		start_threshold = 56;
		end_threshold = 63;
	}

	if (piece_color == 0) { // piece is white
		// Start by generating moves right in file starting at the file to the right of the piece.
		for (int i = square_key + 1; i <= end_threshold; ++i) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto generate_moves_left;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				horizontal_ray_moves.push_back(capture_move);

				goto generate_moves_left;
			}

			// Else just generate a normal move.
			struct Move horizontal_move;
			horizontal_move.Piece = piece_type;
			horizontal_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			horizontal_move.Move[1] = _strdup(Board64Strings1D[i]);
			horizontal_ray_moves.push_back(horizontal_move);
		}

	generate_moves_left:
		for (int i = square_key - 1; i >= start_threshold; --i) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				horizontal_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move horizontal_move;
			horizontal_move.Piece = piece_type;
			horizontal_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			horizontal_move.Move[1] = _strdup(Board64Strings1D[i]);
			horizontal_ray_moves.push_back(horizontal_move);
		}
	}
	else { // piece is black
		// Start by generating moves right in file starting at the file to the right of the piece.
		for (int i = square_key + 1; i <= end_threshold; ++i) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto generate_moves_left_black;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				horizontal_ray_moves.push_back(capture_move);

				goto generate_moves_left_black;
			}

			// Else just generate a normal move.
			struct Move horizontal_move;
			horizontal_move.Piece = piece_type;
			horizontal_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			horizontal_move.Move[1] = _strdup(Board64Strings1D[i]);
			horizontal_ray_moves.push_back(horizontal_move);
		}

	generate_moves_left_black:
		// Now generate moves to the left.
		for (int i = square_key - 1; i >= start_threshold; --i) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				horizontal_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move horizontal_move;
			horizontal_move.Piece = piece_type;
			horizontal_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			horizontal_move.Move[1] = _strdup(Board64Strings1D[i]);
			horizontal_ray_moves.push_back(horizontal_move);
		}
	}

end:
	return horizontal_ray_moves;
}

std::vector<struct Move> generateVerticalRay(int square_key, bool piece_color, char piece_type) {
	std::vector<struct Move> vertical_ray_moves;

	// Set end_threshold to be the last square on the same file as square_key and similarly set start_threshold to be the first such square.
	int start_threshold = -1;
	int end_threshold = -1;

	if (square_key % 8 == 0) {
		start_threshold = 0;
		end_threshold = 56;
	}
	else if ((square_key - 1) % 8 == 0) {
		start_threshold = 1;
		end_threshold = 57;
	}
	else if ((square_key - 2) % 8 == 0) {
		start_threshold = 2;
		end_threshold = 58;
	}
	else if ((square_key - 3) % 8 == 0) {
		start_threshold = 3;
		end_threshold = 59;
	}
	else if ((square_key - 4) % 8 == 0) {
		start_threshold = 4;
		end_threshold = 60;
	}
	else if ((square_key - 5) % 8 == 0) {
		start_threshold = 5;
		end_threshold = 61;
	}
	else if ((square_key - 6) % 8 == 0) {
		start_threshold = 6;
		end_threshold = 62;
	}
	else if ((square_key - 7) % 8 == 0) {
		start_threshold = 7;
		end_threshold = 63;
	}

	if (piece_color == 0) { // piece is white
		// Start by generating moves up in rank starting at the rank above the piece.
		for (int i = square_key + 8; i <= end_threshold; i += 8) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto generate_moves_down;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				vertical_ray_moves.push_back(capture_move);

				goto generate_moves_down;
			}

			// Else just generate a normal move.
			struct Move vertical_move;
			vertical_move.Piece = piece_type;
			vertical_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			vertical_move.Move[1] = _strdup(Board64Strings1D[i]);
			vertical_ray_moves.push_back(vertical_move);
		}

	generate_moves_down:
		// Now generate moves down in rank.
		for (int i = square_key - 8; i >= start_threshold; i -= 8) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				vertical_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move vertical_move;
			vertical_move.Piece = piece_type;
			vertical_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			vertical_move.Move[1] = _strdup(Board64Strings1D[i]);
			vertical_ray_moves.push_back(vertical_move);
		}
	}
	else { // piece is black
		// Start by generating moves up in rank starting at the rank above the piece.
		for (int i = square_key + 8; i <= end_threshold; i += 8) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto generate_moves_down_black;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				vertical_ray_moves.push_back(capture_move);

				goto generate_moves_down;
			}

			// Else just generate a normal move.
			struct Move vertical_move;
			vertical_move.Piece = piece_type;
			vertical_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			vertical_move.Move[1] = _strdup(Board64Strings1D[i]);
			vertical_ray_moves.push_back(vertical_move);
		}

	generate_moves_down_black:
		// Now generate moves down in rank.
		for (int i = square_key - 8; i >= start_threshold; i -= 8) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				vertical_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move vertical_move;
			vertical_move.Piece = piece_type;
			vertical_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			vertical_move.Move[1] = _strdup(Board64Strings1D[i]);
			vertical_ray_moves.push_back(vertical_move);
		}
	}

end:
	return vertical_ray_moves;
}

std::vector<struct Move> generateSouthwestToNortheastRay(int square_key, bool piece_color, char piece_type) {
	std::vector<struct Move> swtone_ray_moves;

	int start_threshold = SouthwestToNortheastRayStartThresholds[square_key];
	int end_threshold = SouthwestToNortheastRayEndThresholds[square_key];

	if (piece_color == 0) { // piece is white
		// Start by generating moves up in rank starting at the rank above the piece.
		for (int i = square_key + 9; i <= end_threshold; i += 9) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto generate_moves_down;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				swtone_ray_moves.push_back(capture_move);

				goto generate_moves_down;
			}

			// Else just generate a normal move.
			struct Move swtone_move;
			swtone_move.Piece = piece_type;
			swtone_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			swtone_move.Move[1] = _strdup(Board64Strings1D[i]);
			swtone_ray_moves.push_back(swtone_move);
		}

	generate_moves_down:
		// Now generate moves down in rank.
		for (int i = square_key - 9; i >= start_threshold; i -= 9) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				swtone_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move swtone_move;
			swtone_move.Piece = piece_type;
			swtone_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			swtone_move.Move[1] = _strdup(Board64Strings1D[i]);
			swtone_ray_moves.push_back(swtone_move);
		}
	}
	else { // piece is black
		// Start by generating moves up in rank starting at the rank above the piece.
		for (int i = square_key + 9; i <= end_threshold; i += 9) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto generate_moves_down_black;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				swtone_ray_moves.push_back(capture_move);

				goto generate_moves_down;
			}

			// Else just generate a normal move.
			struct Move swtone_move;
			swtone_move.Piece = piece_type;
			swtone_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			swtone_move.Move[1] = _strdup(Board64Strings1D[i]);
			swtone_ray_moves.push_back(swtone_move);
		}

	generate_moves_down_black:
		// Now generate moves down in rank.
		for (int i = square_key - 9; i >= start_threshold; i -= 9) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				swtone_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move swtone_move;
			swtone_move.Piece = piece_type;
			swtone_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			swtone_move.Move[1] = _strdup(Board64Strings1D[i]);
			swtone_ray_moves.push_back(swtone_move);
		}
	}

end:
	return swtone_ray_moves;
}

std::vector<struct Move> generateSoutheastToNorthwestRay(int square_key, bool piece_color, char piece_type) {
	std::vector<struct Move> setonw_ray_moves;

	int start_threshold = SoutheastToNorthwestRayStartThresholds[square_key];
	int end_threshold = SoutheastToNorthwestRayEndThresholds[square_key];

	if (piece_color == 0) { // piece is white
		// Start by generating moves up in rank starting at the rank above the piece.
		for (int i = square_key + 7; i <= end_threshold; i += 7) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto generate_moves_down;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				setonw_ray_moves.push_back(capture_move);

				goto generate_moves_down;
			}

			// Else just generate a normal move.
			struct Move setonw_move;
			setonw_move.Piece = piece_type;
			setonw_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			setonw_move.Move[1] = _strdup(Board64Strings1D[i]);
			setonw_ray_moves.push_back(setonw_move);
		}

	generate_moves_down:
		// Now generate moves down in rank.
		for (int i = square_key - 7; i >= start_threshold; i -= 7) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::blackPawnBitboard, i) == 1) capture_move.CapturedPiece = 'p';
				else if (getBit(Bitboard::blackKnightBitboard, i) == 1) capture_move.CapturedPiece = 'n';
				else if (getBit(Bitboard::blackBishopBitboard, i) == 1) capture_move.CapturedPiece = 'b';
				else if (getBit(Bitboard::blackRookBitboard, i) == 1) capture_move.CapturedPiece = 'r';
				else if (getBit(Bitboard::blackQueenBitboard, i) == 1) capture_move.CapturedPiece = 'q';
				else if (getBit(Bitboard::blackKingBitboard, i) == 1) capture_move.CapturedPiece = 'k';

				setonw_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move setonw_move;
			setonw_move.Piece = piece_type;
			setonw_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			setonw_move.Move[1] = _strdup(Board64Strings1D[i]);
			setonw_ray_moves.push_back(setonw_move);
		}
	}
	else { // piece is black
		// Start by generating moves up in rank starting at the rank above the piece.
		for (int i = square_key + 7; i <= end_threshold; i += 7) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto generate_moves_down_black;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				setonw_ray_moves.push_back(capture_move);

				goto generate_moves_down;
			}

			// Else just generate a normal move.
			struct Move setonw_move;
			setonw_move.Piece = piece_type;
			setonw_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			setonw_move.Move[1] = _strdup(Board64Strings1D[i]);
			setonw_ray_moves.push_back(setonw_move);
		}

	generate_moves_down_black:
		// Now generate moves down in rank.
		for (int i = square_key - 7; i >= start_threshold; i -= 7) {
			// Check for a same color piece, in which case we immediately end generation of the ray in this direction.
			if ((getBit(Bitboard::blackPawnBitboard, i) == 1) || (getBit(Bitboard::blackKnightBitboard, i) == 1) ||
				(getBit(Bitboard::blackBishopBitboard, i) == 1) || (getBit(Bitboard::blackRookBitboard, i) == 1) ||
				(getBit(Bitboard::blackQueenBitboard, i) == 1) || (getBit(Bitboard::blackKingBitboard, i) == 1)) {
				goto end;
			}

			// Check for an opposite color piece, in which case we first create a capture move then end generation of the ray in this direction.
			if ((getBit(Bitboard::whitePawnBitboard, i) == 1) || (getBit(Bitboard::whiteKnightBitboard, i) == 1) ||
				(getBit(Bitboard::whiteBishopBitboard, i) == 1) || (getBit(Bitboard::whiteRookBitboard, i) == 1) ||
				(getBit(Bitboard::whiteQueenBitboard, i) == 1) || (getBit(Bitboard::whiteKingBitboard, i) == 1)) {
				struct Move capture_move;
				capture_move.Piece = piece_type;
				capture_move.Move[0] = _strdup(Board64Strings1D[square_key]);
				capture_move.Move[1] = _strdup(Board64Strings1D[i]);

				if (getBit(Bitboard::whitePawnBitboard, i) == 1) capture_move.CapturedPiece = 'P';
				else if (getBit(Bitboard::whiteKnightBitboard, i) == 1) capture_move.CapturedPiece = 'N';
				else if (getBit(Bitboard::whiteBishopBitboard, i) == 1) capture_move.CapturedPiece = 'B';
				else if (getBit(Bitboard::whiteRookBitboard, i) == 1) capture_move.CapturedPiece = 'R';
				else if (getBit(Bitboard::whiteQueenBitboard, i) == 1) capture_move.CapturedPiece = 'Q';
				else if (getBit(Bitboard::whiteKingBitboard, i) == 1) capture_move.CapturedPiece = 'K';

				setonw_ray_moves.push_back(capture_move);

				goto end;
			}

			// Else just generate a normal move.
			struct Move setonw_move;
			setonw_move.Piece = piece_type;
			setonw_move.Move[0] = _strdup(Board64Strings1D[square_key]);
			setonw_move.Move[1] = _strdup(Board64Strings1D[i]);
			setonw_ray_moves.push_back(setonw_move);
		}
	}

end:
	return setonw_ray_moves;
}

std::vector<struct Move> generateMoves(struct Game *game) {
	std::vector<struct Move> moves;

	if (game->SideToMove == 0) { // white to move
		// Generate pawn moves.
		int white_pawn_keys[8] = { -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing white pawns

		// Collect all the bit positions with occupying pawns.
		int counter = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::whitePawnBitboard, i) == 1) {
				white_pawn_keys[counter] = i;
				++counter;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 8; ++counter) {
			if (white_pawn_keys[counter] == -1) break;

			bool second_rank_flag = false; // If true then consider two square pawn moves. Set to false by default.

			// Now check square immediately in front of the pawn. If there is a piece in the way, no need to consider two square moves.
			if (getBit(Bitboard::whitePawnBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteKnightBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteBishopBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteRookBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteQueenBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteKingBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;
			if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 8) == 1) goto capture_moves;

			// Add the one square move since if the program didn't jump to capture_moves then this is permissible (for a pseudo-legal
			// move generator).
			struct Move pawn_one_square_move;
			pawn_one_square_move.Piece = 'P';
			pawn_one_square_move.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
			pawn_one_square_move.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 8]); // one square in front ending square
			moves.push_back(pawn_one_square_move);

			// Check if ending square is on the 8th rank (in which case we have to add info for the promotion and also add additional moves to
			// represent each promotion piece.
			if (white_pawn_keys[counter] + 8 > 55) {
				// pop the last move first since we need more info
				moves.pop_back();

				// add 4 moves: 1 for each promotion piece
				struct Move pawn_prom_move_1;
				pawn_prom_move_1.Piece = 'P';
				pawn_prom_move_1.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
				pawn_prom_move_1.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 8]); // one square in front ending square
				pawn_prom_move_1.IsPromotion = 1;
				pawn_prom_move_1.PromotionPiece = 'N';
				moves.push_back(pawn_prom_move_1);

				struct Move pawn_prom_move_2;
				pawn_prom_move_2.Piece = 'P';
				pawn_prom_move_2.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
				pawn_prom_move_2.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 8]); // one square in front ending square
				pawn_prom_move_2.IsPromotion = 1;
				pawn_prom_move_2.PromotionPiece = 'B';
				moves.push_back(pawn_prom_move_2);

				struct Move pawn_prom_move_3;
				pawn_prom_move_3.Piece = 'P';
				pawn_prom_move_3.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
				pawn_prom_move_3.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 8]); // one square in front ending square
				pawn_prom_move_3.IsPromotion = 1;
				pawn_prom_move_3.PromotionPiece = 'R';
				moves.push_back(pawn_prom_move_3);

				struct Move pawn_prom_move_4;
				pawn_prom_move_4.Piece = 'P';
				pawn_prom_move_4.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
				pawn_prom_move_4.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 8]); // one square in front ending square
				pawn_prom_move_4.IsPromotion = 1;
				pawn_prom_move_4.PromotionPiece = 'Q';
				moves.push_back(pawn_prom_move_4);
			}

			// Now check two squares in front of the pawn.
			if (getBit(Bitboard::whitePawnBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteKnightBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteBishopBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteRookBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteQueenBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::whiteKingBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;
			if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 16) == 1) goto capture_moves;

			// Add the two square move if pawn is on second rank since if the program didn't jump to capture_moves then this is permissible (for a pseudo-legal
			// move generator).
			if ((white_pawn_keys[counter] < 16) && (white_pawn_keys[counter] > 7)) {
				struct Move pawn_two_square_move;
				pawn_two_square_move.Piece = 'P';
				pawn_two_square_move.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
				pawn_two_square_move.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 16]); // two squares in front ending square
				moves.push_back(pawn_two_square_move);
			}

		capture_moves: // jump label for capture moves if two square moves don't need to be checked
			// Don't want to capture any white piece (same color). Check for these first.
			if (getBit(Bitboard::whitePawnBitboard, white_pawn_keys[counter] + 7) == 0) {
				if (getBit(Bitboard::whiteKnightBitboard, white_pawn_keys[counter] + 7) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_pawn_keys[counter] + 7) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_pawn_keys[counter] + 7) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_pawn_keys[counter] + 7) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_pawn_keys[counter] + 7) == 0) {
									// A piece must still be present. Check to make sure there is one legal black piece before making the move (covers all non en passant captures).
									if ((getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 7) == 1) ||
										(getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 7) == 1) ||
										(getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 7) == 1) ||
										(getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 7) == 1) ||
										(getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 7) == 1) ||
										(getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 7) == 1)) {
										// add a left capture move (from POV of side to move)
										struct Move pawn_left_capture_move;
										pawn_left_capture_move.Piece = 'P';
										pawn_left_capture_move.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]);
										pawn_left_capture_move.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 7]);

										// Find the captured piece.
										if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'p'; // captured piece is a black pawn
										}
										else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'n';
										}
										else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'b';
										}
										else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'r';
										}
										else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'q';
										}
										else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'k';
										}

										moves.push_back(pawn_left_capture_move);

										// Check if ending square is on the 8th rank (in which case we have to add info for the promotion and also add additional moves to
										// represent each promotion piece.
										if (white_pawn_keys[counter] + 7 > 55) {
											// pop the last move first since we need more info
											moves.pop_back();

											// add 4 moves: 1 for each promotion piece
											struct Move pawn_prom_left_move_1;
											pawn_prom_left_move_1.Piece = 'P';
											pawn_prom_left_move_1.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_1.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 7]); // one square in front and to the left ending square
											pawn_prom_left_move_1.IsPromotion = 1;
											pawn_prom_left_move_1.PromotionPiece = 'N';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'k';
											}

											moves.push_back(pawn_prom_left_move_1);

											struct Move pawn_prom_left_move_2;
											pawn_prom_left_move_2.Piece = 'P';
											pawn_prom_left_move_2.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_2.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 7]); // one square in front and to the left ending square
											pawn_prom_left_move_2.IsPromotion = 1;
											pawn_prom_left_move_2.PromotionPiece = 'B';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'k';
											}

											moves.push_back(pawn_prom_left_move_2);

											struct Move pawn_prom_left_move_3;
											pawn_prom_left_move_3.Piece = 'P';
											pawn_prom_left_move_3.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_3.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 7]); // one square in front and to the left ending square
											pawn_prom_left_move_3.IsPromotion = 1;
											pawn_prom_left_move_3.PromotionPiece = 'R';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'k';
											}

											moves.push_back(pawn_prom_left_move_3);

											struct Move pawn_prom_left_move_4;
											pawn_prom_left_move_4.Piece = 'P';
											pawn_prom_left_move_4.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_4.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 7]); // one square in front and to the left ending square
											pawn_prom_left_move_4.IsPromotion = 1;
											pawn_prom_left_move_4.PromotionPiece = 'Q';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'k';
											}

											moves.push_back(pawn_prom_left_move_4);
										}
									}
									// en passant captures to the left
									else if ((getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] - 1) == 1) &&
											 (game->EnPassantTargetSquare == board64ToOffset(white_pawn_keys[counter] - 1))) {
										// Add en passant to the left move.
										struct Move en_passant_left_move;
										en_passant_left_move.Piece = 'P';
										en_passant_left_move.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
										en_passant_left_move.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 7]); // one square in front and to the left ending square
										en_passant_left_move.CapturedPiece = 'p'; // in an en passant capture the captured piece is always a pawn
										moves.push_back(en_passant_left_move);
									}
								}
							}
						}
					}
				}
			}
			// Don't want to capture any white piece (same color). Check for these first.
			if (getBit(Bitboard::whitePawnBitboard, white_pawn_keys[counter] + 9) == 0) {
				if (getBit(Bitboard::whiteKnightBitboard, white_pawn_keys[counter] + 9) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_pawn_keys[counter] + 9) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_pawn_keys[counter] + 9) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_pawn_keys[counter] + 9) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_pawn_keys[counter] + 9) == 0) {
									// A piece must still be present. Check to make sure there is one legal black piece before making the move (covers all non en passant captures).
									if ((getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 9) == 1) ||
										(getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 9) == 1) ||
										(getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 9) == 1) ||
										(getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 9) == 1) ||
										(getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 9) == 1) ||
										(getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 9) == 1)) {
										// add a right capture move (from POV of side to move)
										struct Move pawn_right_capture_move;
										pawn_right_capture_move.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]);
										pawn_right_capture_move.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 9]);

										// Find the captured piece.
										if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'p'; // captured piece is a black pawn
										}
										else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'n';
										}
										else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'b';
										}
										else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'r';
										}
										else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'q';
										}
										else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'k';
										}

										moves.push_back(pawn_right_capture_move);

										// Check if ending square is on the 8th rank (in which case we have to add info for the promotion and also add additional moves to
										// represent each promotion piece.
										if (white_pawn_keys[counter] + 9 > 55) {
											// pop the last move first since we need more info
											moves.pop_back();

											// add 4 moves: 1 for each promotion piece
											struct Move pawn_prom_right_move_1;
											pawn_prom_right_move_1.Piece = 'P';
											pawn_prom_right_move_1.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_1.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 9]); // one square in front and to the left ending square
											pawn_prom_right_move_1.IsPromotion = 1;
											pawn_prom_right_move_1.PromotionPiece = 'N';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'k';
											}

											moves.push_back(pawn_prom_right_move_1);

											struct Move pawn_prom_right_move_2;
											pawn_prom_right_move_2.Piece = 'P';
											pawn_prom_right_move_2.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_2.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 9]); // one square in front and to the left ending square
											pawn_prom_right_move_2.IsPromotion = 1;
											pawn_prom_right_move_2.PromotionPiece = 'B';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'k';
											}

											moves.push_back(pawn_prom_right_move_2);

											struct Move pawn_prom_right_move_3;
											pawn_prom_right_move_3.Piece = 'P';
											pawn_prom_right_move_3.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_3.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 9]); // one square in front and to the left ending square
											pawn_prom_right_move_3.IsPromotion = 1;
											pawn_prom_right_move_3.PromotionPiece = 'R';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'k';
											}

											moves.push_back(pawn_prom_right_move_3);

											struct Move pawn_prom_right_move_4;
											pawn_prom_right_move_4.Piece = 'P';
											pawn_prom_right_move_4.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_4.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 9]); // one square in front and to the left ending square
											pawn_prom_right_move_4.IsPromotion = 1;
											pawn_prom_right_move_4.PromotionPiece = 'Q';

											// Find the captured piece.
											if (getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'p'; // captured piece is a black pawn
											}
											else if (getBit(Bitboard::blackKnightBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'n';
											}
											else if (getBit(Bitboard::blackBishopBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'b';
											}
											else if (getBit(Bitboard::blackRookBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'r';
											}
											else if (getBit(Bitboard::blackQueenBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'q';
											}
											else if (getBit(Bitboard::blackKingBitboard, white_pawn_keys[counter] + 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'k';
											}


											moves.push_back(pawn_prom_right_move_4);
										}
									}
									// en passant captures to the right
									else if ((getBit(Bitboard::blackPawnBitboard, white_pawn_keys[counter] + 1) == 1) &&
											 (game->EnPassantTargetSquare == board64ToOffset(white_pawn_keys[counter] + 1))) {
										// Add en passant to the right move.
										struct Move en_passant_right_move;
										en_passant_right_move.Piece = 'P';
										en_passant_right_move.Move[0] = _strdup(Board64Strings1D[white_pawn_keys[counter]]); // starting square
										en_passant_right_move.Move[1] = _strdup(Board64Strings1D[white_pawn_keys[counter] + 9]); // one square in front and to the right ending square
										en_passant_right_move.CapturedPiece = 'p'; // in an en passant capture the captured piece is always a pawn
										moves.push_back(en_passant_right_move);
									}
								}
							}
						}
					}
				}
			}
		}
		
		// Generate knight moves.
		int white_knight_keys[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // holds bit positions for existing white knights (max of 10 possible)

		// Collect all the bit positions with occupying knights.
		int counter_n = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::whiteKnightBitboard, i) == 1) {
				white_knight_keys[counter_n] = i;
				++counter_n;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 10; ++counter) {
			if (white_knight_keys[counter] == -1) break;

			// Break into 8 possible moves. Check to make sure they don't go off the board. The numbering scheme for knight moves is
			// listed below.
			//   1 2
			// 3     4
			//
			// 5     6
			//   7 8
			if (white_knight_keys[counter] + 15 > 63) goto white_knight_move_2_label; // out of bounds
			if (white_knight_keys[counter] % 8 == 0) goto white_knight_move_2_label; // knight is on the a file (1, 3, 5, 7)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] + 15) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] + 15) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] + 15) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] + 15) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] + 15) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] + 15) == 0) {
									// move can be made
									struct Move white_knight_move_1;
									white_knight_move_1.Piece = 'N';
									white_knight_move_1.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_1.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] + 15]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] + 15) == 1) {
										white_knight_move_1.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] + 15) == 1) {
										white_knight_move_1.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] + 15) == 1) {
										white_knight_move_1.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] + 15) == 1) {
										white_knight_move_1.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] + 15) == 1) {
										white_knight_move_1.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_1);
								}
							}
						}
					}
				}
			}

		white_knight_move_2_label:
			if (white_knight_keys[counter] + 17 > 63) goto white_knight_move_3_label;
			if ((white_knight_keys[counter] + 1) % 8 == 0) goto white_knight_move_3_label; // knight is on the h file (2, 4, 6, 8)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] + 17) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] + 17) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] + 17) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] + 17) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] + 17) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] + 17) == 0) {
									// move can be made
									struct Move white_knight_move_2;
									white_knight_move_2.Piece = 'N';
									white_knight_move_2.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_2.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] + 17]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] + 17) == 1) {
										white_knight_move_2.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] + 17) == 1) {
										white_knight_move_2.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] + 17) == 1) {
										white_knight_move_2.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] + 17) == 1) {
										white_knight_move_2.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] + 17) == 1) {
										white_knight_move_2.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_2);
								}
							}
						}
					}
				}
			}

		white_knight_move_3_label:
			if (white_knight_keys[counter] + 6 > 63) goto white_knight_move_4_label;
			if (white_knight_keys[counter] % 8 == 0) goto white_knight_move_4_label; // knight is on the a file (1, 3, 5, 7)
			if ((white_knight_keys[counter] - 1) % 8 == 0) goto white_knight_move_4_label; // knight is on the b file (3, 5)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] + 6) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] + 6) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] + 6) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] + 6) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] + 6) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] + 6) == 0) {
									// move can be made
									struct Move white_knight_move_3;
									white_knight_move_3.Piece = 'N';
									white_knight_move_3.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_3.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] + 6]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] + 6) == 1) {
										white_knight_move_3.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] + 6) == 1) {
										white_knight_move_3.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] + 6) == 1) {
										white_knight_move_3.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] + 6) == 1) {
										white_knight_move_3.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] + 6) == 1) {
										white_knight_move_3.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_3);
								}
							}
						}
					}
				}
			}

		white_knight_move_4_label:
			if (white_knight_keys[counter] + 10 > 63) goto white_knight_move_5_label;
			if ((white_knight_keys[counter] + 1) % 8 == 0) goto white_knight_move_5_label; // knight is on the h file (2, 4, 6, 8)
			if ((white_knight_keys[counter] + 2) % 8 == 0) goto white_knight_move_5_label; // knight is on the g file (4, 6)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] + 10) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] + 10) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] + 10) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] + 10) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] + 10) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] + 10) == 0) {
									// move can be made
									struct Move white_knight_move_4;
									white_knight_move_4.Piece = 'N';
									white_knight_move_4.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_4.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] + 10]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] + 10) == 1) {
										white_knight_move_4.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] + 10) == 1) {
										white_knight_move_4.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] + 10) == 1) {
										white_knight_move_4.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] + 10) == 1) {
										white_knight_move_4.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] + 10) == 1) {
										white_knight_move_4.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_4);
								}
							}
						}
					}
				}
			}

		white_knight_move_5_label:
			if (white_knight_keys[counter] - 10 < 0) goto white_knight_move_6_label;
			if (white_knight_keys[counter] % 8 == 0) goto white_knight_move_6_label; // knight is on the a file (1, 3, 5, 7)
			if ((white_knight_keys[counter] - 1) % 8 == 0) goto white_knight_move_6_label; // knight is on the b file (3, 5)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] - 10) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] - 10) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] - 10) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] - 10) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] - 10) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] - 10) == 0) {
									// move can be made
									struct Move white_knight_move_5;
									white_knight_move_5.Piece = 'N';
									white_knight_move_5.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_5.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] - 10]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] - 10) == 1) {
										white_knight_move_5.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] - 10) == 1) {
										white_knight_move_5.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] - 10) == 1) {
										white_knight_move_5.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] - 10) == 1) {
										white_knight_move_5.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] - 10) == 1) {
										white_knight_move_5.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_5);
								}
							}
						}
					}
				}
			}

		white_knight_move_6_label:
			if (white_knight_keys[counter] - 6 < 0) goto white_knight_move_7_label;
			if ((white_knight_keys[counter] + 1) % 8 == 0) goto white_knight_move_7_label; // knight is on the h file (2, 4, 6, 8)
			if ((white_knight_keys[counter] + 2) % 8 == 0) goto white_knight_move_7_label; // knight is on the g file (4, 6)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] - 6) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] - 6) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] - 6) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] - 6) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] - 6) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] - 6) == 0) {
									// move can be made
									struct Move white_knight_move_6;
									white_knight_move_6.Piece = 'N';
									white_knight_move_6.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_6.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] - 6]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] - 6) == 1) {
										white_knight_move_6.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] - 6) == 1) {
										white_knight_move_6.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] - 6) == 1) {
										white_knight_move_6.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] - 6) == 1) {
										white_knight_move_6.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] - 6) == 1) {
										white_knight_move_6.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_6);
								}
							}
						}
					}
				}
			}

		white_knight_move_7_label:
			if (white_knight_keys[counter] - 17 < 0) goto white_knight_move_8_label;
			if (white_knight_keys[counter] % 8 == 0) goto white_knight_move_8_label; // knight is on the a file (1, 3, 5, 7)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] - 17) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] - 17) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] - 17) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] - 17) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] - 17) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] - 17) == 0) {
									// move can be made
									struct Move white_knight_move_7;
									white_knight_move_7.Piece = 'N';
									white_knight_move_7.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_7.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] - 17]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] - 17) == 1) {
										white_knight_move_7.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] - 17) == 1) {
										white_knight_move_7.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] - 17) == 1) {
										white_knight_move_7.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] - 17) == 1) {
										white_knight_move_7.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] - 17) == 1) {
										white_knight_move_7.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_7);
								}
							}
						}
					}
				}
			}

		white_knight_move_8_label:
			if (white_knight_keys[counter] - 15 < 0) goto white_knight_moves_end;
			if ((white_knight_keys[counter] + 1) % 8 == 0) goto white_knight_moves_end; // knight is on the h file (2, 4, 6, 8)
			if (getBit(Bitboard::whitePawnBitboard, white_knight_keys[counter] - 15) == 0) { // check for same color pieces
				if (getBit(Bitboard::whiteKnightBitboard, white_knight_keys[counter] - 15) == 0) {
					if (getBit(Bitboard::whiteBishopBitboard, white_knight_keys[counter] - 15) == 0) {
						if (getBit(Bitboard::whiteRookBitboard, white_knight_keys[counter] - 15) == 0) {
							if (getBit(Bitboard::whiteQueenBitboard, white_knight_keys[counter] - 15) == 0) {
								if (getBit(Bitboard::whiteKingBitboard, white_knight_keys[counter] - 15) == 0) {
									// move can be made
									struct Move white_knight_move_8;
									white_knight_move_8.Piece = 'N';
									white_knight_move_8.Move[0] = _strdup(Board64Strings1D[white_knight_keys[counter]]);
									white_knight_move_8.Move[1] = _strdup(Board64Strings1D[white_knight_keys[counter] - 15]);

									// Find the captured piece if any.
									if (getBit(Bitboard::blackPawnBitboard, white_knight_keys[counter] - 15) == 1) {
										white_knight_move_8.CapturedPiece = 'p'; // captured piece is a black pawn
									}
									else if (getBit(Bitboard::blackKnightBitboard, white_knight_keys[counter] - 15) == 1) {
										white_knight_move_8.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::blackBishopBitboard, white_knight_keys[counter] - 15) == 1) {
										white_knight_move_8.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::blackRookBitboard, white_knight_keys[counter] - 15) == 1) {
										white_knight_move_8.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::blackQueenBitboard, white_knight_keys[counter] - 15) == 1) {
										white_knight_move_8.CapturedPiece = 'q';
									}

									moves.push_back(white_knight_move_8);
								}
							}
						}
					}
				}
			}

		white_knight_moves_end:
			;

		}

		// Generate bishop moves.
		int white_bishop_keys[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing white bishops (max of 10 possible)

		// Collect all the bit positions with occupying bishops.
		int counter_b = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::whiteBishopBitboard, i) == 1) {
				white_bishop_keys[counter_b] = i;
				++counter_b;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 10; ++counter) {
			if (white_bishop_keys[counter] == -1) break;

			// get the move lists for the diagonal rays
			std::vector<struct Move> swtone_ray_moves_list = generateSouthwestToNortheastRay(white_bishop_keys[counter], 0, 'B');
			std::vector<struct Move> setonw_ray_moves_list = generateSoutheastToNorthwestRay(white_bishop_keys[counter], 0, 'B');

			// append the diagonal rays moves lists to the main move list
			moves.insert(moves.end(), swtone_ray_moves_list.begin(), swtone_ray_moves_list.end());
			moves.insert(moves.end(), setonw_ray_moves_list.begin(), setonw_ray_moves_list.end());
		}

		// Generate rook moves.
		int white_rook_keys[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing white rooks (max of 10 possible)

		// Collect all the bit positions with occupying rooks.
		int counter_r = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::whiteRookBitboard, i) == 1) {
				white_rook_keys[counter_r] = i;
				++counter_r;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 10; ++counter) {
			if (white_rook_keys[counter] == -1) break;

			// get the move lists for the horizontal and vertical rays
			std::vector<struct Move> horizontal_ray_moves_list = generateHorizontalRay(white_rook_keys[counter], 0, 'R');
			std::vector<struct Move> vertical_ray_moves_list = generateVerticalRay(white_rook_keys[counter], 0, 'R');

			// append the horizontal and vertical rays moves lists to the main move list
			moves.insert(moves.end(), horizontal_ray_moves_list.begin(), horizontal_ray_moves_list.end());
			moves.insert(moves.end(), vertical_ray_moves_list.begin(), vertical_ray_moves_list.end());
		}

		// Generate queen moves.
		int white_queen_keys[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing white rooks (max of 9 possible)

		// Collect all the bit positions with occupying queens.
		int counter_q = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::whiteQueenBitboard, i) == 1) {
				white_queen_keys[counter_q] = i;
				++counter_q;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 9; ++counter) {
			if (white_queen_keys[counter] == -1) break;

			// get the move lists for the 4 different rays
			std::vector<struct Move> swtone_ray_moves_list = generateSouthwestToNortheastRay(white_queen_keys[counter], 0, 'Q');
			std::vector<struct Move> setonw_ray_moves_list = generateSoutheastToNorthwestRay(white_queen_keys[counter], 0, 'Q');
			std::vector<struct Move> horizontal_ray_moves_list = generateHorizontalRay(white_queen_keys[counter], 0, 'Q');
			std::vector<struct Move> vertical_ray_moves_list = generateVerticalRay(white_queen_keys[counter], 0, 'Q');

			// append the moves lists to the main list
			moves.insert(moves.end(), swtone_ray_moves_list.begin(), swtone_ray_moves_list.end());
			moves.insert(moves.end(), setonw_ray_moves_list.begin(), setonw_ray_moves_list.end());
			moves.insert(moves.end(), horizontal_ray_moves_list.begin(), horizontal_ray_moves_list.end());
			moves.insert(moves.end(), vertical_ray_moves_list.begin(), vertical_ray_moves_list.end());
		}

		// Generate king moves.
		int white_king_key = -1;

		// Find the square where the white king is.
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::whiteKingBitboard, i) == 1) {
				white_king_key = i;
				break;
			}
		}

		// Break into 8 different moves which are listed below.
		// 1 2 3
		// 4   5
		// 6 7 8

		// move 1
		if (white_king_key > 55) goto white_king_move_4_label; // white king is on 8th rank (1, 2, and 3 not legal)
		if (white_king_key % 8 == 0) goto white_king_move_2_label; // white king is on left edge (1, 4, and 6 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key + 7) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key + 7) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key + 7) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key + 7) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key + 7) == 0) {
							// move can be made
							struct Move white_king_move_1;
							white_king_move_1.Piece = 'K';
							white_king_move_1.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_1.Move[1] = _strdup(Board64Strings1D[white_king_key + 7]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key + 7) == 1) {
								white_king_move_1.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key + 7) == 1) {
								white_king_move_1.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key + 7) == 1) {
								white_king_move_1.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key + 7) == 1) {
								white_king_move_1.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key + 7) == 1) {
								white_king_move_1.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_1);
						}
					}
				}
			}
		}

	white_king_move_2_label:
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key + 8) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key + 8) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key + 8) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key + 8) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key + 8) == 0) {
							// move can be made
							struct Move white_king_move_2;
							white_king_move_2.Piece = 'K';
							white_king_move_2.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_2.Move[1] = _strdup(Board64Strings1D[white_king_key + 8]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key + 8) == 1) {
								white_king_move_2.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key + 8) == 1) {
								white_king_move_2.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key + 8) == 1) {
								white_king_move_2.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key + 8) == 1) {
								white_king_move_2.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key + 8) == 1) {
								white_king_move_2.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_2);
						}
					}
				}
			}
		}

	white_king_move_3_label:
		if ((white_king_key + 1) % 8 == 0) goto white_king_move_4_label; // white king is on right edge (3, 5, and 8 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key + 9) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key + 9) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key + 9) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key + 9) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key + 9) == 0) {
							// move can be made
							struct Move white_king_move_3;
							white_king_move_3.Piece = 'K';
							white_king_move_3.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_3.Move[1] = _strdup(Board64Strings1D[white_king_key + 9]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key + 9) == 1) {
								white_king_move_3.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key + 9) == 1) {
								white_king_move_3.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key + 9) == 1) {
								white_king_move_3.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key + 9) == 1) {
								white_king_move_3.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key + 9) == 1) {
								white_king_move_3.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_3);
						}
					}
				}
			}
		}

	white_king_move_4_label:
		if (white_king_key % 8 == 0) goto white_king_move_5_label; // white king is on left edge (1, 4, and 6 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key - 1) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key - 1) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key - 1) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key - 1) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key - 1) == 0) {
							// move can be made
							struct Move white_king_move_4;
							white_king_move_4.Piece = 'K';
							white_king_move_4.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_4.Move[1] = _strdup(Board64Strings1D[white_king_key - 1]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key - 1) == 1) {
								white_king_move_4.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key - 1) == 1) {
								white_king_move_4.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key - 1) == 1) {
								white_king_move_4.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key - 1) == 1) {
								white_king_move_4.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key - 1) == 1) {
								white_king_move_4.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_4);
						}
					}
				}
			}
		}

	white_king_move_5_label:
		if ((white_king_key + 1) % 8 == 0) goto white_king_move_6_label; // white king is on right edge (3, 5, and 8 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key + 1) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key + 1) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key + 1) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key + 1) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key + 1) == 0) {
							// move can be made
							struct Move white_king_move_5;
							white_king_move_5.Piece = 'K';
							white_king_move_5.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_5.Move[1] = _strdup(Board64Strings1D[white_king_key + 1]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key + 1) == 1) {
								white_king_move_5.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key + 1) == 1) {
								white_king_move_5.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key + 1) == 1) {
								white_king_move_5.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key + 1) == 1) {
								white_king_move_5.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key + 1) == 1) {
								white_king_move_5.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_5);
						}
					}
				}
			}
		}

	white_king_move_6_label:
		if (white_king_key < 8) goto white_king_moves_end; // white king is on 1st rank (6, 7, and 8 not legal)
		if (white_king_key % 8 == 0) goto white_king_move_7_label; // white king is on left edge (1, 4, and 6 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key - 9) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key - 9) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key - 9) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key - 9) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key - 9) == 0) {
							// move can be made
							struct Move white_king_move_6;
							white_king_move_6.Piece = 'K';
							white_king_move_6.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_6.Move[1] = _strdup(Board64Strings1D[white_king_key - 9]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key - 9) == 1) {
								white_king_move_6.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key - 9) == 1) {
								white_king_move_6.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key - 9) == 1) {
								white_king_move_6.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key - 9) == 1) {
								white_king_move_6.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key - 9) == 1) {
								white_king_move_6.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_6);
						}
					}
				}
			}
		}

	white_king_move_7_label:
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key - 8) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key - 8) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key - 8) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key - 8) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key - 8) == 0) {
							// move can be made
							struct Move white_king_move_7;
							white_king_move_7.Piece = 'K';
							white_king_move_7.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_7.Move[1] = _strdup(Board64Strings1D[white_king_key - 8]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key - 8) == 1) {
								white_king_move_7.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key - 8) == 1) {
								white_king_move_7.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key - 8) == 1) {
								white_king_move_7.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key - 8) == 1) {
								white_king_move_7.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key - 8) == 1) {
								white_king_move_7.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_7);
						}
					}
				}
			}
		}

	white_king_move_8_label:
		if ((white_king_key + 1) % 8 == 0) goto white_king_moves_end; // white king is on right edge (3, 5, and 8 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::whitePawnBitboard, white_king_key - 7) == 0) {
			if (getBit(Bitboard::whiteKnightBitboard, white_king_key - 7) == 0) {
				if (getBit(Bitboard::whiteBishopBitboard, white_king_key - 7) == 0) {
					if (getBit(Bitboard::whiteRookBitboard, white_king_key - 7) == 0) {
						if (getBit(Bitboard::whiteQueenBitboard, white_king_key - 7) == 0) {
							// move can be made
							struct Move white_king_move_8;
							white_king_move_8.Piece = 'K';
							white_king_move_8.Move[0] = _strdup(Board64Strings1D[white_king_key]);
							white_king_move_8.Move[1] = _strdup(Board64Strings1D[white_king_key - 7]);

							// Find the captured piece if any.
							if (getBit(Bitboard::blackPawnBitboard, white_king_key - 7) == 1) {
								white_king_move_8.CapturedPiece = 'p'; // captured piece is a black pawn
							}
							else if (getBit(Bitboard::blackKnightBitboard, white_king_key - 7) == 1) {
								white_king_move_8.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::blackBishopBitboard, white_king_key - 7) == 1) {
								white_king_move_8.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::blackRookBitboard, white_king_key - 7) == 1) {
								white_king_move_8.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::blackQueenBitboard, white_king_key - 7) == 1) {
								white_king_move_8.CapturedPiece = 'q';
							}

							moves.push_back(white_king_move_8);
						}
					}
				}
			}
		}

	white_king_moves_end:
		;
	}
	else { // black to move
		// Generate pawn moves.
		int black_pawn_keys[8] = { -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing white pawns

		// Collect all the bit positions with occupying pawns.
		int counter = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::blackPawnBitboard, i) == 1) {
				black_pawn_keys[counter] = i;
				++counter;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 8; ++counter) {
			if (black_pawn_keys[counter] == -1) break;

			bool second_rank_flag = false; // If true then consider two square pawn moves. Set to false by default.

			// Now check square immediately in front of the pawn. If there is a piece in the way, no need to consider two square moves.
			if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackPawnBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackKnightBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackBishopBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackRookBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackQueenBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackKingBitboard, black_pawn_keys[counter] - 8) == 1) goto capture_moves_black;

			// Add the one square move since if the program didn't jump to capture_moves then this is permissible (for a pseudo-legal
			// move generator).
			struct Move pawn_one_square_move;
			pawn_one_square_move.Piece = 'p';
			pawn_one_square_move.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
			pawn_one_square_move.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 8]); // one square in front ending square
			moves.push_back(pawn_one_square_move);

			// Check if ending square is on the 1st rank (in which case we have to add info for the promotion and also add additional moves to
			// represent each promotion piece.
			if (black_pawn_keys[counter] - 8 < 8) {
				// pop the last move first since we need more info
				moves.pop_back();

				// add 4 moves: 1 for each promotion piece
				struct Move pawn_prom_move_1;
				pawn_prom_move_1.Piece = 'p';
				pawn_prom_move_1.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
				pawn_prom_move_1.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 8]); // one square in front ending square
				pawn_prom_move_1.IsPromotion = 1;
				pawn_prom_move_1.PromotionPiece = 'n';
				moves.push_back(pawn_prom_move_1);

				struct Move pawn_prom_move_2;
				pawn_prom_move_2.Piece = 'p';
				pawn_prom_move_2.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
				pawn_prom_move_2.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 8]); // one square in front ending square
				pawn_prom_move_2.IsPromotion = 1;
				pawn_prom_move_2.PromotionPiece = 'b';
				moves.push_back(pawn_prom_move_2);

				struct Move pawn_prom_move_3;
				pawn_prom_move_3.Piece = 'p';
				pawn_prom_move_3.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
				pawn_prom_move_3.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 8]); // one square in front ending square
				pawn_prom_move_3.IsPromotion = 1;
				pawn_prom_move_3.PromotionPiece = 'r';
				moves.push_back(pawn_prom_move_3);

				struct Move pawn_prom_move_4;
				pawn_prom_move_4.Piece = 'p';
				pawn_prom_move_4.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
				pawn_prom_move_4.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 8]); // one square in front ending square
				pawn_prom_move_4.IsPromotion = 1;
				pawn_prom_move_4.PromotionPiece = 'q';
				moves.push_back(pawn_prom_move_4);
			}

			// Now check two squares in front of the pawn.
			if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackPawnBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackKnightBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackBishopBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackRookBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackQueenBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;
			if (getBit(Bitboard::blackKingBitboard, black_pawn_keys[counter] - 16) == 1) goto capture_moves_black;

			// Add the two square move if pawn is on seventh rank since if the program didn't jump to capture_moves then this is permissible (for a pseudo-legal
			// move generator).
			if ((black_pawn_keys[counter] < 56) && (black_pawn_keys[counter] > 47)) {
				struct Move pawn_two_square_move;
				pawn_two_square_move.Piece = 'p';
				pawn_two_square_move.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
				pawn_two_square_move.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 16]); // two squares in front ending square
				moves.push_back(pawn_two_square_move);
			}

		capture_moves_black: // jump label for capture moves if two square moves don't need to be checked
			// Don't want to capture any black piece (same color). Check for these first.
			if (getBit(Bitboard::blackPawnBitboard, black_pawn_keys[counter] - 7) == 0) {
				if (getBit(Bitboard::blackKnightBitboard, black_pawn_keys[counter] - 7) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_pawn_keys[counter] - 7) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_pawn_keys[counter] - 7) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_pawn_keys[counter] - 7) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_pawn_keys[counter] - 7) == 0) {
									// A piece must still be present. Check to make sure there is one legal white piece before making the move (covers all non en passant captures).
									if ((getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 7) == 1) ||
										(getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 7) == 1) ||
										(getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 7) == 1) ||
										(getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 7) == 1) ||
										(getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 7) == 1) ||
										(getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 7) == 1)) {
										// add a left capture move (from POV of side to move)
										struct Move pawn_left_capture_move;
										pawn_left_capture_move.Piece = 'p';
										pawn_left_capture_move.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]);
										pawn_left_capture_move.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 7]);

										// Find the captured piece.
										if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'P'; // captured piece is a white pawn
										}
										else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'N';
										}
										else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'B';
										}
										else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'R';
										}
										else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'Q';
										}
										else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 7) == 1) {
											pawn_left_capture_move.CapturedPiece = 'K';
										}

										moves.push_back(pawn_left_capture_move);

										// Check if ending square is on the 1st rank (in which case we have to add info for the promotion and also add additional moves to
										// represent each promotion piece.
										if (black_pawn_keys[counter] - 7 < 8) {
											// pop the last move first since we need more info
											moves.pop_back();

											// add 4 moves: 1 for each promotion piece
											struct Move pawn_prom_left_move_1;
											pawn_prom_left_move_1.Piece = 'p';
											pawn_prom_left_move_1.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_1.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 7]); // one square in front and to the left ending square
											pawn_prom_left_move_1.IsPromotion = 1;
											pawn_prom_left_move_1.PromotionPiece = 'n';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_1.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_left_move_1);

											struct Move pawn_prom_left_move_2;
											pawn_prom_left_move_2.Piece = 'p';
											pawn_prom_left_move_2.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_2.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 7]); // one square in front and to the left ending square
											pawn_prom_left_move_2.IsPromotion = 1;
											pawn_prom_left_move_2.PromotionPiece = 'b';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_2.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_left_move_2);

											struct Move pawn_prom_left_move_3;
											pawn_prom_left_move_3.Piece = 'p';
											pawn_prom_left_move_3.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_3.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 7]); // one square in front and to the left ending square
											pawn_prom_left_move_3.IsPromotion = 1;
											pawn_prom_left_move_3.PromotionPiece = 'r';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_3.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_left_move_3);

											struct Move pawn_prom_left_move_4;
											pawn_prom_left_move_4.Piece = 'p';
											pawn_prom_left_move_4.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_left_move_4.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 7]); // one square in front and to the left ending square
											pawn_prom_left_move_4.IsPromotion = 1;
											pawn_prom_left_move_4.PromotionPiece = 'q';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 7) == 1) {
												pawn_prom_left_move_4.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_left_move_4);
										}
									}
									// en passant captures to the left
									else if ((getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] + 1) == 1) &&
										(game->EnPassantTargetSquare == board64ToOffset(black_pawn_keys[counter] + 1))) {
										// Add en passant to the left move.
										struct Move en_passant_left_move;
										en_passant_left_move.Piece = 'p';
										en_passant_left_move.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
										en_passant_left_move.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 7]); // one square in front and to the left ending square
										en_passant_left_move.CapturedPiece = 'P'; // in an en passant capture the captured piece is always a pawn
										moves.push_back(en_passant_left_move);
									}
								}
							}
						}
					}
				}
			}
			// Don't want to capture any black piece (same color). Check for these first.
			if (getBit(Bitboard::blackPawnBitboard, black_pawn_keys[counter] - 9) == 0) {
				if (getBit(Bitboard::blackKnightBitboard, black_pawn_keys[counter] - 9) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_pawn_keys[counter] - 9) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_pawn_keys[counter] - 9) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_pawn_keys[counter] - 9) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_pawn_keys[counter] - 9) == 0) {
									// A piece must still be present. Check to make sure there is one legal white piece before making the move (covers all non en passant captures).
									if ((getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 9) == 1) ||
										(getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 9) == 1) ||
										(getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 9) == 1) ||
										(getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 9) == 1) ||
										(getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 9) == 1) ||
										(getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 9) == 1)) {
										// add a right capture move (from POV of side to move)
										struct Move pawn_right_capture_move;
										pawn_right_capture_move.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]);
										pawn_right_capture_move.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 9]);

										// Find the captured piece.
										if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'P'; // captured piece is a white pawn
										}
										else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'N';
										}
										else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'B';
										}
										else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'R';
										}
										else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'Q';
										}
										else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 9) == 1) {
											pawn_right_capture_move.CapturedPiece = 'K';
										}

										moves.push_back(pawn_right_capture_move);

										// Check if ending square is on the 1st rank (in which case we have to add info for the promotion and also add additional moves to
										// represent each promotion piece.
										if (black_pawn_keys[counter] - 9 < 8) {
											// pop the last move first since we need more info
											moves.pop_back();

											// add 4 moves: 1 for each promotion piece
											struct Move pawn_prom_right_move_1;
											pawn_prom_right_move_1.Piece = 'p';
											pawn_prom_right_move_1.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_1.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 9]); // one square in front and to the left ending square
											pawn_prom_right_move_1.IsPromotion = 1;
											pawn_prom_right_move_1.PromotionPiece = 'n';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_1.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_right_move_1);

											struct Move pawn_prom_right_move_2;
											pawn_prom_right_move_2.Piece = 'p';
											pawn_prom_right_move_2.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_2.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 9]); // one square in front and to the left ending square
											pawn_prom_right_move_2.IsPromotion = 1;
											pawn_prom_right_move_2.PromotionPiece = 'b';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_2.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_right_move_2);

											struct Move pawn_prom_right_move_3;
											pawn_prom_right_move_3.Piece = 'p';
											pawn_prom_right_move_3.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_3.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 9]); // one square in front and to the left ending square
											pawn_prom_right_move_3.IsPromotion = 1;
											pawn_prom_right_move_3.PromotionPiece = 'r';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_3.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_right_move_3);

											struct Move pawn_prom_right_move_4;
											pawn_prom_right_move_4.Piece = 'p';
											pawn_prom_right_move_4.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
											pawn_prom_right_move_4.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] - 9]); // one square in front and to the left ending square
											pawn_prom_right_move_4.IsPromotion = 1;
											pawn_prom_right_move_4.PromotionPiece = 'q';

											// Find the captured piece.
											if (getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'P'; // captured piece is a white pawn
											}
											else if (getBit(Bitboard::whiteKnightBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'N';
											}
											else if (getBit(Bitboard::whiteBishopBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'B';
											}
											else if (getBit(Bitboard::whiteRookBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'R';
											}
											else if (getBit(Bitboard::whiteQueenBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'Q';
											}
											else if (getBit(Bitboard::whiteKingBitboard, black_pawn_keys[counter] - 9) == 1) {
												pawn_prom_right_move_4.CapturedPiece = 'K';
											}

											moves.push_back(pawn_prom_right_move_4);
										}
									}
									// en passant captures to the right
									else if ((getBit(Bitboard::whitePawnBitboard, black_pawn_keys[counter] - 1) == 1) &&
										(game->EnPassantTargetSquare == board64ToOffset(black_pawn_keys[counter] - 1))) {
										// Add en passant to the right move.
										struct Move en_passant_right_move;
										en_passant_right_move.Piece = 'p';
										en_passant_right_move.Move[0] = _strdup(Board64Strings1D[black_pawn_keys[counter]]); // starting square
										en_passant_right_move.Move[1] = _strdup(Board64Strings1D[black_pawn_keys[counter] + 9]); // one square in front and to the right ending square
										en_passant_right_move.CapturedPiece = 'P'; // in an en passant capture the captured piece is always a pawn
										moves.push_back(en_passant_right_move);
									}
								}
							}
						}
					}
				}
			}
		}

		// Generate knight moves.
		int black_knight_keys[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing black knights (max of 10 possible)

		// Collect all the bit positions with occupying knights.
		int counter_n = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::blackKnightBitboard, i) == 1) {
				black_knight_keys[counter_n] = i;
				++counter_n;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 10; ++counter) {
			if (black_knight_keys[counter] == -1) break;

			// Break into 8 possible moves. Check to make sure they don't go off the board. The numbering scheme for knight moves is
			// listed below.
			//   1 2
			// 3     4
			//
			// 5     6
			//   7 8
			if (black_knight_keys[counter] + 15 > 63) goto black_knight_move_2_label; // out of bounds
			if (black_knight_keys[counter] % 8 == 0) goto black_knight_move_2_label; // knight is on the a file (1, 3, 5, 7)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] + 15) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] + 15) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] + 15) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] + 15) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] + 15) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] + 15) == 0) {
									// move can be made
									struct Move black_knight_move_1;
									black_knight_move_1.Piece = 'n';
									black_knight_move_1.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_1.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] + 15]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] + 15) == 1) {
										black_knight_move_1.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] + 15) == 1) {
										black_knight_move_1.CapturedPiece = 'n';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] + 15) == 1) {
										black_knight_move_1.CapturedPiece = 'b';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] + 15) == 1) {
										black_knight_move_1.CapturedPiece = 'r';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] + 15) == 1) {
										black_knight_move_1.CapturedPiece = 'q';
									}

									moves.push_back(black_knight_move_1);
								}
							}
						}
					}
				}
			}

		black_knight_move_2_label:
			if (black_knight_keys[counter] + 17 > 63) goto black_knight_move_3_label;
			if ((black_knight_keys[counter] + 1) % 8 == 0) goto black_knight_move_3_label; // knight is on the h file (2, 4, 6, 8)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] + 17) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] + 17) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] + 17) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] + 17) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] + 17) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] + 17) == 0) {
									// move can be made
									struct Move black_knight_move_2;
									black_knight_move_2.Piece = 'n';
									black_knight_move_2.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_2.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] + 17]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] + 17) == 1) {
										black_knight_move_2.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] + 17) == 1) {
										black_knight_move_2.CapturedPiece = 'N';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] + 17) == 1) {
										black_knight_move_2.CapturedPiece = 'B';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] + 17) == 1) {
										black_knight_move_2.CapturedPiece = 'R';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] + 17) == 1) {
										black_knight_move_2.CapturedPiece = 'Q';
									}

									moves.push_back(black_knight_move_2);
								}
							}
						}
					}
				}
			}

		black_knight_move_3_label:
			if (black_knight_keys[counter] + 6 > 63) goto black_knight_move_4_label;
			if (black_knight_keys[counter] % 8 == 0) goto black_knight_move_4_label; // knight is on the a file (1, 3, 5, 7)
			if ((black_knight_keys[counter] - 1) % 8 == 0) goto black_knight_move_4_label; // knight is on the b file (3, 5)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] + 6) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] + 6) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] + 6) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] + 6) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] + 6) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] + 6) == 0) {
									// move can be made
									struct Move black_knight_move_3;
									black_knight_move_3.Piece = 'n';
									black_knight_move_3.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_3.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] + 6]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] + 6) == 1) {
										black_knight_move_3.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] + 6) == 1) {
										black_knight_move_3.CapturedPiece = 'N';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] + 6) == 1) {
										black_knight_move_3.CapturedPiece = 'B';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] + 6) == 1) {
										black_knight_move_3.CapturedPiece = 'R';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] + 6) == 1) {
										black_knight_move_3.CapturedPiece = 'Q';
									}

									moves.push_back(black_knight_move_3);
								}
							}
						}
					}
				}
			}

		black_knight_move_4_label:
			if (black_knight_keys[counter] + 10 > 63) goto black_knight_move_5_label;
			if ((black_knight_keys[counter] + 1) % 8 == 0) goto black_knight_move_5_label; // knight is on the h file (2, 4, 6, 8)
			if ((black_knight_keys[counter] + 2) % 8 == 0) goto black_knight_move_5_label; // knight is on the g file (4, 6)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] + 10) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] + 10) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] + 10) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] + 10) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] + 10) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] + 10) == 0) {
									// move can be made
									struct Move black_knight_move_4;
									black_knight_move_4.Piece = 'N';
									black_knight_move_4.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_4.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] + 10]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] + 10) == 1) {
										black_knight_move_4.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] + 10) == 1) {
										black_knight_move_4.CapturedPiece = 'N';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] + 10) == 1) {
										black_knight_move_4.CapturedPiece = 'B';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] + 10) == 1) {
										black_knight_move_4.CapturedPiece = 'R';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] + 10) == 1) {
										black_knight_move_4.CapturedPiece = 'Q';
									}

									moves.push_back(black_knight_move_4);
								}
							}
						}
					}
				}
			}

		black_knight_move_5_label:
			if (black_knight_keys[counter] - 10 < 0) goto black_knight_move_6_label;
			if (black_knight_keys[counter] % 8 == 0) goto black_knight_move_6_label; // knight is on the a file (1, 3, 5, 7)
			if ((black_knight_keys[counter] - 1) % 8 == 0) goto black_knight_move_6_label; // knight is on the b file (3, 5)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] - 10) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] - 10) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] - 10) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] - 10) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] - 10) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] - 10) == 0) {
									// move can be made
									struct Move black_knight_move_5;
									black_knight_move_5.Piece = 'N';
									black_knight_move_5.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_5.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] - 10]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] - 10) == 1) {
										black_knight_move_5.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] - 10) == 1) {
										black_knight_move_5.CapturedPiece = 'N';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] - 10) == 1) {
										black_knight_move_5.CapturedPiece = 'B';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] - 10) == 1) {
										black_knight_move_5.CapturedPiece = 'R';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] - 10) == 1) {
										black_knight_move_5.CapturedPiece = 'Q';
									}

									moves.push_back(black_knight_move_5);
								}
							}
						}
					}
				}
			}

		black_knight_move_6_label:
			if (black_knight_keys[counter] - 6 < 0) goto black_knight_move_7_label;
			if ((black_knight_keys[counter] + 1) % 8 == 0) goto black_knight_move_7_label; // knight is on the h file (2, 4, 6, 8)
			if ((black_knight_keys[counter] + 2) % 8 == 0) goto black_knight_move_7_label; // knight is on the g file (4, 6)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] - 6) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] - 6) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] - 6) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] - 6) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] - 6) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] - 6) == 0) {
									// move can be made
									struct Move black_knight_move_6;
									black_knight_move_6.Piece = 'n';
									black_knight_move_6.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_6.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] - 6]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] - 6) == 1) {
										black_knight_move_6.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] - 6) == 1) {
										black_knight_move_6.CapturedPiece = 'N';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] - 6) == 1) {
										black_knight_move_6.CapturedPiece = 'B';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] - 6) == 1) {
										black_knight_move_6.CapturedPiece = 'R';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] - 6) == 1) {
										black_knight_move_6.CapturedPiece = 'Q';
									}

									moves.push_back(black_knight_move_6);
								}
							}
						}
					}
				}
			}

		black_knight_move_7_label:
			if (black_knight_keys[counter] - 17 < 0) goto black_knight_move_8_label;
			if (black_knight_keys[counter] % 8 == 0) goto black_knight_move_8_label; // knight is on the a file (1, 3, 5, 7)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] - 17) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] - 17) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] - 17) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] - 17) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] - 17) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] - 17) == 0) {
									// move can be made
									struct Move black_knight_move_7;
									black_knight_move_7.Piece = 'n';
									black_knight_move_7.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_7.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] - 17]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] - 17) == 1) {
										black_knight_move_7.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] - 17) == 1) {
										black_knight_move_7.CapturedPiece = 'N';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] - 17) == 1) {
										black_knight_move_7.CapturedPiece = 'B';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] - 17) == 1) {
										black_knight_move_7.CapturedPiece = 'R';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] - 17) == 1) {
										black_knight_move_7.CapturedPiece = 'Q';
									}

									moves.push_back(black_knight_move_7);
								}
							}
						}
					}
				}
			}

		black_knight_move_8_label:
			if (black_knight_keys[counter] - 15 < 0) goto black_knight_moves_end;
			if ((black_knight_keys[counter] + 1) % 8 == 0) goto black_knight_moves_end; // knight is on the h file (2, 4, 6, 8)
			if (getBit(Bitboard::blackPawnBitboard, black_knight_keys[counter] - 15) == 0) { // check for same color pieces
				if (getBit(Bitboard::blackKnightBitboard, black_knight_keys[counter] - 15) == 0) {
					if (getBit(Bitboard::blackBishopBitboard, black_knight_keys[counter] - 15) == 0) {
						if (getBit(Bitboard::blackRookBitboard, black_knight_keys[counter] - 15) == 0) {
							if (getBit(Bitboard::blackQueenBitboard, black_knight_keys[counter] - 15) == 0) {
								if (getBit(Bitboard::blackKingBitboard, black_knight_keys[counter] - 15) == 0) {
									// move can be made
									struct Move black_knight_move_8;
									black_knight_move_8.Piece = 'n';
									black_knight_move_8.Move[0] = _strdup(Board64Strings1D[black_knight_keys[counter]]);
									black_knight_move_8.Move[1] = _strdup(Board64Strings1D[black_knight_keys[counter] - 15]);

									// Find the captured piece if any.
									if (getBit(Bitboard::whitePawnBitboard, black_knight_keys[counter] - 15) == 1) {
										black_knight_move_8.CapturedPiece = 'P'; // captured piece is a white pawn
									}
									else if (getBit(Bitboard::whiteKnightBitboard, black_knight_keys[counter] - 15) == 1) {
										black_knight_move_8.CapturedPiece = 'N';
									}
									else if (getBit(Bitboard::whiteBishopBitboard, black_knight_keys[counter] - 15) == 1) {
										black_knight_move_8.CapturedPiece = 'B';
									}
									else if (getBit(Bitboard::whiteRookBitboard, black_knight_keys[counter] - 15) == 1) {
										black_knight_move_8.CapturedPiece = 'R';
									}
									else if (getBit(Bitboard::whiteQueenBitboard, black_knight_keys[counter] - 15) == 1) {
										black_knight_move_8.CapturedPiece = 'Q';
									}

									moves.push_back(black_knight_move_8);
								}
							}
						}
					}
				}
			}

		black_knight_moves_end:
			;

		}

		// Generate bishop moves.
		int black_bishop_keys[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing black bishops (max of 10 possible)

		// Collect all the bit positions with occupying bishops.
		int counter_b = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::blackBishopBitboard, i) == 1) {
				black_bishop_keys[counter_b] = i;
				++counter_b;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 10; ++counter) {
			if (black_bishop_keys[counter] == -1) break;

			// get the move lists for the diagonal rays
			std::vector<struct Move> swtone_ray_moves_list = generateSouthwestToNortheastRay(black_bishop_keys[counter], 1, 'b');
			std::vector<struct Move> setonw_ray_moves_list = generateSoutheastToNorthwestRay(black_bishop_keys[counter], 1, 'b');

			// append the diagonal rays moves lists to the main move list
			moves.insert(moves.end(), swtone_ray_moves_list.begin(), swtone_ray_moves_list.end());
			moves.insert(moves.end(), setonw_ray_moves_list.begin(), setonw_ray_moves_list.end());
		}

		// Generate rook moves.
		int black_rook_keys[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing black rooks (max of 10 possible)

		// Collect all the bit positions with occupying rooks.
		int counter_r = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::blackRookBitboard, i) == 1) {
				black_rook_keys[counter_r] = i;
				++counter_r;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 10; ++counter) {
			if (black_rook_keys[counter] == -1) break;

			// get the move lists for the horizontal and vertical rays
			std::vector<struct Move> horizontal_ray_moves_list = generateHorizontalRay(black_rook_keys[counter], 1, 'r');
			std::vector<struct Move> vertical_ray_moves_list = generateVerticalRay(black_rook_keys[counter], 1, 'r');

			// append the horizontal and vertical rays moves lists to the main move list
			moves.insert(moves.end(), horizontal_ray_moves_list.begin(), horizontal_ray_moves_list.end());
			moves.insert(moves.end(), vertical_ray_moves_list.begin(), vertical_ray_moves_list.end());
		}

		// Generate queen moves.
		int black_queen_keys[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // holds bit positions for existing white rooks (max of 9 possible)

		// Collect all the bit positions with occupying queens.
		int counter_q = 0;
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::blackQueenBitboard, i) == 1) {
				black_queen_keys[counter_q] = i;
				++counter_q;
			}
		}

		// Loop through keys. Break if an entry is null.
		for (int counter = 0; counter < 9; ++counter) {
			if (black_queen_keys[counter] == -1) break;

			// get the move lists for the 4 different rays
			std::vector<struct Move> swtone_ray_moves_list = generateSouthwestToNortheastRay(black_queen_keys[counter], 1, 'q');
			std::vector<struct Move> setonw_ray_moves_list = generateSoutheastToNorthwestRay(black_queen_keys[counter], 1, 'q');
			std::vector<struct Move> horizontal_ray_moves_list = generateHorizontalRay(black_queen_keys[counter], 1, 'q');
			std::vector<struct Move> vertical_ray_moves_list = generateVerticalRay(black_queen_keys[counter], 1, 'q');

			// append the moves lists to the main list
			moves.insert(moves.end(), swtone_ray_moves_list.begin(), swtone_ray_moves_list.end());
			moves.insert(moves.end(), setonw_ray_moves_list.begin(), setonw_ray_moves_list.end());
			moves.insert(moves.end(), horizontal_ray_moves_list.begin(), horizontal_ray_moves_list.end());
			moves.insert(moves.end(), vertical_ray_moves_list.begin(), vertical_ray_moves_list.end());
		}

		// Generate king moves.
		int black_king_key = -1;

		// Find the square where the white king is.
		for (int i = 0; i < 64; ++i) {
			if (getBit(Bitboard::blackKingBitboard, i) == 1) {
				black_king_key = i;
				break;
			}
		}

		// Break into 8 different moves which are listed below.
		// 1 2 3
		// 4   5
		// 6 7 8

		// move 1
		if (black_king_key > 55) goto black_king_move_4_label; // white king is on 8th rank (1, 2, and 3 not legal)
		if (black_king_key % 8 == 0) goto black_king_move_2_label; // white king is on left edge (1, 4, and 6 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key + 7) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key + 7) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key + 7) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key + 7) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key + 7) == 0) {
							// move can be made
							struct Move black_king_move_1;
							black_king_move_1.Piece = 'k';
							black_king_move_1.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_1.Move[1] = _strdup(Board64Strings1D[black_king_key + 7]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key + 7) == 1) {
								black_king_move_1.CapturedPiece = 'P'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key + 7) == 1) {
								black_king_move_1.CapturedPiece = 'N';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key + 7) == 1) {
								black_king_move_1.CapturedPiece = 'B';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key + 7) == 1) {
								black_king_move_1.CapturedPiece = 'R';
							}
							else if (getBit(Bitboard::whiteQueenBitboard, black_king_key + 7) == 1) {
								black_king_move_1.CapturedPiece = 'Q';
							}

							moves.push_back(black_king_move_1);
						}
					}
				}
			}
		}

	black_king_move_2_label:
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key + 8) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key + 8) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key + 8) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key + 8) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key + 8) == 0) {
							// move can be made
							struct Move black_king_move_2;
							black_king_move_2.Piece = 'k';
							black_king_move_2.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_2.Move[1] = _strdup(Board64Strings1D[black_king_key + 8]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key + 8) == 1) {
								black_king_move_2.CapturedPiece = 'P'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key + 8) == 1) {
								black_king_move_2.CapturedPiece = 'N';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key + 8) == 1) {
								black_king_move_2.CapturedPiece = 'B';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key + 8) == 1) {
								black_king_move_2.CapturedPiece = 'R';
							}
							else if (getBit(Bitboard::whiteQueenBitboard, black_king_key + 8) == 1) {
								black_king_move_2.CapturedPiece = 'Q';
							}

							moves.push_back(black_king_move_2);
						}
					}
				}
			}
		}

	black_king_move_3_label:
		if ((black_king_key + 1) % 8 == 0) goto black_king_move_4_label; // white king is on right edge (3, 5, and 8 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key + 9) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key + 9) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key + 9) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key + 9) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key + 9) == 0) {
							// move can be made
							struct Move black_king_move_3;
							black_king_move_3.Piece = 'k';
							black_king_move_3.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_3.Move[1] = _strdup(Board64Strings1D[black_king_key + 9]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key + 9) == 1) {
								black_king_move_3.CapturedPiece = 'p'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key + 9) == 1) {
								black_king_move_3.CapturedPiece = 'n';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key + 9) == 1) {
								black_king_move_3.CapturedPiece = 'b';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key + 9) == 1) {
								black_king_move_3.CapturedPiece = 'r';
							}
							else if (getBit(Bitboard::whiteQueenBitboard, black_king_key + 9) == 1) {
								black_king_move_3.CapturedPiece = 'q';
							}

							moves.push_back(black_king_move_3);
						}
					}
				}
			}
		}

	black_king_move_4_label:
		if (black_king_key % 8 == 0) goto black_king_move_5_label; // white king is on left edge (1, 4, and 6 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key - 1) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key - 1) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key - 1) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key - 1) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key - 1) == 0) {
							// move can be made
							struct Move black_king_move_4;
							black_king_move_4.Piece = 'k';
							black_king_move_4.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_4.Move[1] = _strdup(Board64Strings1D[black_king_key - 1]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key - 1) == 1) {
								black_king_move_4.CapturedPiece = 'P'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key - 1) == 1) {
								black_king_move_4.CapturedPiece = 'N';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key - 1) == 1) {
								black_king_move_4.CapturedPiece = 'B';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key - 1) == 1) {
								black_king_move_4.CapturedPiece = 'R';
							}
							else if (getBit(Bitboard::whiteQueenBitboard, black_king_key - 1) == 1) {
								black_king_move_4.CapturedPiece = 'Q';
							}

							moves.push_back(black_king_move_4);
						}
					}
				}
			}
		}

	black_king_move_5_label:
		if ((black_king_key + 1) % 8 == 0) goto black_king_move_6_label; // white king is on right edge (3, 5, and 8 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key + 1) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key + 1) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key + 1) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key + 1) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key + 1) == 0) {
							// move can be made
							struct Move black_king_move_5;
							black_king_move_5.Piece = 'k';
							black_king_move_5.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_5.Move[1] = _strdup(Board64Strings1D[black_king_key + 1]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key + 1) == 1) {
								black_king_move_5.CapturedPiece = 'P'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key + 1) == 1) {
								black_king_move_5.CapturedPiece = 'N';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key + 1) == 1) {
								black_king_move_5.CapturedPiece = 'B';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key + 1) == 1) {
								black_king_move_5.CapturedPiece = 'R';
							}
							else if (getBit(Bitboard::whiteQueenBitboard, black_king_key + 1) == 1) {
								black_king_move_5.CapturedPiece = 'Q';
							}

							moves.push_back(black_king_move_5);
						}
					}
				}
			}
		}

	black_king_move_6_label:
		if (black_king_key < 8) goto black_king_moves_end; // white king is on 1st rank (6, 7, and 8 not legal)
		if (black_king_key % 8 == 0) goto black_king_move_7_label; // white king is on left edge (1, 4, and 6 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key - 9) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key - 9) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key - 9) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key - 9) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key - 9) == 0) {
							// move can be made
							struct Move black_king_move_6;
							black_king_move_6.Piece = 'k';
							black_king_move_6.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_6.Move[1] = _strdup(Board64Strings1D[black_king_key - 9]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key - 9) == 1) {
								black_king_move_6.CapturedPiece = 'P'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key - 9) == 1) {
								black_king_move_6.CapturedPiece = 'N';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key - 9) == 1) {
								black_king_move_6.CapturedPiece = 'B';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key - 9) == 1) {
								black_king_move_6.CapturedPiece = 'R';
							}
							else if (getBit(Bitboard::whiteQueenBitboard, black_king_key - 9) == 1) {
								black_king_move_6.CapturedPiece = 'Q';
							}

							moves.push_back(black_king_move_6);
						}
					}
				}
			}
		}

	black_king_move_7_label:
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key - 8) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key - 8) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key - 8) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key - 8) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key - 8) == 0) {
							// move can be made
							struct Move black_king_move_7;
							black_king_move_7.Piece = 'k';
							black_king_move_7.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_7.Move[1] = _strdup(Board64Strings1D[black_king_key - 8]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key - 8) == 1) {
								black_king_move_7.CapturedPiece = 'P'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key - 8) == 1) {
								black_king_move_7.CapturedPiece = 'N';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key - 8) == 1) {
								black_king_move_7.CapturedPiece = 'B';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key - 8) == 1) {
								black_king_move_7.CapturedPiece = 'R';
							}
							else if (getBit(Bitboard::whiteQueenBitboard, black_king_key - 8) == 1) {
								black_king_move_7.CapturedPiece = 'Q';
							}

							moves.push_back(black_king_move_7);
						}
					}
				}
			}
		}

	black_king_move_8_label:
		if ((black_king_key + 1) % 8 == 0) goto black_king_moves_end; // white king is on right edge (3, 5, and 8 not legal)
		// check for same color (white) pieces
		if (getBit(Bitboard::blackPawnBitboard, black_king_key - 7) == 0) {
			if (getBit(Bitboard::blackKnightBitboard, black_king_key - 7) == 0) {
				if (getBit(Bitboard::blackBishopBitboard, black_king_key - 7) == 0) {
					if (getBit(Bitboard::blackRookBitboard, black_king_key - 7) == 0) {
						if (getBit(Bitboard::blackQueenBitboard, black_king_key - 7) == 0) {
							// move can be made
							struct Move black_king_move_8;
							black_king_move_8.Piece = 'k';
							black_king_move_8.Move[0] = _strdup(Board64Strings1D[black_king_key]);
							black_king_move_8.Move[1] = _strdup(Board64Strings1D[black_king_key - 7]);

							// Find the captured piece if any.
							if (getBit(Bitboard::whitePawnBitboard, black_king_key - 7) == 1) {
								black_king_move_8.CapturedPiece = 'P'; // captured piece is a white pawn
							}
							else if (getBit(Bitboard::whiteKnightBitboard, black_king_key - 7) == 1) {
								black_king_move_8.CapturedPiece = 'N';
							}
							else if (getBit(Bitboard::whiteBishopBitboard, black_king_key - 7) == 1) {
								black_king_move_8.CapturedPiece = 'B';
							}
							else if (getBit(Bitboard::whiteRookBitboard, black_king_key - 7) == 1) {
								black_king_move_8.CapturedPiece = 'R';
							}
							else if (getBit(Bitboard::blackQueenBitboard, black_king_key - 7) == 1) {
								black_king_move_8.CapturedPiece = 'Q';
							}

							moves.push_back(black_king_move_8);
						}
					}
				}
			}
		}

	black_king_moves_end:
		;
	}

	return moves;
}

bool isCheck(struct Game *game) {
	bool check = 0;

	game->SideToMove = !game->SideToMove; // switch sides first

	std::vector<struct Move> is_check_moves = generateMoves(game); // get all moves

	// Loop through all moves and look for a king capture.
	for (int i = 0; i < is_check_moves.size(); ++i) {
		if ((is_check_moves.at(i).CapturedPiece == 'K') || (is_check_moves.at(i).CapturedPiece == 'k')) {
			game->SideToMove = !game->SideToMove; // switch sides back
			check = 1; // in check
		}
	}

	game->SideToMove = !game->SideToMove; // switch sides back

	return check;
}

bool kingCastleInCheckPred(struct Game& game, const struct Move& move) {
	//struct Game game_internal = game;
	return (isCheck(&game) && move.IsCastle);
}

bool kingInCheckAfterMovePred(struct Game& game, const struct Move& move) {
	struct Game game_internal = game;

	bool val = 0;

	// Check for moves that leave king in check afterwards.
	std::string move_string_init;
	move_string_init.append(move.Move[0]);
	move_string_init.append(move.Move[1]);
	char* move_string = _strdup(move_string_init.c_str());
	makeMove(move_string, &game_internal);

	game_internal.SideToMove = !game_internal.SideToMove; // need the same side's point of view since makeMove() automatically switches sides

	// move is illegal if the king is in check after the move has been made
	if (isCheck(&game_internal)) val = 1;

	game_internal.SideToMove = !game_internal.SideToMove; // change back

	unmakeMove(move, &game_internal);

	return val;
}

std::vector<struct Move> legalizeMoves(struct Game *game, std::vector<struct Move> moves_list) {
	std::vector<struct Move> moves_list_internal = moves_list; // local copy to make changes

	// lambdas for dealing with predicates with two arguments
	auto pred1 = [&](struct Move move) -> bool { return kingCastleInCheckPred(*game, move); };
	auto pred2 = [&](struct Move move) -> bool { return kingInCheckAfterMovePred(*game, move); };

	auto pred1_iterator = std::remove_if(moves_list_internal.begin(), moves_list_internal.end(), pred1);
	moves_list_internal.erase(pred1_iterator, moves_list_internal.end()); // king cannot castle while in check

	auto pred2_iterator = std::remove_if(moves_list_internal.begin(), moves_list_internal.end(), pred2);
	moves_list_internal.erase(pred2_iterator, moves_list_internal.end()); // player cannot make a move that leaves king in check

	return moves_list_internal;
}

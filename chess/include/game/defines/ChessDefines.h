#ifndef INCLUDE_DEFINES_CHESSDEFINES_H_
#define INCLUDE_DEFINES_CHESSDEFINES_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declarations



namespace Defines{
	enum PlayerId {
		WHITE_PLAYER_ID ,
		BLACK_PLAYER_ID,
		PLAYERS_COUNT
	};

	enum Direction {
	  UP_LEFT,
	  UP,
	  UP_RIGHT,
	  RIGHT,
	  DOWN_RIGHT,
	  DOWN,
	  DOWN_LEFT,
	  LEFT,
	  //KnightDirs START:
	  UP_LEFT_TURN,
	  UP_RIGHT_TURN,
	  RIGHT_LEFT_TURN,
	  RIGHT_RIGHT_TURN,
	  DOWN_LEFT_TURN,
	  DOWN_RIGHT_TURN,
	  LEFT_LEFT_TURN,
	  LEFT_RIGHT_TURN,
	  //KnightDirs END

	  DIRECTION_COUNT
	};
	enum PawnDefines {
	  WHITE_PLAYER_START_PAWN_ROW = 6,
	  WHITE_PLAYER_END_PAWN_ROW = 0,

	  BLACK_PLAYER_START_PAWN_ROW = 1,
	  BLACK_PLAYER_END_PAWN_ROW = 7,

	  PAWN_COUNT = 8
	};
}// namespace Defines

enum class PieceType : uint8_t {
  KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN,UNKNOWN
};

enum class TileType : uint8_t {
  MOVE, GUARD, TAKE
};


#endif /* INCLUDE_DEFINES_CHESSDEFINES_H_ */

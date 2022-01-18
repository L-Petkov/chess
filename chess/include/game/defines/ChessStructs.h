#ifndef INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_
#define INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_
//C system includes

//C++ system includes
#include <vector>

//Third-party includes

//Own includes
#include "game/defines/ChessDefines.h"
#include "game/utils/BoardPos.h"


//Forward Declarations


struct TileData {
	TileData() = default;

	TileData(const BoardPos &inputBoardPos, TileType inputTileType)
	  : boardPos(inputBoardPos), tileType(inputTileType) {
	}
	BoardPos boardPos;
	TileType tileType = TileType::MOVE;
};

using MoveDirection = std::vector<BoardPos>;




#endif /* INCLUDE_GAME_DEFINES_CHESSSTRUCTS_H_ */

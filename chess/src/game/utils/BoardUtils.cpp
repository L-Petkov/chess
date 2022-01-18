//Corresponding header
#include "game/utils/BoardUtils.h"

//C system includes

//C++ system includes
#include <iostream>
//Third-party includes


//Own includes
#include "utils/drawing/Rectangle.h"


//TODO change with the comments beforeSUBMITING
namespace{
constexpr auto BOARD_SIZE = 8;

constexpr auto FIRST_TILE_X_POS = 29;//58;//TODO change
constexpr auto FIRST_TILE_Y_POS = 30;//60;//TODO change

constexpr auto TILE_SIZE = 49;//98;//TODO change
}


BoardPos BoardUtils::getBoardPos(const Point &absPos){
	return {(absPos.y - FIRST_TILE_Y_POS) / TILE_SIZE,
			(absPos.x - FIRST_TILE_X_POS) / TILE_SIZE};
}

Point BoardUtils::getAbsPos(const BoardPos& boardPos){
	return {(boardPos.col * TILE_SIZE) + FIRST_TILE_X_POS ,
		 	 (boardPos.row * TILE_SIZE) + FIRST_TILE_Y_POS };
}

bool BoardUtils::isInsideBoard(const BoardPos& boardPos){
	const Rectangle bound{ 0, 0, BOARD_SIZE, BOARD_SIZE};
	const Point pos {boardPos.col, boardPos.row};

	return bound.isPointInside(pos);

}
bool BoardUtils::isInsideBoard(const Point& absPos){
	const Rectangle bound{ FIRST_TILE_X_POS, FIRST_TILE_Y_POS,
						   BOARD_SIZE * TILE_SIZE, BOARD_SIZE * TILE_SIZE };
	return bound.isPointInside(absPos);
}


int32_t BoardUtils::getOpponentId(int32_t activePlayerId){
	if(Defines::WHITE_PLAYER_ID == activePlayerId){
		return Defines::BLACK_PLAYER_ID;
	}
	return Defines::WHITE_PLAYER_ID;
}

BoardPos BoardUtils::getAdjacentPos(Defines::Direction dir, const BoardPos &currPos){
	BoardPos  pos = currPos;

	switch (dir){
	//ALL pieces possible Dirs Except for the Knight
	case Defines::UP_LEFT:
		--pos.row;
		--pos.col;
		break;
	case Defines::UP:
		--pos.row;
		break;
	case Defines::UP_RIGHT:
		--pos.row;
		++pos.col;
		break;
	case Defines::RIGHT:
		++pos.col;
		break;
	case Defines::DOWN_RIGHT:
		++pos.row;
		++pos.col;
		break;
	case Defines::DOWN:
		++pos.row;
		break;
	case Defines::DOWN_LEFT:
		++pos.row;
		--pos.col;
		break;
	case Defines::LEFT:
		--pos.col;
		break;
		//END of all pieces possible Dirs Except for the Knight END

		//ONLY KnightDirs START:
									//Releative to Board :
	case Defines::UP_LEFT_TURN:
		pos.row -= 2;				//move up 2 tiles then
		--pos.col;					// move one tile to the left
		break;
	case Defines::UP_RIGHT_TURN:
		pos.row -= 2;				//move up 2 tiles then
		++pos.col;					// move one tile to the right
		break;
	case Defines::RIGHT_LEFT_TURN:
		pos.col += 2;;				//move right 2 tiles then
		--pos.row;					// move one tile to the up
		break;
	case Defines::RIGHT_RIGHT_TURN:
		pos.col += 2;				//move right 2 tiles then
		++pos.row;					// move one tile to the down
		break;

	case Defines::DOWN_LEFT_TURN:
		pos.row += 2;				//move down 2 tiles then
		++pos.col;					// move one tile to the right
		break;
	case Defines::DOWN_RIGHT_TURN:
		pos.row += 2;				//move down 2 tiles then
		--pos.col;					// move one tile to the left
		break;
	case Defines::LEFT_LEFT_TURN:
		pos.col -= 2;				//move left 2 tiles then
		++pos.row;					// move one tile to the down
		break;
	case Defines::LEFT_RIGHT_TURN:
		pos.col -= 2;				//move left 2 tiles then
		--pos.row;					// move one tile to the up
		break;
    //ONLY KnightsDirs END

	default:
		std::cerr << "Received invalid dir" << std::endl;
		break;
	}
	return pos;
}

bool BoardUtils::doCollideWithPiece(const BoardPos &selectedPos,
		const ChessPiece::PlayerPieces &pieces, int32_t& outCollisionRelativeId){
	const size_t size = pieces.size();
	for(size_t i = 0 ;i < size ; ++i){
		if(selectedPos == pieces[i]->getBoardPos()){
			outCollisionRelativeId = static_cast<int32_t>(i);
			return true;
		}
	}
	return false;
}

TileType BoardUtils::getTileType(const BoardPos &boardPos,
		const ChessPiece::PlayerPieces &playerPieces,
		const ChessPiece::PlayerPieces &enemyPieces){

	int32_t collisionIdx = -1;
	if(doCollideWithPiece(boardPos, playerPieces, collisionIdx)){
		return TileType::GUARD;
	}
	else if(doCollideWithPiece(boardPos, enemyPieces, collisionIdx)){
				return TileType::TAKE;
	}
	return TileType::MOVE;
}




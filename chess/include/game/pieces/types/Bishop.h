#ifndef INCLUDE_GAME_PIECES_TYPES_BISHOP_H_
#define INCLUDE_GAME_PIECES_TYPES_BISHOP_H_

//C system includes

//C++ system includes
#include <cstdint>
#include <unordered_map>

//Third-party includes

//Own includes
#include "game/pieces/types/ChessPiece.h"

//Forward Declarations


class Bishop :public ChessPiece{
public:
	std::vector<TileData> getMoveTiles(
	    const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const final;

private:
	std::vector<MoveDirection> getBoardMoves() const ;

};

#endif /* INCLUDE_GAME_PIECES_TYPES_BISHOP_H_ */

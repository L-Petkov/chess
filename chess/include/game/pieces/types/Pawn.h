#ifndef INCLUDE_GAME_PIECES_TYPES_PAWN_H_
#define INCLUDE_GAME_PIECES_TYPES_PAWN_H_

//C system includes

//C++ system includes
#include <cstdint>
#include <unordered_map>

//Third-party includes

//Own includes
#include "game/pieces/types/ChessPiece.h"

//Forward Declarations
class GameProxy;


class Pawn :public ChessPiece{
public:
	Pawn(GameProxy* gameProxy);
	Pawn() = default;
	void setBoardPos(const BoardPos &boardPos) final;
	std::vector<TileData> getMoveTiles(
	    const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const final;

	void setLastPosOfOpponentPiece(BoardPos& lastPosOfOpponent);
	BoardPos getLastPosOfOpponentPiece()const;

private:

	std::vector<TileData> getWhiteMoveTiles(
		    const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const;
	std::vector<TileData> getBlackMoveTiles(
		    const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const;

	std::unordered_map<Defines::Direction,MoveDirection> getWhiteBoardMoves() const ;
	std::unordered_map<Defines::Direction,MoveDirection> getBlackBoardMoves() const ;

	GameProxy* _gameProxy = nullptr;
	BoardPos _lastPosOfOpponent;//workInProgressForElPasant
	int32_t lastRow = Defines::WHITE_PLAYER_START_PAWN_ROW;
};

#endif /* INCLUDE_GAME_PIECES_TYPES_PAWN_H_ */

#ifndef INCLUDE_GAME_PIECES_PIECEHANDLERPOPULATOR_H_
#define INCLUDE_GAME_PIECES_PIECEHANDLERPOPULATOR_H_

//C system includes

//C++ system includes
#include <cstdint>
//#include <array>
//#include <vector>
//#include <memory>

//Third-party includes

//Own includes
#include "game/pieces/types/ChessPiece.h"

//Forward Declaration
class GameProxy;



class PieceHandlerPopulator {
public:
	PieceHandlerPopulator() = delete;
	~PieceHandlerPopulator() = default;

	static int32_t populatePieceHandler(
			GameProxy* gameProxy,
			int32_t whitePiecesRsrcId, int32_t blackPiecesRsrcId,
			std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT>& _pieces);

	static std::unique_ptr<ChessPiece> createPiece(PieceType pieceType, GameProxy* gameProxy);

};

#endif /* INCLUDE_GAME_PIECES_PIECEHANDLERPOPULATOR_H_ */

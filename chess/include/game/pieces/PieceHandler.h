#ifndef INCLUDE_GAME_PIECES_PIECEHANDLER_H_
#define INCLUDE_GAME_PIECES_PIECEHANDLER_H_

//C system includes

//C++ system includes
#include <cstdint>
#include <array>
#include <vector>

//Third-party includes

//Own includes
#include "game/pieces/PieceHandlerPopulator.h"

//Forward Declarations
class GameBoardProxy;
class GameProxy;
class FBO;


class PieceHandler {
public:
	int32_t init(GameBoardProxy* gameBoardProxy, GameProxy* gameProxy,
				 int32_t whitePiecesRsrcId, int32_t blackPiecesRsrcId);
	void drawOnFbo(FBO& fbo) const;
	void draw() const;
	void handleEvent(const InputEvent& e);
	void setCurrPlayerId(int32_t curPLayerId);
	void setWidgetFlipType(WidgetFlip flipType);
	void promotePiece(PieceType pieceType);
	void freePieces();

	void setLastPosOfOpponentPiece(BoardPos& lastPosOfOpponent);
	BoardPos getLastPosOfOpponentPiece()const;

private:
	void handlePieceGrabedEvent(const InputEvent& e);
	void handlePieceUngrabedEvent(const InputEvent& e);
	void doMovePiece(const BoardPos& boardPos);

	GameBoardProxy* _gameBoardProxy = nullptr;
	GameProxy* _gameProxy = nullptr;
	std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> _pieces;
	int32_t _selectedPieceId = 0;
	int32_t _currPlayerId = 0;
	bool _isPieceGrabbed = false;
	BoardPos _lastPosOfOpponent;//workInProgressForElPasant
};

#endif /* INCLUDE_GAME_PIECES_PIECEHANDLER_H_ */

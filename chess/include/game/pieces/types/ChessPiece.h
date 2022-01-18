#ifndef INCLUDE_GAME_PIECES_TYPES_CHESSPIECE_H_
#define INCLUDE_GAME_PIECES_TYPES_CHESSPIECE_H_

//C system includes

//C++ system includes
#include <cstdint>
#include <memory>
#include <array>

//Third-party includes

//Own includes
#include "manager_utils/drawing/Image.h"
#include "game/utils/BoardPos.h"
#include "game/defines/ChessStructs.h"

//Forward Declarations
class InputEvent;
class FBO;



struct ChessPieceCfg{
	BoardPos boardPos{};
	int32_t playerId{};
	int32_t rsrcId = INVALID_RSRC_ID;
	PieceType pieceType = PieceType::UNKNOWN;


};

class ChessPiece {
public:

	using PlayerPieces = std::vector<std::unique_ptr<ChessPiece>>;

	virtual ~ChessPiece() = default;
	virtual int32_t init(const ChessPieceCfg& cfg);
	virtual void drawOnFbo(FBO& fbo) const;
	virtual void draw() const;
	virtual void setBoardPos(const BoardPos &boardPos);// setter virtual
	virtual std::vector<TileData> getMoveTiles(
			const std::array<PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const = 0;

	bool containsEvent(const InputEvent &e) const;

	// getters
	BoardPos getBoardPos()const;
	int32_t getPlayerId()const;
	int32_t getRsrcId()const;
	PieceType getPieceType()const;
	void setWidgetFlipType(WidgetFlip flipType);


protected:
	Image _pieceImg {};
	BoardPos _boardPos {};
	int32_t _playerId {};
	PieceType _pieceType = PieceType::UNKNOWN;
};
#endif /* INCLUDE_GAME_PIECES_TYPES_CHESSPIECE_H_ */

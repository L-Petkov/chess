#ifndef INCLUDE_GAME_BOARD_GAMEBOARD_H_
#define INCLUDE_GAME_BOARD_GAMEBOARD_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "game/proxies/GameBoardProxy.h"
#include "game/board/MoveSelector.h"
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"

//Forward Declarations
class FBO;

class GameBoard : public GameBoardProxy, TimerClient{
public:
	~GameBoard();
	int32_t init(int32_t boardRsrcId, int32_t targetRsrcId,int32_t moveTilesRsrcId, int32_t blinkTimerId);
	void drawGameBoardOnFbo(FBO& fbo) const;
	void drawGameBoardOnly() const;
	void draw() const;

	void setWidgetFlipType(WidgetFlip flipType);
	void setOnlyBoardFlipType(WidgetFlip flipType);

private:
	//fromGameBoardProxy
	void onPieceGrabbed(const BoardPos &boardPos, const std::vector<TileData> &moveTiles) final;
	void onPieceUngrabbed() final;
	bool isMoveAllowed(const BoardPos &pos) const final;
	//end GameBoardProxy
	//from timerClient
	void onTimeout(int32_t timerId)final;//from timerClient
	//end TimerClient
	Image _boardImg;
	Image _targetImg;

	int32_t _blinkTimerId;

	std::vector<TileData> _currMoveTiles;
	MoveSelector _moveSelector;
	ImagePosInverter _imgPosInverter;
};

#endif /* INCLUDE_GAME_BOARD_GAMEBOARD_H_ */

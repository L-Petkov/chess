#ifndef GAME_GAME_H_
#define GAME_GAME_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/drawing/Fbo.h"
#include "manager_utils/drawing/Text.h"
#include "manager_utils/time/TimerClient.h"
#include "game/config/GameCfg.h"
#include "game/board/GameBoard.h"
#include "game/board/GameBoardAnimator.h"
#include "game/buttons/InGameExitBtn.h"
#include "game/pieces/PieceHandler.h"
#include "game/logic/GameLogic.h"
#include "game/logic/InputInverter.h"
#include "game/proxies/GameProxy.h"
#include "game/panels/PiecePromotionPanel.h"



//Forward Declarations
class InputEvent;
class MainMenuCfg;

class Game : public GameProxy, public TimerClient{
public:
	~Game();
	int32_t init(const GameCfg& cfg, MainMenuProxy* cfgMainMenu);
	void deinit();
	void draw() const;
	void handleEvent(InputEvent& e);
	void reset(GameCfg* gameCfg, GameProxy* gameProxy)final;
	GameBoardProxy* getGameBoardPtr();
	int32_t getPlayerTurnTimerCapRsrcId () const;
	void setLastPosOfOpponentPiece(BoardPos& lastPosOfOpponent);
	BoardPos getLastPosOfOpponentPiece()const;
private:

	void onGameTurnFinish() final;
	void onPawnPromotion()final;
	void promotePiece(PieceType pieceType)final;
	void onBoardAnimFinished()final;
	void setWidgetFlipType(WidgetFlip flipType)final;
	bool isPiecePromPanelActive() const final;
	//void handlePiecePromotion(const InputEvent& e)  final;
	void regenerateGameFbo();
	void onTimeout(int32_t timerId)final;

	Image _bgr;
	GameBoard _gameBoard;
	PieceHandler _pieceHandler;
	GameLogic _gameLogic;
	PiecePromotionPanel _piecePromotionPanel;
	GameBoardAnimator _gameBoardAnimator;
	InputInverter _inputInverter;
	FBO	_gameFbo;
	InGameExitBtn _exitBtn;
	int32_t _playerTurnTimerCapRsrcsId ;
	int32_t _timeLeftPerTurn = 60;
	Text _timeLeft;
	BoardPos _lastPosOfOpponent;//workInProgressForElPasant

};

#endif /* GAME_GAME_H_ */

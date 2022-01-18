#ifndef INCLUDE_GAME_PROXIES_GAMEPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMEPROXY_H_

//C system includes

//C++ system includes

//Third-party includes

//Own includes
#include "game/defines/ChessDefines.h"
//Forward Declarations
//class InputEvent;
class GameCfg;
class MainMenuProxy;
class GameProxy;

class GameProxy{
public:

	virtual ~GameProxy() = default;
	virtual void onGameTurnFinish() = 0;
	virtual void onPawnPromotion() = 0;
	virtual void promotePiece(PieceType pieceType) = 0;
	virtual void onBoardAnimFinished() = 0;
	virtual void setWidgetFlipType(WidgetFlip flipType) = 0;
	virtual bool isPiecePromPanelActive() const = 0;
	//virtual void handlePiecePromotion(const InputEvent& e)  = 0;
	virtual void reset(GameCfg* gameCfg, GameProxy* _gameProxy) = 0;
	int32_t getPlayerTurnTimerCapRsrcId () const;
};




#endif /* INCLUDE_GAME_PROXIES_GAMEPROXY_H_ */

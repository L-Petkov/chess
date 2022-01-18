#ifndef INCLUDE_GAME_BOARD_GAMEBOARDANIMATOR_H_
#define INCLUDE_GAME_BOARD_GAMEBOARDANIMATOR_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/drawing/Image.h"
#include "manager_utils/time/TimerClient.h"

//Forward Declarations
class GameProxy;
class FBO;

class GameBoardAnimator : public TimerClient{
public:
	~GameBoardAnimator();
	int32_t init(GameProxy *gameProxy, FBO *_gameFbo, int32_t gameFboRotTimerId);

	void startAnim(int32_t playerId);

	bool isActive();
	void resetFlipType();
	int32_t getGameFboRotTimerId();
private:
	void onTimeout(int32_t timerId) final;

	void procesRotAnim();

	GameProxy *_gameProxy = nullptr;
	FBO *_gameFbo = nullptr;
	int32_t _currRotation { 0 };
	int32_t _targetRotation { 0 };
	int32_t _gameFboRotTimerId = -1;
	WidgetFlip _targetFlipType = WidgetFlip::NONE;
};

#endif /* INCLUDE_GAME_BOARD_GAMEBOARDANIMATOR_H_ */

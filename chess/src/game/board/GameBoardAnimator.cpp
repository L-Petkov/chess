//Corresponding header
#include "game/board/GameBoardAnimator.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/proxies/GameProxy.h"
#include "manager_utils/drawing/Fbo.h"

namespace{
constexpr auto ROT_ANIM_STEP_DEGREES = 30;
}

GameBoardAnimator::~GameBoardAnimator(){
	if(isActiveTimerId(_gameFboRotTimerId)){
		stopTimer(_gameFboRotTimerId);
	}
}

int32_t GameBoardAnimator::init(GameProxy* gameProxy, FBO* gameFbo, int32_t gameFboRotTimerId){
	if(nullptr == gameProxy){
		std::cerr << "Error, nullptr provided for gameProxy in GameBoardAnimator::init()" << std::endl;
		return EXIT_FAILURE;
	}
	_gameProxy = gameProxy;

	if(nullptr == gameFbo){
		std::cerr << "Error, nullptr provided for gameFbo in GameBoardAnimator::init()" << std::endl;
		return EXIT_FAILURE;
	}
	_gameFbo = gameFbo;

	const Point rotCenter((_gameFbo->getWidth()/2), (_gameFbo->getHeight()/2));
	_gameFbo->setRotationCenter(rotCenter);

	_gameFboRotTimerId = gameFboRotTimerId;

	return EXIT_SUCCESS;
}

void GameBoardAnimator::startAnim(int32_t playerId){
	if(Defines::WHITE_PLAYER_ID == playerId){
		_targetFlipType = WidgetFlip::HORIZONTAL_AND_VERTICAL;
		_targetRotation = FULL_ROTATION / 2;
	}
	else if(Defines::BLACK_PLAYER_ID == playerId){
		_targetFlipType = WidgetFlip::NONE;
		_targetRotation = FULL_ROTATION;
	}

	startTimer(50, _gameFboRotTimerId, TimerType::PULSE);

	_gameProxy->setWidgetFlipType(_targetFlipType);
}

bool GameBoardAnimator::isActive(){
	return isActiveTimerId(_gameFboRotTimerId);
}

void GameBoardAnimator::resetFlipType(){
	_targetFlipType = WidgetFlip::NONE;
}

void GameBoardAnimator::onTimeout(int32_t timerId){
	if(timerId == _gameFboRotTimerId){
		procesRotAnim();
	}
	else {
		std::cerr << "Received unsupported timerId" << timerId << std::endl;
	}
}
int32_t GameBoardAnimator::getGameFboRotTimerId(){
	return _gameFboRotTimerId;
}

void GameBoardAnimator::procesRotAnim(){
	_currRotation += ROT_ANIM_STEP_DEGREES;
	_gameFbo->setRotation(_currRotation);
	if(_targetRotation == _currRotation){
		if(FULL_ROTATION == _targetRotation){
			_currRotation = 0;
		}
		stopTimer(_gameFboRotTimerId);
		_gameProxy->onBoardAnimFinished();
	}
}





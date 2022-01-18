//Corresponding header
#include "mainMenu/MainMenu.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "sdl_utils/InputEvent.h"
#include "game/proxies/GameProxy.h"
#include "manager_utils/time/TimerClient.h"

//Forward Declarations



namespace{
	int32_t X = 135;
	int32_t Y = 100;
	constexpr auto FOR_EXIT_BTN_OFFSSET = 44;//offsettt for exitbtn  will change
}
int32_t MainMenu::init(const MainMenuCfg &cfg, GameProxy& gameProxy, const GameCfg& gameCfg) {

	_bgrImg.create(cfg.bgrMainMenuRsrcId);

	Point startBtnPos(X+FOR_EXIT_BTN_OFFSSET,Y);
	Point exitBtnPos(X+FOR_EXIT_BTN_OFFSSET,Y+100);

	if (EXIT_SUCCESS != _startBtns.init(this, cfg.startGameBtnRsrcId)) {
		std::cerr << "_startBtns.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != _stopBtns.init(this, cfg.stopGameBtnRsrcId)) {
		std::cerr << "_stopBtns.init() failed" << std::endl;
		return EXIT_FAILURE;
	}
	_startBtns.create(cfg.startGameBtnRsrcId,startBtnPos);
	_stopBtns.create(cfg.stopGameBtnRsrcId, exitBtnPos);

	_gameProxy = &gameProxy;
	_cfg = gameCfg;

	return EXIT_SUCCESS;
}
void MainMenu::deinit() {

}

void MainMenu::draw() const{
	_bgrImg.draw();
	_startBtns.draw();
	_stopBtns.draw();
}
void MainMenu::handleEvent(InputEvent &e) {
	if(_startBtns.isInputUnlocked() && _startBtns.containsEvent(e)){
		_startBtns.handleEvent(e);
	}
	else if (_stopBtns.isInputUnlocked() && _stopBtns.containsEvent(e)){
		_stopBtns.handleEvent(e);
	}

}
bool MainMenu::isActive()const{
	return _isActive;
}

void MainMenu::activate(){
	_isActive = true;
}

void MainMenu::deactivate(){
	_isActive = false;
}

void MainMenu::onButtonPressed(int32_t buttonId){
	switch(buttonId){
		case START_GAME_BTN_IDX:
			_isActive = false;
			if(isInsideGameBtnExitClicked){
				isInsideGameBtnExitClicked = false;
				// work in progress
				//_gameProxy->reset(&_cfg, _gameProxy); //deinit pieceHandler and init a ew resset
			}
			break;
		case EXIT_GAME_BTN_IDX:
			_isActive = true;
			_exitRequest = true;
			break;
		case IN_GAME_EXIT_BTN:
			_isActive = true;
			isInsideGameBtnExitClicked = true;
			break;
		default:
			std::cerr << "In main menu received unsupported buttonId:" << buttonId << std::endl;
			break;
		}
}
bool MainMenu::checkForExitRequest() const{
	return _exitRequest;
}



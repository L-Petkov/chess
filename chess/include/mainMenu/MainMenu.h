#ifndef INCLUDE_MAINMENU_MAINMENU_H_
#define INCLUDE_MAINMENU_MAINMENU_H_
//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/drawing/Image.h"
#include "mainMenu/config/MainMenuCfg.h"
#include "mainMenu/buttons/StartGameBtn.h"
#include "mainMenu/proxies/MainMenuProxy.h"
#include "game/config/GameCfg.h"

//Forward Declarations
class InputEvent;
class GameProxy;


class MainMenu :public MainMenuProxy {
public:
	int32_t init(const MainMenuCfg& cfg, GameProxy& gameProxy, const GameCfg& gameCfg);
	void deinit();
	void draw() const;
	void handleEvent(InputEvent& e);
	bool isActive()const;
	void activate();
	void deactivate();
	bool checkForExitRequest() const;
private:
	void onButtonPressed(int32_t buttonId) final;
	enum Internals{
			START_GAME_BTN_IDX,
			EXIT_GAME_BTN_IDX,
			IN_GAME_EXIT_BTN,
			BTNS_COUNT
		};
	Image _bgrImg;
	StartGameBtn _startBtns;
	StartGameBtn _stopBtns;
	bool _isActive = true;
	bool _exitRequest = false;
	GameProxy* _gameProxy = nullptr;
	GameCfg _cfg;
	MainMenuProxy* _cfgMainMenu;
	bool isInsideGameBtnExitClicked = false;
};



#endif /* INCLUDE_MAINMENU_MAINMENU_H_ */

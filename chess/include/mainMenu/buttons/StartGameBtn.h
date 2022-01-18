#ifndef INCLUDE_MAINMENU_BUTTONS_STARTGAMEBTN_H_
#define INCLUDE_MAINMENU_BUTTONS_STARTGAMEBTN_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/input/ButtonBase.h"

//Forward Declarations

class MainMenuProxy;


class StartGameBtn : public ButtonBase{
public:
	int32_t init(MainMenuProxy* _mainMenuProxy, int32_t _buttonId);

	void handleEvent(const InputEvent &e) final;

private:

	MainMenuProxy * _mainMenuProxy = nullptr;
	int32_t _buttonId { 0 };

};

#endif /* INCLUDE_MAINMENU_BUTTONS_STARTGAMEBTN_H_ */

#ifndef INCLUDE_GAME_BUTTONS_INGAMEEXITBTN_H_
#define INCLUDE_GAME_BUTTONS_INGAMEEXITBTN_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/input/ButtonBase.h"

//Forward Declarations
class MainMenuProxy;



class InGameExitBtn : public ButtonBase{
public:
	int32_t init(MainMenuProxy* _mainMenuProxy, int32_t _buttonId);

	void handleEvent(const InputEvent &e) final;

private:

	MainMenuProxy * _mainMenuProxy = nullptr;

	int32_t _buttonId { 0 };
};

#endif /* INCLUDE_GAME_BUTTONS_INGAMEEXITBTN_H_ */

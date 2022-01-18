//Corresponding header
#include "mainMenu/buttons/ExitGameBtn.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "mainMenu/proxies/MainMenuProxy.h"
#include "sdl_utils/InputEvent.h"



int32_t ExitGameBtn::init(MainMenuProxy* mainMenuProxy, int32_t buttonId){
	if(nullptr == mainMenuProxy){
		std::cerr << "nullptr provided for mainMenuProxy. ButtonId: "
				<< buttonId << std::endl;
		return EXIT_FAILURE;
	}
	_mainMenuProxy = mainMenuProxy;
	_buttonId = buttonId;

	return EXIT_SUCCESS;
}

void ExitGameBtn::handleEvent(const InputEvent &e){
	if(e.type == TouchEvent::TOUCH_PRESS){
		//setFrame(CLICKED);						//no frames yet
	}
	else if (e.type == TouchEvent::TOUCH_RELEASE){
		//setFrame(UNCLICKED);						//no frames yet
		_mainMenuProxy->onButtonPressed(_buttonId);

	}
}

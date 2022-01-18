
//Corresponding header
#include "game/logic/InputInverter.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "sdl_utils/InputEvent.h"

int32_t InputInverter::init(int32_t boardWidth, int32_t boardHeight){
	 _boardWidth = boardWidth;
	 _boardHeight = boardHeight;

	return EXIT_SUCCESS;
}

void InputInverter::setBoardFlipType(WidgetFlip flipType){
	_flipType  = flipType;
}

void InputInverter::invertEvent(InputEvent & e){
	switch(_flipType){

	case WidgetFlip::NONE:
		break;

	case WidgetFlip::HORIZONTAL:
		e.pos.y = _boardHeight - e.pos.y;
		break;

	case WidgetFlip::VERTICAL:
		e.pos.x = _boardWidth - e.pos.x;
		break;

	case WidgetFlip::HORIZONTAL_AND_VERTICAL:
		e.pos.y = _boardHeight - e.pos.y;
		e.pos.x = _boardWidth - e.pos.x;
		break;
	default :
		std::cerr <<
		"Error, in InputInverter::invertEvent() received unknown InputEvent"
		<< std::endl;
		break;

	}
}







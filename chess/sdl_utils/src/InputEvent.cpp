//Corresponding header
#include "sdl_utils/InputEvent.h"

//C system includes

//C++ system includes
#include <iostream>
#include <cstring>
//Third-party includes
#include <SDL_events.h>

//Own includes


int32_t InputEvent::init(){
	_sdlEvent = new SDL_Event;
	memset(_sdlEvent, 0, sizeof(SDL_Event));
	if(!_sdlEvent){
		std::cerr << "new SDL_Event in InputEvent::init() failed." << std::endl;
	}
	return EXIT_SUCCESS;
}
void InputEvent::deinit(){
	if(_sdlEvent){
		delete _sdlEvent;
		_sdlEvent = nullptr;
	}
}
bool InputEvent::pollEvent(){
	if(0 == SDL_PollEvent(_sdlEvent)){

		return false;
	}
	SDL_GetMouseState(&pos.x, &pos.y);
	setEventTypeInternal();

	return true;
}

void InputEvent::setEventTypeInternal() {
	switch (_sdlEvent->type) {

		case EventType::KEYBOARD_PRESS:
			key = _sdlEvent->key.keysym.sym;
			mouseButton = Mouse::UNKNOWN;
			type = TouchEvent::KEYBOARD_PRESS;
			break;

		case EventType::KEYBOARD_RELEASE:

			key = _sdlEvent->key.keysym.sym;
			mouseButton = Mouse::UNKNOWN;
			type = TouchEvent::KEYBOARD_RELEASE;
			break;


		case EventType::MOUSE_PRESS:
			key = Keyboard::KEY_UNKNOWN;
			mouseButton = _sdlEvent->button.button;
			type = TouchEvent::TOUCH_PRESS;
			break;
		case EventType::FINGER_PRESS:
			key = Keyboard::KEY_UNKNOWN;
			mouseButton = Mouse::UNKNOWN;
			type = TouchEvent::TOUCH_PRESS;
			break;

		case EventType::MOUSE_RELEASE:
			key = Keyboard::KEY_UNKNOWN;
			mouseButton = _sdlEvent->button.button;
			type = TouchEvent::TOUCH_RELEASE;
			break;
		case EventType::FINGER_RELEASE:
			key = Keyboard::KEY_UNKNOWN;
			mouseButton = Mouse::UNKNOWN;
			type = TouchEvent::TOUCH_RELEASE;
			break;

			//X is pressed on the window (or CTRL-C signal is sent)
		case EventType::QUIT:
			key = Keyboard::KEY_UNKNOWN;
			mouseButton = Mouse::UNKNOWN;
			type = TouchEvent::UNKNOWN;
			break;

		default:
			key = Keyboard::KEY_UNKNOWN;
			mouseButton = Mouse::UNKNOWN;
			type = TouchEvent::UNKNOWN;
			break;
	}
}
bool InputEvent::checkForExitRequest() const{
	return (_sdlEvent->type	== EventType::QUIT) || (type ==TouchEvent::KEYBOARD_PRESS && Keyboard::KEY_ESCAPE == key);
}

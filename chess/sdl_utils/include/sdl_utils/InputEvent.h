#ifndef SDL_UTILS_INPUTEVENT_H_
#define SDL_UTILS_INPUTEVENT_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "utils/input/EventDefines.h"
#include "utils/drawing/Point.h"

//Forward Declarations
//Do not expose SDL_Event internals to the system
union SDL_Event;

class InputEvent {
public:
	int32_t init();
	void deinit();
	/*returns if OS event is pulled*/
	bool pollEvent();
	bool checkForExitRequest() const;

	/* Holds event position on the screen */
	Point pos = Point::UNDEFINED;

	/* See EventDefines.h for more information */
	int32_t key = Keyboard::KEY_UNKNOWN;
	uint8_t mouseButton = Mouse::UNKNOWN;
	TouchEvent type = TouchEvent::UNKNOWN;


private:

	void setEventTypeInternal();
	/** Holds the OS communication event system */
	SDL_Event *_sdlEvent = nullptr;
};
#endif /* SDL_UTILS_INPUTEVENT_H_ */

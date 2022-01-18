//Corresponding header
#include "manager_utils/debug/DebugConsole.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "utils/drawing/Color.h"
#include "sdl_utils/InputEvent.h"

int32_t DebugConsole::init(int64_t maxFrames, uint32_t fontId){
	_maxFrames = maxFrames;

	Point debugTextPos = Point(0,80);
	_debugTexts[FPS_TEXT_IDX].create("0", fontId, Colors::GREEN,debugTextPos);

	debugTextPos.y += 40;
	_debugTexts[ACTIVE_TIMER_IDX].create("0", fontId, Colors::GREEN,debugTextPos);

	debugTextPos.y += 40;
	_debugTexts[ACTIVE_WIDGETS_IDX].create("0", fontId, Colors::GREEN,debugTextPos);



	return EXIT_SUCCESS;
}

void DebugConsole::handleEvent(const InputEvent &e){
	if(e.type != TouchEvent::KEYBOARD_PRESS){
		return;
	}
	if(e.key == Keyboard::KEY_TILDA){
		_isActive = !_isActive;
	}
}

void DebugConsole::update(int64_t elapsedMicroseconds, size_t activeTimers){
	std::string textContents;

	//debuggConsole FPS START
	constexpr int64_t microSecondsInASecond = 1000000;
	int64_t currFps = microSecondsInASecond /  elapsedMicroseconds;
	if(currFps > _maxFrames){
		currFps = _maxFrames;
	}
	textContents = "FPS:  ";
	textContents.append(std::to_string(currFps));
	_debugTexts[FPS_TEXT_IDX].setText(textContents);
	//debuggConsole FPS END

	//debugConsole ActiveTimers START
	textContents = "Active timers: ";
	textContents.append(std::to_string(activeTimers));
	_debugTexts[ACTIVE_TIMER_IDX].setText(textContents);
	//debugConsole ActiveTimers END
}

void DebugConsole::updateActiveWidgets(int32_t activeWidgets){
	std::string textContents = "Active widgets: ";
	textContents.append(std::to_string(activeWidgets));
	_debugTexts[ACTIVE_WIDGETS_IDX].setText(textContents);

}

void DebugConsole::draw() const{
	for(int32_t i = 0; i <DEBUG_TEXTS_COUNT; ++i){
		_debugTexts[i].draw();
	}
}

bool DebugConsole::isActive() const{
	return _isActive;
}






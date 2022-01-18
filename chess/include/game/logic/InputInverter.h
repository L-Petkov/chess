#ifndef INCLUDE_GAME_LOGIC_INPUTINVERTER_H_
#define INCLUDE_GAME_LOGIC_INPUTINVERTER_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "utils/drawing/DrawParams.h"

//Forward Declarations
class InputEvent;


class InputInverter {
public:
	int32_t init(int32_t boardWidth, int32_t boardHeight);
	void setBoardFlipType(WidgetFlip flipType);
	void invertEvent(InputEvent & e);
private:
  int32_t _boardWidth { 0 };
  int32_t _boardHeight { 0 };
  WidgetFlip _flipType = WidgetFlip::NONE;
};

#endif /* INCLUDE_GAME_LOGIC_INPUTINVERTER_H_ */

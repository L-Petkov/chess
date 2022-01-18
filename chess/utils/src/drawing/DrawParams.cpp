//Corresponding header
#include "utils/drawing/DrawParams.h"

//C system includes

//C++ system includes

//Third-party includes

//Own includes

 void DrawParams::reset(){
	frameRect = Rectangle::ZERO;

	pos = Point::UNDEFINED;

    rotationAngle = 0.0;
    rotationCenter = Point::ZERO;

	width = 0;
	height = 0;

	opacity = FULL_OPACITY;

	rsrcId = INVALID_RSRC_ID;

	widgetType = WidgetType::UNKNOWN;

	flipType = WidgetFlip::NONE;
 }


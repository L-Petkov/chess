//Corresponding header
#include "utils/drawing/Rectangle.h"
//C system includes

//C++ system includes

//Third-party includes

//Own includes

const Rectangle Rectangle::ZERO(0,0,0,0);
const Rectangle Rectangle::UNDEFINED(10000,10000,10000,10000);

Rectangle::Rectangle(int32_t inputX, int32_t inputY, int32_t inputWidth, int32_t inputHeight) :
		x(inputX), y(inputY), w(inputWidth), h(inputHeight) {

}
bool Rectangle::operator ==(const Rectangle& other) const{
	return (this->x == other.x) && (this->y == other.y) && (this->w == other.w) && (this->h == other.h);
}
bool Rectangle::operator !=(const Rectangle& other) const{
	return !(*this == other);
}

bool Rectangle::isPointInside(const Point& point) const{
	const bool isInsideX = (this->x<=point.x) && (point.x < this->x+ this->w);
	const bool isInsideY = (this->y<=point.y) && (point.y < this->y+ this->h);
	return isInsideX && isInsideY;
}

#ifndef INCLUDE_GAME_LOGIC_IMAGEPOSINVERTER_H_
#define INCLUDE_GAME_LOGIC_IMAGEPOSINVERTER_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "utils/drawing/DrawParams.h"

//Forward Declarations
class Image;
struct BoardPos;

class ImagePosInverter {
public:
	int32_t init(int32_t boardWidth, int32_t boardHeight);
	void setWidgetFlipType(WidgetFlip flipType);
	void invertImgPos(Image& img);
	void invertVectorOfImgPos(Image& img);
private:
  int32_t _boardWidth { 0 };
  int32_t _boardHeight { 0 };
  WidgetFlip _flipType = WidgetFlip::NONE;
};

#endif /* INCLUDE_GAME_LOGIC_IMAGEPOSINVERTER_H_ */

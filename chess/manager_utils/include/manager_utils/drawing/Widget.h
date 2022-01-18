#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_

//C system includes

//C++ system includes

//Third-party includes

//Own includes
#include "utils/drawing/DrawParams.h"

//Forward Declarations

class Widget {
public:

	void draw() const;

	void reset();
	// setters||||||||||||||||||||||||||||||||||||
	void setFlipType(WidgetFlip flipType);

	void setWidth(int32_t width);
	void setHeight(int32_t height);

	void setRotationCenter(const Point& rotCenter);
	void setRotation(double angle);

	void setPosition(const Point& pos);
	void setPosition(const int32_t x , const int32_t y);
	void setPosX(const int32_t x);
	void setPosY(const int32_t y);
	void setOpacity(int32_t opacity);
	//endSetters|||||||||||||||||||||||||||||||||||
	//getters///////////////////////////////
	int32_t getWidth() const;
	int32_t getHeight() const;
	double getRotation() const;
	int32_t getOpacity() const;
	Point getPosition()const ;
	int32_t getX() const;
	int32_t getY() const;
	DrawParams getDrawParams()const;
	int32_t getRsrcId()const;
	//endGeters///////////////////////////
	void activateAlphaModulation();
	void deactivateAlphaModulation();

	void show();
	void hide();

	void moveRight(int32_t delta);
	void moveLeft(int32_t delta);
	void moveUp(int32_t delta);
	void moveDown(int32_t delta);
	void rotateRight(double delta);
	void rotateLeft(double delta);

	bool containsPoint(const Point& pos) const;

	bool isVisible() const;
	bool isCreated() const;
protected:
	DrawParams _drawParams;

	bool _isCreated = false;
	bool _isDestroyed = true;
	bool _isVisible = true;
	bool _isAlphaModulationEnabled = false;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_ */

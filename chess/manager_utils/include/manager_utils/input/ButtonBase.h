#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTONBASE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTONBASE_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/drawing/Image.h"

//Forward Declaration
class InputEvent;


enum ButtonStates {
  UNCLICKED, CLICKED, DISABLED
};


class ButtonBase : public Image{
public:
	virtual ~ButtonBase() = default;
	virtual void handleEvent(const InputEvent &e) = 0;


	virtual void draw()const;

	void destroy();

	void lockInput();
	void unlockInput();

	bool isInputUnlocked() const;

	bool containsEvent(const InputEvent &e)const;

private:
	bool _isInputUnlocked = true;
};
#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTONBASE_H_ */

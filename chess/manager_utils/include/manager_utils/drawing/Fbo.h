#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_FBO_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_FBO_H_


//C system includes

//C++ system includes
#include <cstdint>
#include <vector>

//Third-party includes

//Own includes
#include "manager_utils/drawing/Widget.h"
#include "utils/drawing/Color.h"

//Forward Declarations


class FBO: public Widget {
public:
	~FBO();
	void create(int32_t width, int32_t height, const Point &pos = Point::ZERO,
	                   const Color &clearColor = Colors::BLACK);
	void destroy();
	void unlock();
	void lock();
	void reset();
	void addWidget(const Widget &widget);
	void update()const;
private:
	std::vector<DrawParams> _storedItems;
	Color _clearColor = Colors::BLACK;
	bool _isLocked = true;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_FBO_H_ */

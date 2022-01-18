#ifndef SDL_UTILS_CONFIG_MONITORWINDOWCFG_H_
#define SDL_UTILS_CONFIG_MONITORWINDOWCFG_H_


//C system includes

//C++ system includes
#include <cstdint>
#include <string>
//Third-party includes

//Own includes
#include"utils/drawing/Point.h"
//Forward Declarations

enum WindowFlags{
	WINDOW_SHOWN = 4,//SDL_WINDOW_SHOWN
	WINDOW_FULLSCREEN_DESKTOP = 4097, //SDL_WINDOW_FULLSCREEN_DESKTOP

};

struct MonitorWindowCfg {
	std::string windowName;
	Point windowPos = Point::UNDEFINED;
	int32_t windowWidth = { 0 };
	int32_t windowHeight = { 0 };
	WindowFlags windowFlags = WINDOW_SHOWN;
//  //Window modes:
//  //SDL_WINDOW_SHOWN - for windowed version

//  int32_t displayMode { 0 };
//  int32_t windowWidth { 0 };
//  int32_t windowHeight { 0 };
//
//  std::string windowName;
};



#endif /* SDL_UTILS_CONFIG_MONITORWINDOWCFG_H_ */

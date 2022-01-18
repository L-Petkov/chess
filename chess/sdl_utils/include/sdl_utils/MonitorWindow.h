#ifndef SDL_UTILS_MONITORWINDOW_H_
#define SDL_UTILS_MONITORWINDOW_H_

//C system includes

//C++ system includes
#include <cstdint>
#include <string>
//Third-party includes

//Own includes

#include "sdl_utils/config/MonitorWindowCfg.h"

//Forward Declarations
struct SDL_Window;
struct SDL_Surface;

class MonitorWindow {
public:
	MonitorWindow() = default;
	~MonitorWindow();

	MonitorWindow(const MonitorWindow& other) = delete;
	MonitorWindow(const MonitorWindow&& other) = delete;

	MonitorWindow& operator=(const MonitorWindow& other) = delete;
	MonitorWindow& operator=(const MonitorWindow&& other) = delete;

	int32_t init(const MonitorWindowCfg& cfg);
	void deinit();
	void updateWindowSurface();
	SDL_Window* getWindow();
private:
	SDL_Window* _window = nullptr;
};

#endif /* SDL_UTILS_MONITORWINDOW_H_ */

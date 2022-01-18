#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/managers/ManagerHandler.h"
#include "game/Game.h"
#include "mainMenu/MainMenu.h"
#include "manager_utils/debug/DebugConsole.h"
#include "sdl_utils/InputEvent.h"

//Forward Declarations
struct EngineConfig;





class Engine  {
public:

	int32_t init(const EngineConfig& cfg);
	void deinit();
	void start();


private:

	void mainLoop();
	void drawFrame();
	bool processFrame();
	void handleEvent();

	void limitFPS(int64_t elapsedTimeMicroSeconds);

	ManagerHandler _managerHandler;
	InputEvent _event;
	Game _game;
	MainMenu _mainMenu;
	DebugConsole _debugConsole;

};

#endif /* ENGINE_ENGINE_H_ */

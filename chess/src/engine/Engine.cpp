//Corresponding header
#include "engine/Engine.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "engine/config/EngineConfig.h"
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/TimerMgr.h"

#include "utils/thread/ThreadUtils.h"
#include "utils/time/Time.h"

#include "sdl_utils/Texture.h"


int32_t Engine::init(const EngineConfig &cfg) {

	if (EXIT_SUCCESS != _managerHandler.init(cfg.managerHandlerCfg)) {
		std::cerr << "_managerHandler.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != _event.init()) {
		std::cerr << "event.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != _game.init(cfg.gameCfg,&_mainMenu)) {
		std::cerr << "_game.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != _mainMenu.init(cfg.mainMenuCfg, _game, cfg.gameCfg)) {
		std::cerr << "_mainMenu.init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != _debugConsole.init(cfg.managerHandlerCfg.drawMgrCfg.maxFrameRate,
			cfg.debugConsoleFontId)) {
		std::cerr << "_debugConsole.init() failed." << std::endl;
		return EXIT_FAILURE;
	}
	gTimerMgr->onInitEnd();

	return EXIT_SUCCESS;
}
void Engine::deinit() {
	_game.deinit();
	_mainMenu.deinit();
	_event.deinit();
	_managerHandler.deinit();

}

void Engine::start() {
	mainLoop();
}

void Engine::mainLoop() {
	Time time;
	while (true) {
		time.getElapsed();
		const bool shouldExit = processFrame();
		if (shouldExit) {
			return;
		}
		const int64_t elapsedTime = time.getElapsed().toMicroseconds();
		if(_debugConsole.isActive()){
			_debugConsole.update(elapsedTime, gTimerMgr->getActiveTimersCount());
		}
		limitFPS(elapsedTime);
	}
}
void Engine::drawFrame() {

	gDrawMgr->clearScreen();

	if(_mainMenu.isActive()){
		_mainMenu.draw();
		gDrawMgr->finishFrame();
		return;
	}

	_game.draw();

	if(_debugConsole.isActive()){
		_debugConsole.updateActiveWidgets(gDrawMgr->getActiveWidgets());
		_debugConsole.draw();//swap with the above function if u want the
		//texts of the console to be counted in the total sum active widgets
	}

	gDrawMgr->finishFrame();
}
bool Engine::processFrame() {
	_managerHandler.process();

	while (_event.pollEvent()) {
		if(_mainMenu.checkForExitRequest()){
			return true;
		}
		if (_event.checkForExitRequest()) {
			return true;
		}
		handleEvent();
	}
	drawFrame();
	return false;
}
void Engine::handleEvent() {
	if(_mainMenu.isActive()){
		_mainMenu.handleEvent(_event);
		return;
	}
	_game.handleEvent(_event);
	_debugConsole.handleEvent(_event);
}
void Engine::limitFPS(int64_t elapsedTimeMicroSeconds) {
	constexpr int64_t microSecondsInASecond = 1000000;
	const int64_t microSecondsPerFrame = microSecondsInASecond / gDrawMgr->getMaxFrameRate();
	const int64_t sleepDurationMicroSeconds = microSecondsPerFrame - elapsedTimeMicroSeconds;
	if (sleepDurationMicroSeconds > 0) {
		Threading::sleepFor(sleepDurationMicroSeconds);
	}
}

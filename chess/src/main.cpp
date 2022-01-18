//C system includes

//C++ system includes
#include <cstdint>
#include <iostream>

//Third-party includes

//Own includes
#include "engine/Engine.h"
#include "engine/EngineConfigLoader.h"
#include "sdl_utils/SDLLoader.h"


static int32_t runAplication(){

	Engine engine;

	if (EXIT_SUCCESS != engine.init(EngineConfigLoader::loadConfig())) {
			std::cerr << "engine.init() failed." << std::endl;
			return EXIT_FAILURE;
	}

	engine.start();
	engine.deinit();

	return EXIT_SUCCESS;
}

int32_t main([[maybe_unused]] int32_t argc, [[maybe_unused]] char *argv[]) {

	if (EXIT_SUCCESS != SDLLoader::init()) {
		std::cerr << "SDLLoader::init() failed." << std::endl;
		return EXIT_FAILURE;
	}

	if (EXIT_SUCCESS != runAplication()) {
		std::cerr << "runAplication() failed." << std::endl;
		return EXIT_FAILURE;
	}
	SDLLoader::deinit();

	return EXIT_SUCCESS;
}

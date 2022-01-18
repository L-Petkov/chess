#ifndef ENGINE_CONFIG_ENGINECONFIG_H_
#define ENGINE_CONFIG_ENGINECONFIG_H_

//C system includes

//C++ system includes
#include <cstdint>
//Third-party includes

//Own includes
#include "manager_utils/config/ManagerHandlerCfg.h"
#include "mainMenu/config/MainMenuCfg.h"

#include "game/config/GameCfg.h"

//Forward Declarations

struct EngineConfig {
	ManagerHandlerCfg managerHandlerCfg;
	MainMenuCfg mainMenuCfg;
	GameCfg gameCfg;

	int32_t debugConsoleFontId;
};


#endif /* ENGINE_CONFIG_ENGINECONFIG_H_ */

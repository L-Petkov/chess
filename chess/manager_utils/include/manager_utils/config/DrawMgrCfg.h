#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_CONFIG_DRAWMGRCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_CONFIG_DRAWMGRCFG_H_


//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "sdl_utils/config/MonitorWindowCfg.h"

//Forward Declarations

struct DrawMgrCfg {

	MonitorWindowCfg windowCfg;
	int64_t maxFrameRate { 0 };
};


#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_CONFIG_DRAWMGRCFG_H_ */

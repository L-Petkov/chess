#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHANDLER_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHANDLER_H_

//C system includes

//C++ system includes
#include <cstdint>
//Third-party includes

//Own includes
#include "manager_utils/managers/MgrBase.h"

//Forward Declarations
struct ManagerHandlerCfg;

class ManagerHandler {
public:
	int32_t init(const ManagerHandlerCfg& cfg);
	void deinit();
	void process();

private:
	void nullifyGlobalMgr(int32_t mgrIdx);
	MgrBase* _managers[MANAGERS_COUNT];
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_MANAGERHANDLER_H_ */

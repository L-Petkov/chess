//Corresponding header
#include "manager_utils/managers/ManagerHandler.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "manager_utils/config/ManagerHandlerCfg.h"
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/RsrcMgr.h"
#include "manager_utils/managers/TimerMgr.h"


int32_t ManagerHandler::init(const ManagerHandlerCfg& cfg){
	gDrawMgr = new DrawMgr();
	if (nullptr == gDrawMgr) {
		std::cerr << "Error, bad alloc for DrawMgr." << std::endl;
		return EXIT_FAILURE;
		}
	if (EXIT_SUCCESS != gDrawMgr->init(cfg.drawMgrCfg)) {
		std::cerr << "gDrawMgr.iniit() failed." << std::endl;
		return EXIT_FAILURE;
	}
	gRsrcMgr = new RsrcMgr();
	if (nullptr == gRsrcMgr) {
		std::cerr << "Error, bad alloc for RsrcMgr." << std::endl;
		return EXIT_FAILURE;
	}
	if (EXIT_SUCCESS != gRsrcMgr->init(cfg.rsrcMgrCfg)) {
		std::cerr << "gRsrcMgr.iniit() failed." << std::endl;
		return EXIT_FAILURE;
	}
	gTimerMgr = new TimerMgr();
		if (nullptr == gTimerMgr) {
			std::cerr << "Error, bad alloc for gTimerMgr." << std::endl;
			return EXIT_FAILURE;
		}
		if (EXIT_SUCCESS != gTimerMgr->init()){
			std::cerr << "gTimerMgr.iniit() failed." << std::endl;
			return EXIT_FAILURE;
		}

	_managers[DRAW_MGR_IDX] = static_cast<MgrBase*>(gDrawMgr);
	_managers[RSRC_MGR_IDX] = static_cast<MgrBase*>(gRsrcMgr);
	_managers[TIMER_MGR_IDX] = static_cast<MgrBase*>(gTimerMgr);

	return EXIT_SUCCESS;
}

void ManagerHandler::deinit(){

	for(int32_t i = MANAGERS_COUNT-1 ;i >= 0 ;--i){
		_managers[i]->deinit();
		_managers[i]=nullptr;
		nullifyGlobalMgr(i);
	}
}
void ManagerHandler::process(){
	for(int32_t i=0;i<MANAGERS_COUNT;++i){
		_managers[i]->process();

	}
}
void ManagerHandler::nullifyGlobalMgr(int32_t mgrIdx){
	switch(mgrIdx){

	case DRAW_MGR_IDX:
		delete gDrawMgr;
		gDrawMgr = nullptr;
	break;

	case RSRC_MGR_IDX:
		delete gRsrcMgr;
		gRsrcMgr = nullptr;
	break;

	case TIMER_MGR_IDX:
		delete gTimerMgr;
		gTimerMgr = nullptr;
	break;

	default:
		 std::cerr << "Received invalid mgrIdx" << std::endl;
	break;

	}
}



//Corresponding header
#include "manager_utils/time/TimerClient.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "manager_utils/managers/TimerMgr.h"




void TimerClient::startTimer(int64_t interval, int32_t timerId, TimerType timerType){
	if (!gTimerMgr) {
		return;
	}
	if (gTimerMgr->isActiveTimerId(timerId)) {
		std::cerr << "Warning, timer with Id: " << timerId << " already exist. "
				  "Will not start new timer"
				  << std::endl;
		return;
	}

	constexpr auto minTimerInterval =20;//ms
	if(interval < minTimerInterval){
		std::cerr << "Timer with id: " << timerId << " requested interval: "
				  << interval << ", wich is lower than the minimum one: "
				  << minTimerInterval << std::endl;
		return;
	}

	const TimerData data(interval,interval, this, timerType);
	gTimerMgr->startTimer(timerId, data);
}

void TimerClient::stopTimer(int32_t timerId){
	if (!gTimerMgr) {
			return;
		}
	gTimerMgr->stopTimer(timerId);
}

bool TimerClient::isActiveTimerId(int32_t timerId) const{
	if (!gTimerMgr) {// this and the gTimerMgr in the secondd return do the same
			return false;
		}
	return gTimerMgr && gTimerMgr->isActiveTimerId(timerId);
}






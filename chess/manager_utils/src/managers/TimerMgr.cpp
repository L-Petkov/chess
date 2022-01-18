//Corresponding header
#include "manager_utils/managers/TimerMgr.h"

//C system includes

//C++ system includes
#include <iostream>
//Third-party includes

//Own includes
#include "manager_utils/time/TimerClient.h"



TimerMgr* gTimerMgr = nullptr;

int32_t TimerMgr::init(){
	_elapsedTime.getElapsed();
	return EXIT_SUCCESS;
}

void TimerMgr::deinit() {

}


void TimerMgr::process() {
	removeTimersInternal();

	const int64_t msElapsed = _elapsedTime.getElapsed().toMilliseconds();

	for (auto it = _timerMap.begin(); it != _timerMap.end(); ++it) {
		const int32_t timerId  =it->first;
		TimerData& timerData = it->second;

		it->second.remaining -= msElapsed;
		if (0 > it->second.remaining) {
		  onTimerTimeout(timerId, timerData);
		}
	}
	removeTimersInternal();
}


void TimerMgr::startTimer(int32_t timerId, const TimerData& data){
	if(isActiveTimerId(timerId)){
		std::cerr << "Error, trying to start an already existing timer with Id: "<< timerId << std::endl;
		return;
	}

	_timerMap.emplace(timerId, data);
}

void TimerMgr::stopTimer(int32_t timerId){
	if(!isActiveTimerId(timerId)){
		std::cerr << "Error, trying to stop a non existing timer with Id: "<< timerId << std::endl;
		return;
		}
	_removeTimerSet.insert(timerId);
}

bool TimerMgr::isActiveTimerId(int32_t timerId) const {
  return (_removeTimerSet.end() == _removeTimerSet.find(timerId))
      && (_timerMap.end() != _timerMap.find(timerId));
}

void TimerMgr::onInitEnd(){
	_elapsedTime.getElapsed();
}

size_t TimerMgr::getActiveTimersCount() const{
	return (_timerMap.size() - _removeTimerSet.size());
}

void TimerMgr::removeTimersInternal() {
  for (const int32_t timerId : _removeTimerSet) {
    auto mapIt = _timerMap.find(timerId);
    if (mapIt != _timerMap.end()) {
      _timerMap.erase(mapIt);
    }
  }

  //clear the removeTimerSet
  _removeTimerSet.clear();
}

void  TimerMgr::onTimerTimeout(int32_t timerId, TimerData& timer){
	timer.tcInstance->onTimeout(timerId);

	if(TimerType::ONESHOT == timer.timerType){
		_removeTimerSet.insert(timerId);
	}

	timer.remaining += timer.interval;
}



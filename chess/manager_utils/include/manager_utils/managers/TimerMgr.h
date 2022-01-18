#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMERMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMERMGR_H_

//C system includes

//C++ system includes
#include <map>
#include <set>

//Third-party includes

//Own includes
#include "manager_utils/managers/MgrBase.h"
#include "manager_utils/time/TimerData.h"
#include "utils/time/Time.h"

//Forward Declaration

class TimerMgr: public MgrBase {
public:
	TimerMgr() = default;

	TimerMgr(const TimerMgr &other) = delete;
	TimerMgr(TimerMgr &&other) = delete;

	TimerMgr& operator=(const TimerMgr &other) = delete;
	TimerMgr& operator=(TimerMgr &&other) = delete;
///////////////////////////////////////////////////////////////////////////////////////////////////////
	int32_t init();
	void deinit() final;
	void process() final;

	void startTimer(int32_t timerId, const TimerData& data);

	void stopTimer(int32_t timerId);
//	void detachTimerClient(int32_t timerId);
	bool isActiveTimerId(int32_t timerId) const;
	void onInitEnd();

	size_t getActiveTimersCount() const;

private:

	void removeTimersInternal();

	void  onTimerTimeout(int32_t timerId, TimerData& timer);

	Time _elapsedTime;
	std::map<int32_t, TimerData> _timerMap;
	std::set<int32_t> _removeTimerSet;
};
extern TimerMgr* gTimerMgr;


#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_TIMERMGR_H_ */

#ifndef INCLUDE_ENGINE_PROXIES_ENGINEPROXY_H_
#define INCLUDE_ENGINE_PROXIES_ENGINEPROXY_H_


//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declarations

class EngineProxy {
public:
	EngineProxy() = default;
  virtual ~EngineProxy() = default;
  virtual void onInGameExitBtnPressed() = 0;
};


#endif /* INCLUDE_ENGINE_PROXIES_ENGINEPROXY_H_ */

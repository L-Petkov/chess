#ifndef INCLUDE_MAINMENU_PROXIES_MAINMENUPROXY_H_
#define INCLUDE_MAINMENU_PROXIES_MAINMENUPROXY_H_


//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declarations

class MainMenuProxy {
public:
  MainMenuProxy() = default;
  virtual ~MainMenuProxy() = default;
  virtual void onButtonPressed(int32_t buttonId) = 0;
};



#endif /* INCLUDE_MAINMENU_PROXIES_MAINMENUPROXY_H_ */

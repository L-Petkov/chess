#ifndef SDL_UTILS_CONFIG_TEXTCONTAINERCFG_H_
#define SDL_UTILS_CONFIG_TEXTCONTAINERCFG_H_

//C system includes

//C++ system includes
#include <string>
#include <unordered_map>

//Third-party includes

//Own includes

//Forward Declarations



struct FontCfg {
  std::string location;
  int32_t fontSize = 0;
};

struct TextContainerCfg {
  std::unordered_map<int32_t, FontCfg> fontConfigs;
};



#endif /* SDL_UTILS_CONFIG_TEXTCONTAINERCFG_H_ */

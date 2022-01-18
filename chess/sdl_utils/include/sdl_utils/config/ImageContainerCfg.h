#ifndef SDL_UTILS_CONFIG_IMAGECONTAINERCFG_H_
#define SDL_UTILS_CONFIG_IMAGECONTAINERCFG_H_
//C system includes

//C++ system includes
#include <cstdint>
#include <unordered_map>
#include <vector>

//Third-party includes

//Own includes
#include "utils/drawing/Rectangle.h"
//Forward Declarations

struct ImageCfg {
  std::string location;
  std::vector<Rectangle> frames;
};

struct ImageContainerCfg {
  std::unordered_map<int32_t, ImageCfg> imageConfigs;
};


#endif /* SDL_UTILS_CONFIG_IMAGECONTAINERCFG_H_ */

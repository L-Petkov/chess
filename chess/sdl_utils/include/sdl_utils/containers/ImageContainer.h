#ifndef SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_
#define SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_
//C system includes

//C++ system includes
#include <cstdint>
#include <unordered_map>



//Third-party includes

//Own includes

#include "sdl_utils/config/ImageContainerCfg.h"
#include "utils/drawing/Rectangle.h"

//Forward Declarations
struct SDL_Texture;


using Frames = std::vector<Rectangle>;


class ImageContainer {
public:

	SDL_Texture* getImageTexture(int32_t rsrcId) const;

	const Frames& getImageFrame(int32_t rsrcId) const;
protected:
	int32_t init(const ImageContainerCfg& cfg);
	void deinit();

private:
	int32_t loadSingleResource(const ImageCfg& resCfg, int32_t rsrcId);

	//the textures we'll be drawing
	std::unordered_map<int32_t, SDL_Texture*> _textures;

	std::unordered_map<int32_t, Frames> _textureFrames;

};

#endif /* SDL_UTILS_CONTAINERS_IMAGECONTAINER_H_ */

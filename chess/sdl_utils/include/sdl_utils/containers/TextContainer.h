#ifndef SDL_UTILS_CONTAINERS_CONTAINER_H_
#define SDL_UTILS_CONTAINERS_TEXTCONTAINER_H_
//C system includes

//C++ system includes
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>

//Third-party includes

//Own includes

#include "sdl_utils/config/TextContainerCfg.h"

//Forward Declarations
struct SDL_Texture;
typedef struct _TTF_Font TTF_Font;
class Color;

class TextContainer {
public:

	void createText(const std::string& text, const Color &color, int32_t fontId,
	                         int32_t &outTextId, int32_t &outTextWidth,
	                         int32_t &outTextHeight);

	void reloadText(const std::string& text, const Color &color, int32_t fontId,
	                         int32_t textId, int32_t &outTextWidth,
	                         int32_t &outTextHeight);

	void unloadText(int32_t textId);

	SDL_Texture* getTextTexture(int32_t textId) const;

protected:
	int32_t init(const TextContainerCfg& cfg);

	void deinit();

private:
	void occupyFreeSlotIndex(int32_t& outIdx, SDL_Texture* texture);
	void freeSlotIndex(int32_t index);
	//the textures we'll be drawing
	std::vector<SDL_Texture*> _textures;

	std::unordered_map<int32_t, TTF_Font*> _fonts;
};

#endif /* SDL_UTILS_CONTAINERS_TEXTCONTAINER_H_ */

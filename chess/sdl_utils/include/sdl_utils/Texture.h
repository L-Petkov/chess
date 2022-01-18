#ifndef SDL_UTILS_TEXTURE_H_
#define SDL_UTILS_TEXTURE_H_

//C system includes

//C++ system includes
#include <cstdint>
#include <string>
//Third-party includes

//Own includes
#include "utils/drawing/DrawParams.h"

//Forward Declarations
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
typedef struct _TTF_Font TTF_Font;
struct Color;


class Texture {
public:
	Texture() = default ;
	~Texture() = default;

	static int32_t createSurfaceFromFile(const std::string filePath, SDL_Surface*& outSurface);
	static int32_t createTextureFromFile(const std::string filePath, SDL_Texture*& outTexture);
	static int32_t createTextureFromSurface(SDL_Surface*& inOutSurface, SDL_Texture*& outTexture);
	static int32_t createTextureFromText(const std::string& text, const Color &color, TTF_Font* font,
										SDL_Texture*& outTexture,
										int32_t &outTextWidth,
										int32_t &outTextHeight);
	static int32_t createEmptyTexture(int32_t width, int32_t height, SDL_Texture*& outTexture);
	static void freeSurface(SDL_Surface*& outSurface);
	static void freeTexture(SDL_Texture*& outTexture);

	static void setRenderer(SDL_Renderer* renderer);

	static int32_t setBlendModeTexture(SDL_Texture *texture, BlendMode blendMode);

	static int32_t setAlphaTexture(SDL_Texture *texture, int32_t alpha);

	static int32_t clearCurrentRendererTarget(const Color &color);
	static int32_t setRendererTarget(SDL_Texture *target);
	static int32_t resetRendererTarget();
};

#endif /* SDL_UTILS_TEXTURE_H_ */

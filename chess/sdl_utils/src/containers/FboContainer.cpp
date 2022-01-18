//Corresponding header
#include "sdl_utils/containers/FboContainer.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes
#include <SDL_ttf.h>

//Own includes
#include "sdl_utils/Texture.h"

int32_t FboContainer::init() {

	return EXIT_SUCCESS;
}

void FboContainer::deinit() {
	for (auto& texture : _textures) {
		if(texture){
		Texture::freeTexture(texture);
		}
	}
}

void FboContainer::createFbo(int32_t fboWidth, int32_t fboHeight, int32_t &outFboId) {

	SDL_Texture* textTexture = nullptr;
	if (EXIT_SUCCESS
			!= Texture::createEmptyTexture(fboWidth, fboHeight, textTexture)) {
		std::cerr << "Error Texture::createEmptyTexture() failed."
				  << std::endl;
		return;
	}
	occupyFreeSlotIndex(outFboId, textTexture);
}


void FboContainer::unloadFbo(int32_t fboId) {
	if (0 > fboId || fboId >= static_cast<int32_t>(_textures.size())) {
		std::cerr << "Error, trying to unload non-existing fboId: " << fboId << std::endl;
		return;
	}
	freeSlotIndex(fboId);
}

SDL_Texture* FboContainer::getFboTexture(int32_t fboId) const {
	if (0 > fboId || fboId >= static_cast<int32_t>(_textures.size())) {
		std::cerr << "Error, trying to get non-existing fboId: " << fboId << std::endl;
		return nullptr;
	}
	return _textures[fboId];
}

void FboContainer::occupyFreeSlotIndex(int32_t &outIdx, SDL_Texture *texture) {
	const int32_t size = static_cast<int32_t>(_textures.size());

	for (int32_t i = 0; i < size; ++i) {
		if (_textures[i] == nullptr) { //found free  index
			outIdx = i;
			_textures[i] = texture;
			return;
		}
	}
	_textures.push_back(texture);
	outIdx = size;
}

void FboContainer::freeSlotIndex(int32_t index) {
	Texture::freeTexture(_textures[index]);
}

//Corresponding header
#include "sdl_utils/containers/TextContainer.h"
//C system includes

//C++ system includes
#include <iostream>

//Third-party includes
#include <SDL_ttf.h>

//Own includes
#include "sdl_utils/Texture.h"

int32_t TextContainer::init(const TextContainerCfg &cfg) {

	TTF_Font *currFont = nullptr;
	for (const auto &pair : cfg.fontConfigs) {
		const auto key = pair.first;
		const FontCfg &fontCfg = pair.second;
		currFont = TTF_OpenFont(fontCfg.location.c_str(), fontCfg.fontSize);

		if (currFont == nullptr) {
			std::cerr << "Error TTF_OpenFont failed: for fontLocation: " << fontCfg.location
					<< ". Reason: " << SDL_GetError() << std::endl;
			return EXIT_FAILURE;
		}
		_fonts[key] = currFont;
	}

	return EXIT_SUCCESS;
}

void TextContainer::deinit() {
	for (auto &pair : _fonts) {
		TTF_CloseFont(pair.second);
	}
	for (auto& texture : _textures) {
	    if(texture){
		Texture::freeTexture(texture);
	    }
	}
}

void TextContainer::createText(const std::string &text, const Color &color, int32_t fontId,
		int32_t &outTextId, int32_t &outTextWidth, int32_t &outTextHeight) {
	auto it = _fonts.find(fontId);
	if (it == _fonts.end()) {
		std::cerr << "Error, fontId: " << fontId << " could not be found. Will not create text: "
				<< text << std::endl;
		return;
	}
	TTF_Font *currFont = it->second;
	SDL_Texture *textTexture = nullptr;
	if (EXIT_SUCCESS
			!= Texture::createTextureFromText(text, color, currFont, textTexture, outTextWidth,
					outTextHeight)) {
		std::cerr << "Error Texture::createTextureFromText() failed for text: " << text
				<< std::endl;
		return;
	}
	occupyFreeSlotIndex(outTextId, textTexture);
}

void TextContainer::reloadText(const std::string &text, const Color &color, int32_t fontId,
		int32_t textId, int32_t &outTextWidth, int32_t &outTextHeight) {
	auto it = _fonts.find(fontId);
	if (it == _fonts.end()) {
		std::cerr << "Error, fontId: " << fontId << " could not be found. Will not reload text: "
				<< text << std::endl;
		return;
	}

	TTF_Font *currFont = it->second;
	SDL_Texture *textTexture = nullptr;
	if (EXIT_SUCCESS
			!= Texture::createTextureFromText(text, color, currFont, textTexture, outTextWidth,
					outTextHeight)) {
		std::cerr << "Error Texture::createTextureFromText() failed for text: " << text
				<< std::endl;
		return;
	}

	freeSlotIndex(textId);

	_textures[textId] = textTexture;
}

void TextContainer::unloadText(int32_t textId) {
	if (0 > textId || textId >= static_cast<int32_t>(_textures.size())) {
		std::cerr << "Error, trying to unload non-existing textId: " << textId << std::endl;
		return;
	}
	freeSlotIndex(textId);
}

SDL_Texture* TextContainer::getTextTexture(int32_t textId) const {
	if (0 > textId || textId >= static_cast<int32_t>(_textures.size())) {
		std::cerr << "Error, trying to get non-existing textId: " << textId << std::endl;
		return nullptr;
	}
	return _textures[textId];
}

void TextContainer::occupyFreeSlotIndex(int32_t &outIdx, SDL_Texture *texture) {
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

void TextContainer::freeSlotIndex(int32_t index) {
	Texture::freeTexture(_textures[index]);
}

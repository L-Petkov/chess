//Corresponding header
#include "sdl_utils/containers/ImageContainer.h"
//C system includes

//C++ system includes
#include <iostream>
//Third-party includes

//Own includes
#include "sdl_utils/Texture.h"


static const Frames EMPTY_FRAMES {Rectangle::ZERO};

int32_t ImageContainer::init(const ImageContainerCfg& cfg){
	for(const auto& pair : cfg.imageConfigs ){
		const auto  elem = pair.second;
		const auto rsrcId = pair.first;
		if(EXIT_SUCCESS != loadSingleResource(elem, rsrcId)){
			std::cerr << " loadSingleResource fail for file: " << elem.location << std::endl;
			return EXIT_FAILURE;
		}
	   _textureFrames[pair.first] = elem.frames;

	}
	return EXIT_SUCCESS;
}
void ImageContainer::deinit(){
	for(auto& pair : _textures ){
	Texture::freeTexture(pair.second);
	}

}

SDL_Texture* ImageContainer::getImageTexture(int32_t rsrcId) const{
	auto it = _textures.find(rsrcId);
	if(it == _textures.end()){
		std::cerr << "Error, invalid rsrcID: " << rsrcId << " requested." << std::endl;
		return nullptr;
	}
	return it->second;
}

const Frames& ImageContainer::getImageFrame(int32_t rsrcId) const{
	auto it = _textureFrames.find(rsrcId);
		if(it == _textureFrames.end()){
			std::cerr << "Error, invalid rsrcID: " << rsrcId << " requested. Returning EMPTY_FRAMES." << std::endl;
			return EMPTY_FRAMES;
		}
		return it->second;

}

int32_t ImageContainer::loadSingleResource(const ImageCfg& resCfg, int32_t rsrcId){
	SDL_Texture* texture = nullptr;
	if(EXIT_SUCCESS != Texture::createTextureFromFile(resCfg.location, texture)){
		std::cerr << "Texture::createTextureFromFile fail for file: " << resCfg.location << std::endl;
		return EXIT_FAILURE;
	}

	_textures[rsrcId] = texture;
	_textureFrames[rsrcId] = resCfg.frames;

	return EXIT_SUCCESS;
}

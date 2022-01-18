//Corresponding header
#include "sdl_utils/Renderer.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes
#include <SDL_render.h>
#include <SDL_hints.h>

//Own includes
#include "sdl_utils/Texture.h"

int32_t Renderer::init(SDL_Window *window){

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
	  std::cerr << "Warning: Linear texture filtering not enabled! "
			 "SDL_SetHint() failed. SDL Error: " << SDL_GetError() << std::endl;
	  return EXIT_FAILURE;
	}

	constexpr auto unspecifiedDriverId = -1;
	_sdlRenderer = SDL_CreateRenderer(window, unspecifiedDriverId,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if(nullptr == _sdlRenderer){
		std::cerr << "SDL_CreateRenderer() failed. Reason: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}
	if(EXIT_SUCCESS != SDL_SetRenderDrawColor(_sdlRenderer,
			_clearColor.rgba.r, _clearColor.rgba.g, _clearColor.rgba.b, _clearColor.rgba.a)){
		std::cerr << "SDL_SetRenderDrawColor() failed. Reason: " << SDL_GetError() << std::endl;
				return EXIT_FAILURE;
	}
	Texture::setRenderer(_sdlRenderer);

	return EXIT_SUCCESS;
}
void Renderer::deinit(){
	if(_sdlRenderer){
		SDL_DestroyRenderer(_sdlRenderer);
		_sdlRenderer = nullptr;
	}

}


void Renderer::clearScreen(){
	clearCurrentRendererTarget(_clearColor); //Texture::clearCurrentRendererTarget(color);
}
void Renderer::finishFrame(){
	if(!_isRendererLocked){
		std::cerr << "WARNING , Renderer was left unlocked. Self-locking locking renderer."
				"Some  FBO will be in a broken state."
				  << std::endl;
		_isRendererLocked = true;
		resetRendererTarget();
	}
	SDL_RenderPresent(_sdlRenderer);
	_activeWidgets = 0;
}
void Renderer::renderTexture(SDL_Texture *texture, const DrawParams& drawParams) const{
	if(WidgetType::IMAGE ==drawParams.widgetType){
		drawImage(drawParams, texture);
	}
	else if(WidgetType::TEXT ==drawParams.widgetType ||
			WidgetType::FBO ==drawParams.widgetType){
		drawText(drawParams, texture); // drawText() calls only
		//drawTextureInternal(drawParams, texture); for the time being
		//left drawText() coz not sure if text can have opacity and if in future will need it
	}
	else{
		std::cerr << "Error, received unsupported WidgetType: "
				  << static_cast<int32_t>(drawParams.widgetType)
				  << " for rsrcId: "<< drawParams.rsrcId << std::endl;

		--_activeWidgets;
	}
	++_activeWidgets;
}
void Renderer::setWidgetBlendMode(SDL_Texture *texture, BlendMode blendMode){
	if(EXIT_SUCCESS != Texture::setBlendModeTexture(texture, blendMode)){
		std::cerr << "Texture::setBlendModeTexture failed."  << std::endl;
	}
}

void Renderer::setWidgetOpacity(SDL_Texture *texture, int32_t opacity){
	if(EXIT_SUCCESS != Texture::setAlphaTexture(texture,opacity)){
		std::cerr << "Texture::setAlphaTexture failed."  << std::endl;
	}
}

int32_t Renderer::getActiveWidgets()const{
	return _activeWidgets;
}

int32_t Renderer::clearCurrentRendererTarget(const Color &color){
	return Texture::clearCurrentRendererTarget(color);
}

int32_t Renderer::setRendererTarget(SDL_Texture *target){
	return Texture::setRendererTarget(target);
}

int32_t Renderer::resetRendererTarget(){
	return Texture::resetRendererTarget();
}

int32_t Renderer::lockRenderer(){
	if(_isRendererLocked){
		std::cerr << "Error, in Renderer::lockRenderer(), Renderer was already locked"
				  << std::endl;
		return EXIT_FAILURE;
	}
	_isRendererLocked = true;
	return EXIT_SUCCESS;
}

int32_t Renderer::unlockRenderer(){
	if(!_isRendererLocked){
		std::cerr << "Error, in Renderer::unlockRenderer(), Renderer was not locked in the first place"
				  << std::endl;
		return EXIT_FAILURE;
	}
	_isRendererLocked = false;;

	return EXIT_SUCCESS;
}


void Renderer::drawImage(const DrawParams& drawParams, SDL_Texture *texture) const{


	if(FULL_OPACITY == drawParams.opacity){
		drawTextureInternal(drawParams,texture);
	}
	else {
		if(EXIT_SUCCESS != Texture::setAlphaTexture(texture, drawParams.opacity)){
			std::cerr << "Texture::setAlphaTexture() failed for rsrcId: "
					  << drawParams.rsrcId << std::endl;
		}
		drawTextureInternal(drawParams,texture);
		if(EXIT_SUCCESS != Texture::setAlphaTexture(texture, FULL_OPACITY)){
			std::cerr << "Texture::setAlphaTexture() failed for rsrcId: "
					  << drawParams.rsrcId << std::endl;
		}
	}
}
void Renderer::drawText(const DrawParams& drawParams, SDL_Texture *texture) const{
	drawTextureInternal(drawParams,texture);
}

void Renderer::drawTextureInternal(const DrawParams& drawParams, SDL_Texture *texture) const{

	const SDL_Rect destRect ={.x = drawParams.pos.x, .y = drawParams.pos.y,
								  .w = drawParams.width, .h = drawParams.height};

	const SDL_Rect* sourceRect = reinterpret_cast<const SDL_Rect*> (&drawParams.frameRect);
	const SDL_Point* center = reinterpret_cast<const SDL_Point*>(&drawParams.rotationCenter);

			const int32_t err = SDL_RenderCopyEx(_sdlRenderer,texture,sourceRect,&destRect,
			drawParams.rotationAngle,
			center,
			static_cast<SDL_RendererFlip>(drawParams.flipType));

	if(EXIT_SUCCESS != err){
		std::cerr << "SDL_RenderCopy() failed for rsrcId: " << drawParams.rsrcId << ". Reason:  "
            	  << SDL_GetError() << std::endl;
	}

}

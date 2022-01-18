//Corresponding header
#include "manager_utils/drawing/Image.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "manager_utils/managers/RsrcMgr.h"


Image::~Image(){

	if(_isCreated && !_isDestroyed){
		destroy();
	}
}

void Image::create(int32_t rsrcId, const Point &pos){

	if(_isCreated){
		std::cerr << "Error, image with rsrcId: "
				<< rsrcId << " was already created. Will not create twice." << std::endl;
		return;
	}

	const Frames& frames = gRsrcMgr->getImageFrame(rsrcId);
	_maxFrames = static_cast<int32_t>(frames.size());

	const auto& firstFrame = frames.front();// mayble not needed coz next line
	_drawParams.frameRect = firstFrame; //frames.front();

	_drawParams.rsrcId = rsrcId;
	_drawParams.width = _drawParams.frameRect.w;
	_drawParams.height = _drawParams.frameRect.h;
	_drawParams.pos = pos;
	_drawParams.widgetType = WidgetType::IMAGE;

	_isCreated =  true;
	_isDestroyed = false;

}

void Image::destroy(){
	if(!_isCreated){
			std::cerr << "Error, image  was already destroyed." << std::endl;
			return;
	}

	_isCreated = false;
	_isDestroyed = true;

	Widget::reset();
}

void Image::setFrame(int32_t frameIdx){
	if(0 > frameIdx || frameIdx >= _maxFrames){
		std::cerr << "Error, trying to set invalid frameIdx: " <<
				frameIdx << " for Image with rsrcId: "<< _drawParams.rsrcId
				<< std::endl;
	}

	const Frames& frames = gRsrcMgr->getImageFrame(_drawParams.rsrcId);
	_drawParams.frameRect = frames[frameIdx];
	_currFrame = frameIdx;

}

void Image::setNextFrame(){
	++_currFrame;

	if(_currFrame == _maxFrames){
		_currFrame = 0;
	}

	const Frames& frames = gRsrcMgr->getImageFrame(_drawParams.rsrcId);
	_drawParams.frameRect = frames[_currFrame];
}

void Image::setPrevFrame(){
	--_currFrame;
	if(_currFrame == -1){
		_currFrame = _maxFrames - 1;
	}

	const Frames& frames = gRsrcMgr->getImageFrame(_drawParams.rsrcId);
	_drawParams.frameRect = frames[_currFrame];

}

int32_t Image::getFrame() const{
	return _currFrame;
}

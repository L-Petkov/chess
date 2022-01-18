//Corresponding header
#include "manager_utils/drawing/Fbo.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "manager_utils/managers/RsrcMgr.h"
#include "manager_utils/managers/DrawMgr.h"



FBO::~FBO(){
	if(_isCreated && !_isDestroyed){
		destroy();
	}
}

void FBO::create(int32_t width, int32_t height, const Point &pos,
				   const Color &clearColor){

	if(_isCreated){
		std::cerr << "Error, FBO with fboId: " << _drawParams.fboId
				  << " was already created. Will not create twice."
				  << std::endl;
		return;
	}

	_drawParams.width = width;
	_drawParams.height = height;


	_drawParams.frameRect.x = 0;
	_drawParams.frameRect.y = 0;
	_drawParams.frameRect.w = _drawParams.width;
	_drawParams.frameRect.h = _drawParams.height;

	gRsrcMgr->createFbo(width, height, _drawParams.fboId);

	_drawParams.pos = pos;
	_drawParams.widgetType = WidgetType::FBO;
	_clearColor = clearColor;

	_isCreated =  true;
	_isDestroyed = false;

}

void FBO::destroy(){
	if(!_isCreated){
		std::cerr << "Error, image  was not created in first place." << std::endl;
		return;
	}
	if(_isDestroyed){
		std::cerr << "Error, image  was already destroyed." << std::endl;
		return;
	}
	//sanity check, because manager could already been destroyed
	if (nullptr != gRsrcMgr) {
		//unload text from graphical text vector
		gRsrcMgr->unloadText(_drawParams.textId);
	}

	_storedItems.clear();
	_clearColor = Colors::BLACK;
	_isLocked = true;

	_isCreated = false;
	_isDestroyed = true;


	Widget::reset();

}

void FBO::unlock(){
	if(!_isLocked){
		std::cerr << "Error, in FBO::unlock(), FBO was already not locked in the first place"
				  << std::endl;
		return;
	}
	_isLocked = false;
	if(EXIT_SUCCESS != gDrawMgr->unlockRenderer()){
		std::cerr << "Error, in FBO::unlock(), gDrawMgr->unlockRenderer() failed"
				  << std::endl;
	}
	gDrawMgr->setRendererTarget(_drawParams.fboId);
}

void FBO::lock(){
	if(_isLocked){
		std::cerr << "Error, in FBO::lock(), FBO was already locked"
				  << std::endl;
		return;
	}
	_isLocked = true;
	if(EXIT_SUCCESS != gDrawMgr->lockRenderer()){
		std::cerr << "Error, in FBO::lock(), gDrawMgr->lockRenderer() failed"
				  << std::endl;
	}
	gDrawMgr->resetRendererTarget();
}

void FBO::reset(){
	gDrawMgr->clearCurrentRendererTarget(_clearColor);
	_storedItems.clear();
}

void FBO::addWidget(const Widget &widget){
	if(!widget.isCreated()){
		std::cerr<< "Error, trying to add non-created widget for FBO with id: "
				 << _drawParams.fboId
				 << std::endl;
	}
	_storedItems.push_back(widget.getDrawParams());
}

void FBO::update() const {
	for(const auto& drawParam : _storedItems){
		gDrawMgr->addDrawCmd(drawParam);
	}
}





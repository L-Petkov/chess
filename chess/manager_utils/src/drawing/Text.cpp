//Corresponding header
#include "manager_utils/drawing/Text.h"

//C system includes

//C++ system includes
#include <iostream>
//Third-party includes

//Own includes
#include "manager_utils/managers/RsrcMgr.h"

Text::~Text(){
	if(_isCreated && !_isDestroyed){
			Text::destroy();
	}

}

void Text::create(const std::string text,  int32_t fontId,
	                   const Color& color, const Point &pos){
	if(_isCreated){
		std::cerr << "Error, text with fontId: "
				<< fontId << " was already created. Will not create twice." << std::endl;
		return;
	}

	gRsrcMgr->createText(text, color, fontId, _drawParams.textId,
			_drawParams.width, _drawParams.height);

	_drawParams.frameRect.x = 0;
	_drawParams.frameRect.y = 0;
	_drawParams.frameRect.w = _drawParams.width;
	_drawParams.frameRect.h = _drawParams.height;

	_drawParams.pos = pos;
	_drawParams.widgetType = WidgetType::TEXT;

	 _textContent = text;
	 _color = color;
	 _fontId = fontId;


	_isCreated =  true;
	_isDestroyed = false;

}

void Text::destroy(){

	if (_isDestroyed) {
	    std::cerr
	        << "Warning, trying to destroy already destroyed text with textId: "
	        << _drawParams.textId << std::endl;
	    return;
	}
	if (!_isCreated) {
	    std::cerr << "Warning, trying to destroy a not-created text with textId: "
	              << _drawParams.textId << std::endl;
	    return;
	}


	//unload text from graphical text vector
	if (nullptr != gRsrcMgr) {	//sanity check, because manager could already been destroyed
		gRsrcMgr->unloadText(_drawParams.textId);
		return;
	}
	_isCreated = false;
	_isDestroyed = true;

	Widget::reset();
}

void Text::setText(const std::string text){
	if(text == _textContent){
		return;
	}
	_textContent  = text;
	gRsrcMgr->reloadText(text, _color, _fontId, _drawParams.textId,
		_drawParams.width, _drawParams.height);

	_drawParams.frameRect.w = _drawParams.width;
	_drawParams.frameRect.h = _drawParams.height;

}

void Text::setColor(const Color& color){
	if (_isDestroyed) {
	    std::cerr
	        << "Warning, trying to set color on already destroyed text with textId: "
	        << _drawParams.textId << std::endl;
	    return;
	  }
	if(color == _color){
		return;
	}
	_color = color;
	gRsrcMgr->reloadText(_textContent, color, _fontId, _drawParams.textId,
		_drawParams.width, _drawParams.height);
	_drawParams.frameRect.w = _drawParams.width;
	_drawParams.frameRect.h = _drawParams.height;

}

std::string Text::getTextContent() const{
	return _textContent;
}


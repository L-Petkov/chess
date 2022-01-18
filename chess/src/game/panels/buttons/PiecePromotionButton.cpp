//Corresponding header
#include "game/panels/buttons/PiecePromotionButton.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "sdl_utils/InputEvent.h"


int32_t PiecePromotionButton::init(const PiecePromotionButtonCfg &cfg){
	_cfg = cfg;
	_bgrImg.create(_cfg.buttonBgrRsrcId, _cfg.bgrPos);


	return EXIT_SUCCESS;
}

void PiecePromotionButton::draw() const{
	_bgrImg.draw();
	ButtonBase::draw();
}

void PiecePromotionButton::handleEvent(const InputEvent &e){
	if(TouchEvent::TOUCH_RELEASE == e.type){
		_cfg.onBtnClicked(_cfg.pieceType);
	}
}

void PiecePromotionButton::activate(int32_t activePlayerId){
	const auto rsrcId =
			(activePlayerId == Defines::WHITE_PLAYER_ID) ?
					_cfg.buttonWhitePieceRsrcId : _cfg.buttonBlackPieceRsrcId;
	const int32_t X_Y_DELTA = (_bgrImg.getWidth() - _cfg.width) / 2;
	const Point btnPos = Point(_bgrImg.getX() + X_Y_DELTA,
	                                           _bgrImg.getY() + X_Y_DELTA);

	if(isCreated()){//no need getter coz PiecePromotion derive from ButtonBase
		//wich derive from Image wich having _isCreated
		ButtonBase::destroy();
	}
	ButtonBase::create(rsrcId, btnPos);
	setFrame(static_cast<int32_t>(_cfg.pieceType));
}





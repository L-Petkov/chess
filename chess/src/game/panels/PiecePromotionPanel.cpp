//Corresponding header
#include "game/panels/PiecePromotionPanel.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/proxies/GameProxy.h"
#include "sdl_utils/InputEvent.h"


int32_t PiecePromotionPanel::init(const PiecePromotionPanelCfg& cfg,
								  GameProxy* gameProxy) {
	if(nullptr == gameProxy){
		std::cerr << "Error, nullptr provided for gameProxy IN PiecePromotionPanel::init()"
				<< std::endl;
		return EXIT_FAILURE;
	}
	_gameProxy = gameProxy;
	PiecePromotionButtonCfg btnCfg;

	btnCfg.onBtnClicked =[this](PieceType pieceType){ //functioncallback atach usinglaabda
		onButtonClicked(pieceType);
	};


	btnCfg.buttonBgrRsrcId =  cfg.buttonBgrRsrcId;
	btnCfg.buttonWhitePieceRsrcId = cfg.whitePiecesRsrcId;
	btnCfg.buttonBlackPieceRsrcId = cfg.blackPiecesRsrcId;
	btnCfg.bgrWidth = cfg.buttonBgrWidth;
	btnCfg.bgrHeight = cfg.buttonBgrHeight;
	btnCfg.width = cfg.buttonWidth;
	btnCfg.height = cfg.buttonHeight;


	constexpr std::array<PieceType, BUTTONS_COUNT> pieceTypes{
		PieceType::QUEEN, PieceType::ROOK, PieceType::BISHOP, PieceType::KNIGHT
	};
	//TODO return btnOffset to 50 when returning rom 450 to 900 boarda and all other related
	constexpr auto btnOffset = 25;//50;
	const auto startX = (cfg.gameBoardWidth -
			(BUTTONS_COUNT * (cfg.buttonWidth + btnOffset)))/2;
	btnCfg.bgrPos.y = (cfg.gameBoardHeight - cfg.buttonHeight)/2;


	for(int32_t i = 0; i < BUTTONS_COUNT; ++i){
		btnCfg.pieceType = pieceTypes[i];
		btnCfg.bgrPos.x = startX + (i * (cfg.buttonWidth + btnOffset));

		if(EXIT_SUCCESS != _promotionBtns[i].init(btnCfg)){
			std::cerr <<
			"Error, in PiecePromotionPanel::init(), _promotionBtns["
			<< i
			<<"].init() failed"
					<< std::endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

void PiecePromotionPanel::handleEvent(const InputEvent& e){

		for(auto& btn : _promotionBtns){
			if(btn.isInputUnlocked() && btn.containsEvent(e)){
				btn.handleEvent(e);
				break;
			}
		}


}

void PiecePromotionPanel::draw()const{
	if(!_isActive){
		return;
	}
	for(const auto& btn : _promotionBtns){
		btn.draw();
	}
}

void PiecePromotionPanel::activate(int32_t playerId){
	_isActive = true;
	for(auto& btn : _promotionBtns){
		btn.activate(playerId);
	}
}

bool PiecePromotionPanel::isActive() const{
	return _isActive;
}

void PiecePromotionPanel::onButtonClicked(PieceType pieceType){
	_isActive = false;
	_gameProxy->promotePiece(pieceType);
	_gameProxy->onGameTurnFinish();
}




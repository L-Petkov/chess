//Corresponding header
#include "game/pieces/types/ChessPiece.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/utils/BoardUtils.h"
#include "manager_utils/drawing/Fbo.h"
#include "sdl_utils/InputEvent.h"


int32_t ChessPiece::init(const ChessPieceCfg& cfg){
	if(cfg.pieceType == PieceType::UNKNOWN){
		std::cerr << "Error, invalid PieceType provided: "<< static_cast<int32_t>(cfg.pieceType)
				<<std::endl;

		return EXIT_FAILURE;
	}
	if(cfg.rsrcId == INVALID_RSRC_ID){
		std::cerr << "Error, invalid rsrcId provided"
				<<std::endl;

		return EXIT_FAILURE;
	}

	_boardPos = cfg.boardPos;
	_playerId = cfg.playerId;
	_pieceType = cfg.pieceType;

	_pieceImg.create(cfg.rsrcId, BoardUtils::getAbsPos(_boardPos));
	_pieceImg.setFrame(static_cast<int32_t>(_pieceType));

	return EXIT_SUCCESS;
}

void ChessPiece::drawOnFbo(FBO& fbo) const{
	fbo.addWidget(_pieceImg);
}

void ChessPiece::draw() const{
	_pieceImg.draw();
}

bool ChessPiece::containsEvent(const InputEvent &e) const{
	return _pieceImg.containsPoint(e.pos);
}

void ChessPiece::setWidgetFlipType(WidgetFlip flipType){
	_pieceImg.setFlipType(flipType);
}

void ChessPiece::setBoardPos(const BoardPos &boardPos){
	_boardPos = boardPos;
	_pieceImg.setPosition(BoardUtils::getAbsPos(_boardPos));
}

BoardPos ChessPiece::getBoardPos()const{
	return _boardPos;
}

int32_t ChessPiece::getPlayerId()const{
	return _playerId;
}

int32_t ChessPiece::getRsrcId()const{
	return _pieceImg.getRsrcId();
}

PieceType ChessPiece::getPieceType()const{
	return _pieceType;
}

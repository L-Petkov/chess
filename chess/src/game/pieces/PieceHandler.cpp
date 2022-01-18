//Corresponding header
#include "game/pieces/PieceHandler.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "sdl_utils/InputEvent.h"
#include "manager_utils/drawing/Fbo.h"
#include "game/proxies/GameBoardProxy.h"
#include "game/proxies/GameProxy.h"
#include "game/utils/BoardUtils.h"
#include "common/CommonDefines.h"


int32_t PieceHandler::init(GameBoardProxy* gameBoardProxy, GameProxy* gameProxy,
		 int32_t whitePiecesRsrcId, int32_t blackPiecesRsrcId){
	if(nullptr == gameBoardProxy){
		std::cerr << "Error, nullptr provided for gameBoardProxy" << std::endl;
		return EXIT_FAILURE;
	}
	_gameBoardProxy = gameBoardProxy;

	if(nullptr == gameProxy){
			std::cerr << "Error, nullptr provided for gameProxy in PieceHandler::init()" << std::endl;
			return EXIT_FAILURE;
	}
	_gameProxy = gameProxy;

	if (EXIT_SUCCESS!= PieceHandlerPopulator::populatePieceHandler(
					_gameProxy, whitePiecesRsrcId,
					blackPiecesRsrcId, _pieces)) {

		std::cerr << "Error, PieceHandlerPopulator::populatePieceHandler() failed" << std::endl;
		return EXIT_FAILURE;

	}


	return EXIT_SUCCESS;
}

void PieceHandler::drawOnFbo(FBO& fbo) const{
	for(const auto& playerPieces : _pieces){
		for(const auto& piece : playerPieces){
			piece->drawOnFbo(fbo);
		}
	}
}

void PieceHandler::draw() const{
	for(const auto& playerPieces : _pieces){
		for(const auto& piece : playerPieces){
			piece->draw();
		}
	}
}

void PieceHandler::handleEvent(const InputEvent& e){
	_isPieceGrabbed ? handlePieceGrabedEvent(e) : handlePieceUngrabedEvent(e);
}

void PieceHandler::setCurrPlayerId(int32_t curPLayerId){
	_currPlayerId = curPLayerId;
}
void PieceHandler::setWidgetFlipType(WidgetFlip flipType){
	for(auto& playerPieces : _pieces){
		for(auto& piece : playerPieces){
			piece->setWidgetFlipType(flipType);
		}
	}
}

void PieceHandler::promotePiece(PieceType pieceType){
	//TODO finish
	const auto boardPos = _pieces[_currPlayerId][_selectedPieceId]->getBoardPos();
	const auto piecePlayerId = _pieces[_currPlayerId][_selectedPieceId]->getPlayerId();
	const auto pieceRsrcId = _pieces[_currPlayerId][_selectedPieceId]->getRsrcId();

	_pieces[_currPlayerId][_selectedPieceId].reset();

	ChessPieceCfg pieceCfg;
	pieceCfg.boardPos = boardPos;
	pieceCfg.playerId = piecePlayerId;
	pieceCfg.rsrcId = pieceRsrcId;
	pieceCfg.pieceType = pieceType;



	_pieces[_currPlayerId][_selectedPieceId] =
			PieceHandlerPopulator::createPiece(pieceType, _gameProxy);

	_pieces[_currPlayerId][_selectedPieceId]->init(pieceCfg);

}

void PieceHandler::freePieces(){
	// work in progress
//	for(auto& curPlayerPieces :_pieces){
//		size_t size = curPlayerPieces.size();
//		for(size_t i = 0 ; i < size;++i){
//			curPlayerPieces[i]->~ChessPiece();
//
//			if (EXIT_SUCCESS!= PieceHandlerPopulator::populatePieceHandler(
//							_gameProxy,Defines::WHITE_PLAYER_ID,
//							Defines::BLACK_PLAYER_ID, _pieces)) {
//
//				std::cerr << "Error, PieceHandlerPopulator::populatePieceHandler() failed" << std::endl;
//				return ;
//
//			}
	//	}

//	//	curPlayerPieces.erase(curPlayerPieces.begin(), curPlayerPieces.end());
	//}
//	this->
//	this->init(_gameBoardProxy, _gameProxy, whitePiecesRsrcId, blackPiecesRsrcId)
}

void PieceHandler::setLastPosOfOpponentPiece(BoardPos& lastPosOfOpponent){
	_lastPosOfOpponent = lastPosOfOpponent;
}

BoardPos PieceHandler::getLastPosOfOpponentPiece()const{
	return _lastPosOfOpponent;
}

void PieceHandler::handlePieceGrabedEvent(const InputEvent& e){
	if(e.type != TouchEvent::TOUCH_RELEASE){
				return;
	}

	_isPieceGrabbed = false;

	if(!BoardUtils::isInsideBoard(e.pos)){
		_gameBoardProxy->onPieceUngrabbed();
		return;
	}

	const BoardPos boardPos = BoardUtils::getBoardPos(e.pos);
	_lastPosOfOpponent = boardPos;
	if(!_gameBoardProxy->isMoveAllowed(boardPos)){
		_gameBoardProxy->onPieceUngrabbed();
		return;
	}

	doMovePiece(boardPos);
}

void PieceHandler::handlePieceUngrabedEvent(const InputEvent& e){
  if(e.type != TouchEvent::TOUCH_RELEASE){
    return;
  }
  int32_t pieceId = 0;
  for(const auto &piece : _pieces[_currPlayerId]){
    if(piece->containsEvent(e)){
	  _selectedPieceId = pieceId;
	  _isPieceGrabbed = true;

	  const auto moveTile =
			  _pieces[_currPlayerId][_selectedPieceId]->getMoveTiles(_pieces);

	  _gameBoardProxy->onPieceGrabbed(piece->getBoardPos(),
			  moveTile);
	  return;
    }
    ++pieceId;
  }

}
void PieceHandler::doMovePiece(const BoardPos& boardPos) {
	_pieces[_currPlayerId][_selectedPieceId]->setBoardPos(boardPos);

	const auto opponentId = BoardUtils::getOpponentId(_currPlayerId);
	int32_t colissionIdx = -1;
	if(BoardUtils::doCollideWithPiece(boardPos, _pieces[opponentId], colissionIdx)){

		_pieces[opponentId].erase(_pieces[opponentId].begin() + colissionIdx);
	}
	_gameBoardProxy->onPieceUngrabbed();

	while (_gameProxy->isPiecePromPanelActive()){

		return;
	}
	_gameProxy->onGameTurnFinish();

}





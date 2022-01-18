//Corresponding header
#include "game/board/GameBoard.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/utils/BoardUtils.h"
#include "manager_utils/drawing/Fbo.h"

GameBoard::~GameBoard(){
	if(isActiveTimerId(_blinkTimerId)){
		stopTimer(_blinkTimerId);
	}
}
int32_t GameBoard::init(int32_t boardRsrcId, int32_t targetRsrcId,
					int32_t moveTilesRsrcId, int32_t blinkTimerId){
	_boardImg.create(boardRsrcId);
	_targetImg.create(targetRsrcId);
	_targetImg.hide();
	_blinkTimerId = blinkTimerId;
	if(EXIT_SUCCESS != _moveSelector.init(moveTilesRsrcId,
							_boardImg.getWidth(),_boardImg.getHeight())){
		std::cerr << "Error, _moveSelector.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _imgPosInverter.init(_boardImg.getWidth(),
			_boardImg.getHeight())){
		std::cerr << "_imgPosInverter.init() failed" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void GameBoard::drawGameBoardOnFbo(FBO& fbo) const{
	fbo.addWidget(_boardImg);
}

void GameBoard::drawGameBoardOnly() const{
	_boardImg.draw();
}

void GameBoard::draw() const{

	_targetImg.draw();
	_moveSelector.draw();
}
void GameBoard::setWidgetFlipType(WidgetFlip flipType){
	_imgPosInverter.setWidgetFlipType(flipType);
	_moveSelector.setWidgetFlipType(flipType);
}
void GameBoard::setOnlyBoardFlipType(WidgetFlip flipType){
	_boardImg.setFlipType(flipType);
}

void GameBoard::onPieceGrabbed(const BoardPos &boardPos, const std::vector<TileData> &moveTiles){

	_targetImg.setPosition(BoardUtils::getAbsPos(boardPos));
	_imgPosInverter.invertImgPos(_targetImg);
	_targetImg.show();

	_currMoveTiles = moveTiles;
	_moveSelector.markTiles(_currMoveTiles);
	_moveSelector.invertMoveTilesImgPos();

	startTimer(1000, _blinkTimerId, TimerType::PULSE);
}

void GameBoard::onPieceUngrabbed(){
	_moveSelector.unmarkTiles();
	_currMoveTiles.clear();
	if(isActiveTimerId(_blinkTimerId)){
		stopTimer(_blinkTimerId);
	}

	_targetImg.hide();
}

bool GameBoard::isMoveAllowed(const BoardPos &pos) const{
  for(const auto& moveTile : _currMoveTiles){
    if(moveTile.boardPos == pos){
	  if(moveTile.tileType == TileType::MOVE ||
		 moveTile.tileType == TileType::TAKE) {
	    return true;
	  }
	}
  }
  return false;
}

void GameBoard::onTimeout(int32_t timerId){
	if(_blinkTimerId == timerId){
		if(_targetImg.isVisible()){
			_targetImg.hide();
		}
		else{
			_targetImg.show();
		}
	}
	else{
	std::cerr << "Received unsupported timerId: " << timerId << std::endl;
	}
}

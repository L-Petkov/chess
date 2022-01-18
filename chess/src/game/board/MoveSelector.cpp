//Corresponding header
#include "game/board/MoveSelector.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/utils/BoardUtils.h"


int32_t MoveSelector::init(int32_t rsrcId, int32_t boardWidth,int32_t boardHeight) {
	for (auto &img : _tileImgs) {
		img.create(rsrcId);
	}
	if(EXIT_SUCCESS != _imgPosInverter.init(boardWidth, boardHeight)){
		std::cerr << "_imgPosInverter.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void MoveSelector::draw() const{
	for (size_t i = 0; i < _activeTiles; ++i) {
		_tileImgs[i].draw();
	}
}

void MoveSelector::markTiles(const std::vector<TileData> &markedTiles) {
	_activeTiles = markedTiles.size();
	for (size_t i = 0; i < _activeTiles; ++i) {
		_tileImgs[i].setPosition(BoardUtils::getAbsPos(markedTiles[i].boardPos));
		_tileImgs[i].setFrame(static_cast<int32_t>(markedTiles[i].tileType));
	}
}

void MoveSelector::unmarkTiles() {
	_activeTiles = 0;
}

void MoveSelector::setWidgetFlipType(WidgetFlip flipType){
	_imgPosInverter.setWidgetFlipType(flipType);
}

void MoveSelector::invertMoveTilesImgPos(){
	for(size_t i = 0; i < _activeTiles; ++i){
		_imgPosInverter.invertImgPos(_tileImgs[i]);

	}
}



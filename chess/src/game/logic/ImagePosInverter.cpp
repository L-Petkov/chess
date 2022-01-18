//Corresponding header
#include "game/logic/ImagePosInverter.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/board/GameBoard.h"
//#include "game/utils/BoardUtils.h" TODO removeif not needed


int32_t ImagePosInverter::init(int32_t boardWidth, int32_t boardHeight){
	 _boardWidth = boardWidth;
	 _boardHeight = boardHeight;

	return EXIT_SUCCESS;
}

void ImagePosInverter::setWidgetFlipType(WidgetFlip flipType){
	_flipType  = flipType;
}
void ImagePosInverter::invertVectorOfImgPos([[maybe_unused]]Image& img){
	//std::vector<Point> currMoveTilesPos;
	//	currMoveTilesPos.reserve(_currMoveTiles.size());
	//	Point moveTilePos;
	//	for(const auto& currMoveTile : _currMoveTiles){
	//		moveTilePos = BoardUtils::getAbsPos(currMoveTile.boardPos);
	//		currMoveTilesPos.push_back(moveTilePos);
	//	}
}

void ImagePosInverter::invertImgPos(Image& img){

	int32_t x = 0;
	int32_t y = 0;

	switch(_flipType){

	case WidgetFlip::NONE:
		break;

	case WidgetFlip::HORIZONTAL:
		x = img.getX();
		y = (_boardHeight - img.getY()) - img.getHeight();
		img.setPosition(x,y);

		break;

	case WidgetFlip::VERTICAL:
		x = (_boardWidth - img.getX()) - img.getWidth();
		y = img.getY();
		img.setPosition(x,y);
		break;

	case WidgetFlip::HORIZONTAL_AND_VERTICAL:
		x = (_boardWidth-img.getX()) - img.getWidth();
		y = (_boardHeight-img.getY()) - img.getHeight();

		img.setPosition(x,y);
		break;
	default :
		std::cerr <<
		"Error, in InputInverter::invertImgPosInGameBoard() received unknown GameBoard"
		<< std::endl;
		break;

	}
}

void setCurrMoveTilesByX(){

}

void setCurrMoveTilesByY(){

}

void setCurrMoveTilesByXandY(){

}


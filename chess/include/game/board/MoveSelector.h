#ifndef INCLUDE_GAME_BOARD_MOVESELECTOR_H_
#define INCLUDE_GAME_BOARD_MOVESELECTOR_H_

//C system includes

//C++ system includes
#include <cstdint>
#include <array>

//Third-party includes

//Own includes
#include "game/defines/ChessStructs.h"
#include "manager_utils/drawing/Image.h"
#include "game/logic/ImagePosInverter.h"

//Forward Declarations

class MoveSelector {
public:
	int32_t init(int32_t rsrcId, int32_t boardWidth,int32_t boardHeight);
	void draw()const;
	void markTiles(const std::vector<TileData> &markedTiles);
	void unmarkTiles();
	void setWidgetFlipType(WidgetFlip flipType);
	void invertMoveTilesImgPos();//
private:
	enum InternalDefines {
    MAX_ACTIVE_TILES = 28
	};

  std::array<Image, MAX_ACTIVE_TILES> _tileImgs;
  size_t _activeTiles { 0 };
  ImagePosInverter _imgPosInverter;
};
#endif /* INCLUDE_GAME_BOARD_MOVESELECTOR_H_ */

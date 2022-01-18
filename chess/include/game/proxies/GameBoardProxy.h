#ifndef INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_
#define INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "game/defines/ChessStructs.h"

//Forward Declarations
struct BoardPos;

class GameBoardProxy{
public:
	virtual ~GameBoardProxy() = default;
	virtual void onPieceGrabbed(const BoardPos &boardPos, const std::vector<TileData> &moveTiles) = 0;
	virtual void onPieceUngrabbed() = 0;
	virtual bool isMoveAllowed(const BoardPos &pos) const = 0;

};




#endif /* INCLUDE_GAME_PROXIES_GAMEBOARDPROXY_H_ */

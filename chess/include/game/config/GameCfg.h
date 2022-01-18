#ifndef GAME_CONFIG_GAMECFG_H_
#define GAME_CONFIG_GAMECFG_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declarations
#include "game/panels/config/PiecePromotionPanelCfg.h"


struct GameCfg {
	int32_t  inGameBtnExitRsrcId;
	PiecePromotionPanelCfg piecePromotionPanelCfg;

	int32_t bgrImg;
	int32_t chessBoardRsrcId;
	int32_t whitePiecesRsrcId;
	int32_t blackPiecesRsrcId;
	int32_t targetRsrcId;
	int32_t moveTilesRsrcId;


	int32_t pLayerTurnTimeCapRsrcsId;

	int32_t blinkTargetTimerId;

	int32_t gameFboRotTimerId;


};



#endif /* GAME_CONFIG_GAMECFG_H_ */

//Corresponding header
#include "engine/EngineConfigLoader.h"

//C system includes

//C++ system includes

//Third-party includes

//Own includes
#include "common/CommonDefines.h"

//constants
namespace{
	constexpr auto WINDOW_WIDHT = 450 + 89; //+89 is to have place for exitbtn///900;    //752
	constexpr auto WINDOW_HEIGHT = 450;//900;	//600
	constexpr auto WINDOW_NAME = "Chess";

	constexpr auto BGR_MAIN_MENU_WIDTH = 752;
	constexpr auto BGR_MAIN_MENU_HEIGHT = 600;

	constexpr auto BUTTON_FRAMES = 1;
	constexpr auto MAIN_MENU_BUTTON_WIDTH = 188;
	constexpr auto MAIN_MENU_BUTTON_HEIGHT = 69;

	constexpr auto IN_GAME_EXIT_BTN_WIDTH =  89;
	constexpr auto IN_GAME_EXIT_BTN_HEIGHT = 69;

	constexpr auto CHESS_PIECES_FRAMES = 6;
	constexpr auto CHESS_PIECES_WIDTH_HEIGHT = 48;//96;

	constexpr auto CHESS_BOARD_WIDTH_HEIGHT = 450;//900;

	constexpr auto TARGET_IMG_WIDTH_HEIGHT = 49;//98;

	constexpr auto MOVE_TILES_FRAMES = 3;
	constexpr auto MOVE_TILES_IMG_WIDTH_HEIGHT = 49;//98;

	constexpr auto PROMOTION_BTN_FRAMES = 2;
	constexpr auto PROMOTION_BTN_WIDTH_HEIGHT = 52;//104;

	constexpr auto ANGELINE_VINTAGE_80_FONT_SIZE = 80;//40;

	constexpr auto MAX_FRAMERATE = 60;
	// TODO CHANGE THE ONES WHO HAVE COMENTS BEHIND THEM WITH THE COMMENT BEFORE SUBMITING
	// AND CHANGE RESOURCE PICS WITH THE BIGGER ONE AND CHANGE IN BOARDUTILS.CPP
}

static std::string getFilePath(const std::string& relativePath){

#ifdef RELEASE_BUILD
	return relativePath;
#else
	return "../" + relativePath;
#endif

}
static void populateTextContainerConfig(TextContainerCfg& cfg){
	FontCfg fontCfg;

	fontCfg.location = getFilePath("resources/fonts/AngelineVintage.ttf");
	fontCfg.fontSize = ANGELINE_VINTAGE_80_FONT_SIZE;

	cfg.fontConfigs.emplace(FontId::ANGELINE_VINTAGE_40, fontCfg);

}
static void populateImageContainerConfig(ImageContainerCfg& cfg){
	ImageCfg imageCfg;
	//MAINMENU START
		//BGR MAIN MENU  START
	imageCfg.location = getFilePath("resources/pictures/bgrImg.jpg");
	imageCfg.frames.emplace_back(
			0, 							//x
			0,							//y
			WINDOW_WIDHT,     //width
			WINDOW_HEIGHT);	//height
	cfg.imageConfigs.emplace(TextureId::BGR_IMG, imageCfg);
	imageCfg.frames.clear();
	//BGR MAIN MENU END
	//START BUTTON AND EXIT BUTTON START
	constexpr auto buttonsCount = 2;
	const std::string buttonPaths[buttonsCount] = {
		"resources/pictures/buttons/button_start-game.png",
		"resources/pictures/buttons/button_exit-game.png"
	};
	constexpr int32_t buttonRsrcIds[buttonsCount] = {
		TextureId::START_GAME_BTN_MAIN_MENU,
		TextureId::STOP_GAME_BTN_MAIN_MENU
	};
	for(int32_t i = 0; i < buttonsCount; ++i){
		imageCfg.location = getFilePath(buttonPaths[i]);

		for(auto frameId = 0; frameId < BUTTON_FRAMES; ++frameId){
			imageCfg.frames.emplace_back(
					frameId * MAIN_MENU_BUTTON_WIDTH, //x
					0,						    //y
					MAIN_MENU_BUTTON_WIDTH,     //width
					MAIN_MENU_BUTTON_HEIGHT);   //height
		}
		cfg.imageConfigs.emplace(buttonRsrcIds[i], imageCfg);
		imageCfg.frames.clear();

	}
		//START BUTTON AND EXIT BUTTON END

	//MAINMENU END
	//IN_GAME_EXIT_BTN START
	imageCfg.location = getFilePath("resources/pictures/buttons/in_game_button_exit.png");
		imageCfg.frames.emplace_back(
				0, 							//x
				0,							//y
				IN_GAME_EXIT_BTN_WIDTH,     //width
				IN_GAME_EXIT_BTN_HEIGHT);	//height
		cfg.imageConfigs.emplace(TextureId::IN_GAME_BTN_EXIT, imageCfg);
		imageCfg.frames.clear();
	// IN GAME EXIT BTN END
	// PIECES START
	constexpr auto typeOfPiecesCount = 2;
	const std::string piecesPaths[typeOfPiecesCount] = {
		"resources/pictures/whitePieces.png",
		"resources/pictures/blackPieces.png"
	};
	constexpr int32_t piecesRsrcIds[typeOfPiecesCount] = {
		TextureId::WHITE_PIECES,
		TextureId::BLACK_PIECES
	};
	for(int32_t i = 0; i < typeOfPiecesCount; ++i){
		imageCfg.location = getFilePath(piecesPaths[i]);

		for(auto frameId = 0; frameId < CHESS_PIECES_FRAMES; ++frameId){
			imageCfg.frames.emplace_back(
					frameId * CHESS_PIECES_WIDTH_HEIGHT, //x
					0,						    //y
					CHESS_PIECES_WIDTH_HEIGHT,     //width
					CHESS_PIECES_WIDTH_HEIGHT);   //height
		}
		cfg.imageConfigs.emplace(piecesRsrcIds[i], imageCfg);
		imageCfg.frames.clear();
	}
	//PIECES END

	//CHESS_BOARD START
	imageCfg.location = getFilePath("resources/pictures/chessBoard.jpg");
	imageCfg.frames.emplace_back(
			0, 							//x
			0,							//y
			CHESS_BOARD_WIDTH_HEIGHT,     //width
			CHESS_BOARD_WIDTH_HEIGHT);	//height
	cfg.imageConfigs.emplace(TextureId::CHESS_BOARD, imageCfg);
	imageCfg.frames.clear();
	//CHESS_BOARD END

	//TARGET START
	imageCfg.location = getFilePath("resources/pictures/target.png");
		imageCfg.frames.emplace_back(
				0, 							//x
				0,							//y
				TARGET_IMG_WIDTH_HEIGHT,     //width
				TARGET_IMG_WIDTH_HEIGHT);	//height
		cfg.imageConfigs.emplace(TextureId::TARGET, imageCfg);
		imageCfg.frames.clear();
	//TARGET END

	//MOVE_TILES START
	imageCfg.location = getFilePath("resources/pictures/moveTiles.png");

	for(auto frameId = 0; frameId < MOVE_TILES_FRAMES; ++frameId){
		imageCfg.frames.emplace_back(
				frameId * MOVE_TILES_IMG_WIDTH_HEIGHT, //x
				0,						    //y
				MOVE_TILES_IMG_WIDTH_HEIGHT,     //width
				MOVE_TILES_IMG_WIDTH_HEIGHT);   //height
	}
	cfg.imageConfigs.emplace(TextureId::MOVE_TILES, imageCfg);
	imageCfg.frames.clear();
	//MOVE_TILES END

	//PROMOTION BTN START
	imageCfg.location = getFilePath("resources/pictures/piecePromoteButtonBgr.png");

	for(auto frameId = 0; frameId < PROMOTION_BTN_FRAMES; ++frameId){
		imageCfg.frames.emplace_back(
				frameId * PROMOTION_BTN_WIDTH_HEIGHT, //x
				0,						    //y
				PROMOTION_BTN_WIDTH_HEIGHT,     //width
				PROMOTION_BTN_WIDTH_HEIGHT);   //height
	}
	cfg.imageConfigs.emplace(TextureId::PROMOTION_BUTTON, imageCfg);
	imageCfg.frames.clear();
	//PROMOTION BTN END
}


static void populateMonitorConfig(MonitorWindowCfg& cfg){
	cfg.windowName = WINDOW_NAME;
	cfg.windowWidth = WINDOW_WIDHT;
	cfg.windowHeight = WINDOW_HEIGHT;
	cfg.windowFlags = WINDOW_SHOWN;
}
static void populateRsrcMgrConfig(RsrcMgrCfg& cfg){
	populateImageContainerConfig(cfg.imageContainerCfg);
	populateTextContainerConfig(cfg.textContainerCfg);

}
static void populateDrawMgrConfig(DrawMgrCfg& cfg){
	populateMonitorConfig(cfg.windowCfg);
	cfg.maxFrameRate = MAX_FRAMERATE;
}
static void populateManagerHandlerConfig(ManagerHandlerCfg& cfg){
	populateDrawMgrConfig(cfg.drawMgrCfg);
	populateRsrcMgrConfig(cfg.rsrcMgrCfg);

}
static void populateGameConfig(GameCfg& cfg){
	cfg.bgrImg = TextureId::BGR_IMG;
	cfg.chessBoardRsrcId = TextureId::CHESS_BOARD;
	cfg.whitePiecesRsrcId = TextureId::WHITE_PIECES;
	cfg.blackPiecesRsrcId = TextureId::BLACK_PIECES;
	cfg.targetRsrcId = TextureId::TARGET;
	cfg.moveTilesRsrcId = TextureId::MOVE_TILES;


	cfg.blinkTargetTimerId = TimerId::BLINK_TARGET_TIMER_ID;
	cfg.gameFboRotTimerId = TimerId::GAME_FBO_ROT_TIMER_ID;

	cfg.pLayerTurnTimeCapRsrcsId = TimerId::PLAYER_TURN_TIME_CAP;

	auto& panelCfg = cfg.piecePromotionPanelCfg;
	panelCfg.whitePiecesRsrcId = TextureId::WHITE_PIECES;
	panelCfg.blackPiecesRsrcId = TextureId::BLACK_PIECES;
	panelCfg.buttonBgrRsrcId = TextureId::PROMOTION_BUTTON;
	panelCfg.gameBoardWidth = CHESS_BOARD_WIDTH_HEIGHT;
	panelCfg.gameBoardHeight = CHESS_BOARD_WIDTH_HEIGHT;
	panelCfg.buttonBgrWidth = PROMOTION_BTN_WIDTH_HEIGHT;
	panelCfg.buttonBgrHeight = PROMOTION_BTN_WIDTH_HEIGHT;
	panelCfg.buttonWidth = CHESS_PIECES_WIDTH_HEIGHT; // simulation of button width
	panelCfg.buttonHeight = CHESS_PIECES_WIDTH_HEIGHT;// simulation of button height

	cfg.inGameBtnExitRsrcId = TextureId::IN_GAME_BTN_EXIT;
}

static void populateMainMenuConfig(MainMenuCfg& cfg){
	cfg.bgrMainMenuRsrcId = TextureId::BGR_IMG;
	cfg.startGameBtnRsrcId = TextureId::START_GAME_BTN_MAIN_MENU;
	cfg.stopGameBtnRsrcId = TextureId::STOP_GAME_BTN_MAIN_MENU;
}

EngineConfig EngineConfigLoader::loadConfig(){

	EngineConfig cfg;

	populateManagerHandlerConfig(cfg.managerHandlerCfg);
	populateMainMenuConfig(cfg.mainMenuCfg);
	populateGameConfig(cfg.gameCfg);
	cfg.debugConsoleFontId = FontId::ANGELINE_VINTAGE_40;
	return cfg;
}

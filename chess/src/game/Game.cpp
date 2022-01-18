//Corresponding header
#include "game/Game.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/defines/ChessDefines.h"
#include "sdl_utils/InputEvent.h"
#include "common/CommonDefines.h"

//Forward Declarations
class MainMenuProxy;

namespace{
	constexpr auto MAX_SEC_PER_TURN = 60;
}


Game::~Game(){
	if(isActiveTimerId(_playerTurnTimerCapRsrcsId)){
		stopTimer(_playerTurnTimerCapRsrcsId);
	}
}

int32_t Game::init(const GameCfg &cfg, MainMenuProxy* cfgMainMenu) {

	_bgr.create(cfg.bgrImg);

	if(EXIT_SUCCESS != _gameBoard.init(cfg.chessBoardRsrcId,cfg.targetRsrcId,
			cfg.moveTilesRsrcId,cfg.blinkTargetTimerId)){
		std::cerr << "_gameBoard.init() failed" << std::endl;
		return EXIT_FAILURE;
	}
	if(EXIT_SUCCESS != _pieceHandler.init(static_cast<GameBoardProxy*>(&_gameBoard),
			static_cast<GameProxy*>(this),
			cfg.whitePiecesRsrcId, cfg.blackPiecesRsrcId)){
		std::cerr << "_pieceHandler.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _piecePromotionPanel.init(cfg.piecePromotionPanelCfg, this)){
		std::cerr << "_piecePromotionPanel.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	//FBO related init START
	_gameFbo.create(cfg.piecePromotionPanelCfg.gameBoardWidth,
			cfg.piecePromotionPanelCfg.gameBoardHeight, Point::ZERO, Colors::FULL_TRANSPARENT);
	_gameFbo.activateAlphaModulation();
	regenerateGameFbo();

	//FBO related init END


	if(EXIT_SUCCESS != _gameBoardAnimator.init(this, &_gameFbo, cfg.gameFboRotTimerId)){
		std::cerr << "_gameBoardAnimator.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _inputInverter.init(cfg.piecePromotionPanelCfg.gameBoardWidth,
			cfg.piecePromotionPanelCfg.gameBoardHeight)){
		std::cerr << "_inputInverter.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _exitBtn.init(cfgMainMenu,cfg.inGameBtnExitRsrcId)){
		std::cerr << "_inputInverter.init() failed" << std::endl;
		return EXIT_FAILURE;
	}
	_exitBtn.create(cfg.inGameBtnExitRsrcId, Point(450,0));

	_playerTurnTimerCapRsrcsId = cfg.pLayerTurnTimeCapRsrcsId;

	_timeLeft.create(std::to_string(_timeLeftPerTurn), FontId::ANGELINE_VINTAGE_40, Colors::BLACK, Point(450,100));

	startTimer(1000, _playerTurnTimerCapRsrcsId, TimerType::PULSE);
	return EXIT_SUCCESS;
}
void Game::deinit() {

	//this->_pieceHandler.~PieceHandler();

}

void Game::draw() const{

	_bgr.draw();
	_gameFbo.draw();
	_gameBoard.draw();
	_exitBtn.draw();
	_timeLeft.draw();
	_piecePromotionPanel.draw();
}
void Game::handleEvent(InputEvent &e) {
	if(e.type == TouchEvent::TOUCH_PRESS&& _exitBtn.containsEvent(e)){

//TODO finishi now work like pause we need to reset pieceHandler
		_exitBtn.handleEvent(e);
		return;
	}
	if(	_piecePromotionPanel.isActive()){
		_piecePromotionPanel.handleEvent(e);
		return;
	}
	_inputInverter.invertEvent(e);

	_pieceHandler.handleEvent(e);

}
void Game::reset([[maybe_unused]]GameCfg* gameCfg, [[maybe_unused]]GameProxy* gameProxy){
	//WorkInProgress
	//this->deinit();
	//this->_pieceHandler.freePieces();
//	PieceHandlerPopulator::populatePieceHandler(gameProxy,
//												gameCfg->whitePiecesRsrcId,
//												gameCfg->blackPiecesRsrcId,
//												);
//	this->_pieceHandler.init(&_gameBoard, this, gameCfg->whitePiecesRsrcId, gameCfg->blackPiecesRsrcId);
}

GameBoardProxy* Game::getGameBoardPtr(){
	return &_gameBoard;
}
int32_t Game::getPlayerTurnTimerCapRsrcId () const{
	return _playerTurnTimerCapRsrcsId;
}

void Game::setLastPosOfOpponentPiece(BoardPos& lastPosOfOpponent){
	_pieceHandler.setLastPosOfOpponentPiece(lastPosOfOpponent);
}

BoardPos Game::getLastPosOfOpponentPiece()const{
	return _pieceHandler.getLastPosOfOpponentPiece();
}


bool Game::isPiecePromPanelActive() const{
	return _piecePromotionPanel.isActive();
}

void Game::onGameTurnFinish() {
	_gameBoardAnimator.startAnim(_gameLogic.getActivePlayerId());

}

void Game::onPawnPromotion(	 ){
	_piecePromotionPanel.activate(_gameLogic.getActivePlayerId());
}

void Game::promotePiece(PieceType pieceType){
	_pieceHandler.promotePiece(pieceType);
}

void Game::onBoardAnimFinished(){

	_gameLogic.finishTurn();
	_pieceHandler.setCurrPlayerId(_gameLogic.getActivePlayerId());
	_timeLeftPerTurn = MAX_SEC_PER_TURN;
	_timeLeft.setText(std::to_string(_timeLeftPerTurn));

}

void Game::setWidgetFlipType(WidgetFlip flipType){

	_pieceHandler.setWidgetFlipType(flipType);
	_inputInverter.setBoardFlipType(flipType);
	_gameBoard.setWidgetFlipType(flipType);
	regenerateGameFbo();
}

void Game::regenerateGameFbo() {
	_gameFbo.unlock();
	_gameFbo.reset();


	if(_gameBoardAnimator.isActive()){
		_gameBoard.drawGameBoardOnFbo(_gameFbo);
	}
	else {
		_gameBoard.drawGameBoardOnly();
	}

	_pieceHandler.drawOnFbo(_gameFbo);



	_gameFbo.update();
	_gameFbo.lock();
}


void Game::onTimeout(int32_t timerId){
	if(_playerTurnTimerCapRsrcsId == timerId){
		--_timeLeftPerTurn;
		_timeLeft.setText(std::to_string(_timeLeftPerTurn));
		if(_timeLeftPerTurn <= 0){
			_timeLeftPerTurn = MAX_SEC_PER_TURN;
			_timeLeft.setText(std::to_string(_timeLeftPerTurn));
			onGameTurnFinish();
		}
	}
	else{
		std::cerr << "Received unsupported timerId: " << timerId << std::endl;
	}
}








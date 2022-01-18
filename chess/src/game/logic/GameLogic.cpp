//Corresponding header
#include "game/logic/GameLogic.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/defines/ChessDefines.h"

GameLogic::GameLogic() : _activePlayerId(Defines::WHITE_PLAYER_ID){

}

int32_t GameLogic::getActivePlayerId() const{
	return _activePlayerId;
}

void GameLogic::finishTurn(){
	if(Defines::WHITE_PLAYER_ID == _activePlayerId){
		_activePlayerId = Defines::BLACK_PLAYER_ID;
		return;
	}
	if(Defines::BLACK_PLAYER_ID == _activePlayerId){
		_activePlayerId = Defines::WHITE_PLAYER_ID;
		return;
	}

}


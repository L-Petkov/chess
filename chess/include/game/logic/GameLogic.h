#ifndef INCLUDE_GAME_LOGIC_GAMELOGIC_H_
#define INCLUDE_GAME_LOGIC_GAMELOGIC_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declarations

class GameLogic {
public:
	GameLogic();
	int32_t getActivePlayerId() const;
	void finishTurn();

private:

	int32_t _activePlayerId = 0;;
};


#endif /* INCLUDE_GAME_LOGIC_GAMELOGIC_H_ */

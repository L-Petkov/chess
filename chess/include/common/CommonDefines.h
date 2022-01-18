#ifndef COMMON_COMMONDEFINES_H_
#define COMMON_COMMONDEFINES_H_
//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declaration


namespace TextureId{

	enum ResourceId{
		START_GAME_BTN_MAIN_MENU,
		STOP_GAME_BTN_MAIN_MENU,
		IN_GAME_BTN_EXIT,
		BGR_IMG,
		CHESS_BOARD,
		TARGET,
		WHITE_PIECES,
		BLACK_PIECES,
		MOVE_TILES,
		PROMOTION_BUTTON
	};

}
// namespace TextureId End


namespace FontId{
enum FontIdKeys{
		ANGELINE_VINTAGE_40
	};
}//namespace FontId End

namespace TimerId{
	enum Keys{
		BLINK_TARGET_TIMER_ID,
		GAME_FBO_ROT_TIMER_ID,
		PLAYER_TURN_TIME_CAP
	};
}// namespace TimerId End



#endif /* COMMON_COMMONDEFINES_H_ */

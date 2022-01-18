#ifndef INCLUDE_GAME_PANELS_BUTTONS_PIECEPROMOTIONBUTTON_H_
#define INCLUDE_GAME_PANELS_BUTTONS_PIECEPROMOTIONBUTTON_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes
#include "manager_utils/input/ButtonBase.h"
#include "game/panels/config/PiecePromotionButtonCfg.h"

//Forward Declarations

class PiecePromotionButton : public ButtonBase{
public:

	int32_t init(const PiecePromotionButtonCfg &cfg);
	void draw() const final;
	void handleEvent(const InputEvent &e) final;
	void activate(int32_t activePlayerId);

private:

	Image _bgrImg;
	PiecePromotionButtonCfg _cfg;
};

#endif /* INCLUDE_GAME_PANELS_BUTTONS_PIECEPROMOTIONBUTTON_H_ */

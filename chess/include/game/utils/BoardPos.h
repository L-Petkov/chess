#ifndef INCLUDE_GAME_UTILS_BOARDPOS_H_
#define INCLUDE_GAME_UTILS_BOARDPOS_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declarations

struct BoardPos{
	BoardPos(int32_t inputRow, int32_t inputCol) : row(inputRow), col(inputCol){

	}
	BoardPos() = default;

	bool operator==(const struct BoardPos&  other) const {
		return this->row == other.row && this->col == other.col;
	}

	int32_t row{0};
	int32_t col{0};
};



#endif /* INCLUDE_GAME_UTILS_BOARDPOS_H_ */

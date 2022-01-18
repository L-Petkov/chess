//Corresponding header
#include "game/pieces/types/Queen.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/utils/BoardUtils.h"
#include "game/proxies/GameProxy.h"

//
//Defines::UP_LEFT, Defines::UP_RIGHT,
//			Defines::DOWN_RIGHT, Defines::DOWN_LEFT
std::vector<MoveDirection> Queen::getBoardMoves() const {
	constexpr auto allowedDirs = 8;
	constexpr std::array<Defines::Direction, allowedDirs> queenDirs { Defines::UP, Defines::UP_RIGHT
		, Defines::RIGHT,Defines::DOWN_RIGHT, Defines::DOWN, Defines::DOWN_LEFT, Defines::LEFT, Defines::UP_LEFT };

	constexpr auto maxQueenMoves = 7;
	std::vector<MoveDirection> boardMoves(allowedDirs);

	BoardPos futurePos;
	for (int32_t dirIdx = 0; dirIdx < allowedDirs; ++dirIdx) {
		boardMoves[dirIdx].reserve(maxQueenMoves);
		futurePos = _boardPos;
		futurePos = BoardUtils::getAdjacentPos(queenDirs[dirIdx], futurePos);

		while (BoardUtils::isInsideBoard(futurePos)) {
			boardMoves[dirIdx].push_back(futurePos);
			futurePos = BoardUtils::getAdjacentPos(queenDirs[dirIdx], futurePos);
		}

	}

	return boardMoves;
}

std::vector<TileData> Queen::getMoveTiles(
		const std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT> &activePieces) const {

	const std::vector<MoveDirection> boardMoves = getBoardMoves();
	std::vector<TileData> moveTiles;
	moveTiles.reserve(boardMoves.size());

	const auto opponentId = BoardUtils::getOpponentId(_playerId);
	for (const auto &moveDir : boardMoves) {
		if (moveDir.empty()) {
			continue;
		}

		for (const auto &boardPos : moveDir) {
			const TileType tileType = BoardUtils::getTileType(boardPos,
					activePieces[_playerId], activePieces[opponentId]);
			TileData tileData;
			tileData.boardPos = boardPos;
			tileData.tileType = tileType;
			moveTiles.push_back(tileData);
			if (TileType::MOVE != tileType) {
				break;
			}
		}
	}

	return moveTiles;
}




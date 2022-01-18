//Corresponding header
#include "game/pieces/types/Knight.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/utils/BoardUtils.h"
#include "game/proxies/GameProxy.h"



std::vector<MoveDirection> Knight::getBoardMoves() const {
	constexpr auto allowedDirs = 8;
	constexpr std::array<Defines::Direction, allowedDirs> rookDirs {
		Defines::UP_LEFT_TURN, Defines::UP_RIGHT_TURN,
		Defines::RIGHT_LEFT_TURN,Defines::RIGHT_RIGHT_TURN,
		Defines::DOWN_LEFT_TURN, Defines::DOWN_RIGHT_TURN,
		Defines::LEFT_LEFT_TURN, Defines::LEFT_RIGHT_TURN };
	constexpr auto maxKnightMoves = 1;
	std::vector<MoveDirection> boardMoves(allowedDirs);

	BoardPos futurePos;
	for (int32_t dirIdx = 0; dirIdx < allowedDirs; ++dirIdx) {
		boardMoves[dirIdx].reserve(maxKnightMoves);
		futurePos = _boardPos;
		futurePos = BoardUtils::getAdjacentPos(rookDirs[dirIdx], futurePos);

		if (BoardUtils::isInsideBoard(futurePos)) {
			boardMoves[dirIdx].push_back(futurePos);
		}

	}

	return boardMoves;
}

std::vector<TileData> Knight::getMoveTiles(
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




//Corresponding header
#include "game/pieces/types/Rook.h"

//C system includes

//C++ system includes
#include <iostream>

//Third-party includes

//Own includes
#include "game/utils/BoardUtils.h"

std::vector<MoveDirection> Rook::getBoardMoves() const {
	constexpr auto allowedDirs = 4;
	constexpr std::array<Defines::Direction, allowedDirs> rookDirs { Defines::UP, Defines::RIGHT,
			Defines::DOWN, Defines::LEFT };

	constexpr auto maxRookMoves = 7;
	std::vector<MoveDirection> boardMoves(allowedDirs);

	BoardPos futurePos;
	for (int32_t dirIdx = 0; dirIdx < allowedDirs; ++dirIdx) {
		boardMoves[dirIdx].reserve(maxRookMoves);
		futurePos = _boardPos;
		futurePos = BoardUtils::getAdjacentPos(rookDirs[dirIdx], futurePos);

		while (BoardUtils::isInsideBoard(futurePos)) {
			boardMoves[dirIdx].push_back(futurePos);
			futurePos = BoardUtils::getAdjacentPos(rookDirs[dirIdx], futurePos);
		}

	}

	return boardMoves;
}

std::vector<TileData> Rook::getMoveTiles(
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

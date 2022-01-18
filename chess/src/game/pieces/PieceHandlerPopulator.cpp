//Corresponding header
#include "game/pieces/PieceHandlerPopulator.h"

//C system includes

//C++ system includes
#include <iostream>


//Third-party includes

//Own includes
#include "game/pieces/types/Pawn.h"
#include "game/pieces/types/Rook.h"
#include "game/pieces/types/Bishop.h"
#include "game/pieces/types/Knight.h"
#include "game/pieces/types/Queen.h"
#include "game/pieces/types/King.h"


namespace {
constexpr auto STARTING_PIECES_COUNT = 16;
constexpr auto PAWNS_COUNT = 8;


constexpr auto NON_PAWN_COUNT = PAWNS_COUNT;
constexpr PieceType NON_PAWN_TYPES[NON_PAWN_COUNT] = {
		PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN,
		PieceType::KING, PieceType::BISHOP, PieceType::KNIGHT,	PieceType::ROOK
};


int32_t populateWhitePieces(GameProxy* gameProxy,int32_t rsrcId,
		ChessPiece::PlayerPieces& whites){

	whites.reserve(STARTING_PIECES_COUNT);

	ChessPieceCfg pieceCfg;
	pieceCfg.boardPos.row = Defines::WHITE_PLAYER_START_PAWN_ROW;
	pieceCfg.playerId = Defines::WHITE_PLAYER_ID;
	pieceCfg.rsrcId = rsrcId;
	pieceCfg.pieceType = PieceType::PAWN;



	for(auto i = 0; i < PAWNS_COUNT; ++i){
		whites.push_back(PieceHandlerPopulator::createPiece(pieceCfg.pieceType,gameProxy));
		pieceCfg.boardPos.col = i;
		if(EXIT_SUCCESS != whites[i]->init(pieceCfg)){
			std::cerr << "for pawns whites[i].init() failed" << std::endl;
			return EXIT_FAILURE;
		}
	}
	pieceCfg.boardPos.row = Defines::WHITE_PLAYER_START_PAWN_ROW + 1;
	for(auto i = NON_PAWN_COUNT; i < STARTING_PIECES_COUNT; ++i){
		pieceCfg.boardPos.col = i - NON_PAWN_COUNT;
		pieceCfg.pieceType = NON_PAWN_TYPES[i-NON_PAWN_COUNT];

		whites.push_back(PieceHandlerPopulator::createPiece(pieceCfg.pieceType,gameProxy));

		if(EXIT_SUCCESS != whites[i]->init(pieceCfg)){
			std::cerr << "for NON pawns whites[i].init() failed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int32_t populateBlackPieces(GameProxy* gameProxy,int32_t rsrcId,
		ChessPiece::PlayerPieces& blacks){

	blacks.reserve(STARTING_PIECES_COUNT);

	ChessPieceCfg pieceCfg;
	pieceCfg.boardPos.row = Defines::BLACK_PLAYER_START_PAWN_ROW;
	pieceCfg.playerId = Defines::BLACK_PLAYER_ID;
	pieceCfg.rsrcId = rsrcId;
	pieceCfg.pieceType = PieceType::PAWN;



	for(auto i = 0; i < PAWNS_COUNT; ++i){
		blacks.push_back(PieceHandlerPopulator::createPiece(pieceCfg.pieceType,gameProxy));
		pieceCfg.boardPos.col = i;
		if(EXIT_SUCCESS != blacks[i]->init(pieceCfg)){
			std::cerr << "for pawns blacks[i].init() failed" << std::endl;
			return EXIT_FAILURE;
		}

	}
	pieceCfg.boardPos.row = Defines::BLACK_PLAYER_START_PAWN_ROW - 1;
	for(auto i = NON_PAWN_COUNT; i < STARTING_PIECES_COUNT; ++i){
		pieceCfg.boardPos.col = i - NON_PAWN_COUNT;
		pieceCfg.pieceType = NON_PAWN_TYPES[i-NON_PAWN_COUNT];

		blacks.push_back(PieceHandlerPopulator::createPiece(pieceCfg.pieceType,gameProxy));

		if(EXIT_SUCCESS != blacks[i]->init(pieceCfg)){
			std::cerr << "for NON pawns blacks[i].init() failed" << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

};

int32_t PieceHandlerPopulator::populatePieceHandler(
		GameProxy* gameProxy, int32_t whitePiecesRsrcId,
		int32_t blackPiecesRsrcId,
		std::array<ChessPiece::PlayerPieces, Defines::PLAYERS_COUNT>& _pieces){

	auto& whites = _pieces[Defines::WHITE_PLAYER_ID];
	auto& blacks = _pieces[Defines::BLACK_PLAYER_ID];

	if(EXIT_SUCCESS != populateWhitePieces(gameProxy, whitePiecesRsrcId, whites)){
		std::cerr << "Error, populateWhitePieces() failed" << std::endl;
		return EXIT_FAILURE;
	}
	if(EXIT_SUCCESS != populateBlackPieces(gameProxy, blackPiecesRsrcId, blacks)){
		std::cerr << "Error, populateWhitePieces() failed" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
std::unique_ptr<ChessPiece> PieceHandlerPopulator::createPiece(PieceType pieceType, GameProxy* gameProxy){
	switch(pieceType){
	case PieceType::PAWN:
		return std::make_unique<Pawn>(gameProxy);
		break;
	case PieceType::ROOK:
		return std::make_unique<Rook>();
		break;
	case PieceType::BISHOP:
		return std::make_unique<Bishop>();
		break;
	case PieceType::KNIGHT:
		return std::make_unique<Knight>();
		break;
	case PieceType::QUEEN:
		return std::make_unique<Queen>();
			break;
	case PieceType::KING:
		return std::make_unique<King>();
		break;
	default:
		std::cerr << "Error, received unknown PieceType: "
					<< static_cast<int32_t>(pieceType)
					<< std::endl;
		return nullptr;
		break;
	}
	return nullptr;
}





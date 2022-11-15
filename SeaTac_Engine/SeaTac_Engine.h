//
// Created by Jonathan Hall on 10/9/22.
//

#ifndef SEATAC_ENGINE_SEATAC_ENGINE_H
#define SEATAC_ENGINE_SEATAC_ENGINE_H

#include "ChessGame.h"

class SeaTac_Engine {
public:
    SeaTac_Engine(ChessGame chessGame)
    {
        isWhite = chessGame.moveNumber/2;
        chessGame = chessGame;
    }
    int isWhite;

    std::bitset<64> FindBestMove(GameState gameState, int depth);

    int CalculateScore();

    int PerformMoveForPiece(GameState::ChessPieces chessPiece);

    ChessGame chessGame;
};


#endif //SEATAC_ENGINE_SEATAC_ENGINE_H

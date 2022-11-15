//
// Created by Jonathan Hall on 10/20/22.
//

#include "SeaEngine.h"
#include <stdio.h>
#include <iostream>

int SeaEngine::CalculateScore(GameState gameState) {

    printf("calculating score");
    int whiteBalance = 0;
    int blackBalance = 0;
    float runningScore = 0;

    for(int piece = 0; piece < 6; piece++)
    {
        std::bitset<64> wPieceBB = gameState.whitePieces[(GameState::ChessPieces)piece];
        whiteBalance = wPieceBB.count()*GameState::pieceValue((GameState::ChessPieces)piece);
        std::bitset<64> bPieceBB = gameState.blackPieces[(GameState::ChessPieces)piece];
        blackBalance = bPieceBB.count()*GameState::pieceValue((GameState::ChessPieces)piece);
    }

    runningScore = whiteBalance - blackBalance;

    printf("calculated best score: %f", runningScore);

    return runningScore;
}

GameState SeaEngine::MakeMove(GameState gameState, std::bitset<64> moveBoard, GameState::ChessPieces piece, bool white) {
    GameState *newGameState = new GameState(gameState);

    std::bitset<64> *ourSide, *otherSide;
    std::map<GameState::ChessPieces, std::bitset<64>> *ourPieces, *otherPieces;
    if(white)
    {
        ourSide = &(newGameState->white.board);
        otherSide = &(newGameState->black.board);
        ourPieces = &(newGameState->whitePieces);
        otherPieces = &(newGameState->blackPieces);
    }else
    {
        otherSide = &(newGameState->white.board);
        ourSide = &(newGameState->black.board);
        otherPieces = &(newGameState->whitePieces);
        ourPieces = &(newGameState->blackPieces);
    }

    *ourSide ^= moveBoard;
    (*ourPieces)[piece] ^= moveBoard;
    //we have to nand
    std::bitset<64> bANDmB = (*otherSide) & moveBoard; //will be empty or just the square we're attacking
    std::bitset<64> not_bANDmB = ~bANDmB;
    *otherSide &= not_bANDmB;

    //and the black occupied pieces with individual pieces to get rid of whatever piece we took out.
    for(int bPiece = 0; bPiece < 6; bPiece++)
    {
        (*otherPieces)[(GameState::ChessPieces) bPiece] &= *otherSide;
    }

    newGameState->occSquares.board = (newGameState->black.board | newGameState->white.board);
    newGameState->openSquares.board = ~(newGameState->occSquares.board);

    return *newGameState;
}

float SeaEngine::CalcBestMove(GameState gameState, int depth, bool color) {

    // if depth = 0, we simply return score from current board state.
    if(depth==0)
    {
        return CalculateScore(gameState);
    }
    return 0;
}

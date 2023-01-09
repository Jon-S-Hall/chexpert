//
// Created by Jonathan Hall on 10/20/22.
//

#include "SeaEngine.h"
#include <stdio.h>
#include <iostream>

int SeaEngine::CalculateScore(const GameState* gameState) {

    int whiteBalance = 0;
    int blackBalance = 0;
    float runningScore = 0;

    for(int piece = 0; piece < 6; piece++)
    {
        std::bitset<64> wPieceBB = gameState->whitePieces.at((ChessPieces)piece);
        whiteBalance += wPieceBB.count()*GameState::pieceValue((ChessPieces)piece);
        std::bitset<64> bPieceBB = gameState->blackPieces.at((ChessPieces)piece);
        blackBalance += bPieceBB.count()*GameState::pieceValue((ChessPieces)piece);
    }

    runningScore = whiteBalance - blackBalance;

    return runningScore;
}


std::bitset<64> SeaEngine::CalculateBestMove(const GameState* gameState, int depth, Color color) {

    if(depth<=0)
    {
        //can't have a depth of 0 or below, else no calculation is done.
        return std::bitset<64>();
    }

    float bestScore = -1000;
    std::bitset<64> bestMove;
    std::bitset<64> *ourPieces;

    if(color == Color::White)
    {
        ourPieces =  new std::bitset<64>(gameState->white);
    }else
    {
        ourPieces  = new std::bitset<64>(gameState->black);
    }

    //iterate through pawns. this should be a copy since not a pointer
    while(!(ourPieces->none()))
    {
        int pp = SeaChessUtils::bitScanForward(*ourPieces);
        //perform move
        std::bitset<64> movingPiece, pieceMoves;

        movingPiece[pp] = 1;

        ChessPieces ourPieceType = gameState->GetPieceFromGameState(movingPiece, color);

        std::bitset moves = gameState->CalculateLegalMoves(movingPiece, ourPieceType, color);

        while(!moves.none())
        {
            int move = SeaChessUtils::bitScanForward(moves);

            std::bitset<64> moveBB;
            moveBB[move] = 1;
            moveBB |= movingPiece;

            const GameState newState = gameState->GenerateGameStateFromMove(moveBB, color);

            float score = -1*CalculateBestMove_internal(&newState, depth-1, SeaChessUtils::otherColor(color));

            if(score > bestScore) {
                bestScore = score;
                bestMove = moveBB;
                //now we have to set the best "GS" or best "move" here.
            }

            moves[move] = 0;
        }

        (*ourPieces)[pp] = 0;
    }
    printf("score %f calculated for move.\n", bestScore);
    return bestMove;
}

float SeaEngine::CalculateBestMove_internal(const GameState* gameState, int depth, Color color) {

    // if depth = 0, we simply return score from current board state. must flip score since it is the opposite
    // of what color is calling.
    if(depth<=0)
    {
        if(color == Color::Black)
        {
            return -1* CalculateScore(gameState);
        }
        return CalculateScore(gameState);
    }

    int bestScore = -1000;
    std::bitset<64> bestMove;

    std::bitset<64> *ourPieces;
    if(color == Color::White)
    {
        ourPieces =  new std::bitset<64>(gameState->white);
    }else
    {
        ourPieces  = new std::bitset<64>(gameState->black);
    }

    //iterate through pawns. this should be a copy since not a pointer
    while(!(ourPieces->none()))
    {
        int pp = SeaChessUtils::bitScanForward(*ourPieces);
        //perform move
        std::bitset<64> movingPiece, pieceMoves;
        movingPiece.reset();
        movingPiece[pp] = 1;

        ChessPieces ourPieceType = gameState->GetPieceFromGameState(movingPiece, color);

        std::bitset moves = gameState->CalculateLegalMoves(movingPiece, ourPieceType, color);

        while(!moves.none())
        {
            int move = SeaChessUtils::bitScanForward(moves);

            std::bitset<64> moveBB;
            moveBB[move] = 1;
            moveBB |= movingPiece;

            const GameState newState = gameState->GenerateGameStateFromMove(moveBB, color);

            float score = -1*CalculateBestMove_internal(&newState, depth-1, SeaChessUtils::otherColor(color));

            if(score > bestScore) {
                bestScore = score;
                bestMove = moveBB; //make sure this makes a copy. Unnecessary clean up
            }
            moves[move] = 0;
        }
        (*ourPieces)[pp] = 0;
    }

    return bestScore;
}

std::bitset<64> SeaEngine::MakeMove(const GameState* gameState) const {

    //Given Game state, generate all moves
    auto start = std::chrono::high_resolution_clock::now();
    std::bitset<64> bestMove =  CalculateBestMove(gameState, m_depth, m_color);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    printf("time taken to calculate move: %llu", duration);
    //Iterate through moves, find best move

    //return best move
    return bestMove;
}

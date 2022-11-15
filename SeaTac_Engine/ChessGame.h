//
// Created by Jonathan Hall on 10/9/22.
//

#ifndef SEATAC_ENGINE_CHESSGAME_H
#define SEATAC_ENGINE_CHESSGAME_H

#include "GameState.h"

class ChessGame {
    //default constructor to start a game from scratch. Will also have to support starting game from separate position.
public:
    char *board;
    int moveNumber; //odd is white move, even is black move
    int winner;
    GameState *gameState;


public:

    ChessGame()
    {
        board = "rnbqkbnrpppppppp00000000000000000000000000000000PPPPPPPPRNBQKBNR";
        moveNumber = 1;
        GameState newState(board);
        gameState = &newState;
    }

    //method for player/engine to interact with the game, and move the piece. returns the moveNumber.
    int MovePiece(int source, int dest);

    int waitForUserInput();

    void DisplayBoard();

};


#endif //SEATAC_ENGINE_CHESSGAME_H

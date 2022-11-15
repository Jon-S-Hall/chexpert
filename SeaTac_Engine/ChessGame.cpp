//
// Created by Jonathan Hall on 10/9/22.
//

#include "ChessGame.h"
#include <iostream>

int ChessGame::MovePiece(int source, int dest) {
    board[dest] = board[source];
    board[source] = '0';


    return 0;
}

void ChessGame::DisplayBoard() {
    printf("Move: %d\n\n", moveNumber);
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            printf("%c ", board[row*8+col]);
        }
        printf("\n");
    }

}


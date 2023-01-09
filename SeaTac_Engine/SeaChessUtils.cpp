//
// Created by Jonathan Hall on 12/21/22.
//
#include "SeaChessUtils.h"
#include <stdio.h>



char SeaChessUtils::ChessPieceClassToChar(ChessPieces chessPiece, Color color) {
    char pieceChar = 'x';
    switch (chessPiece) {
        case ChessPieces::Pawn:
            pieceChar = 'p';
            break;
        case ChessPieces::Rook:
            pieceChar = 'r';
            break;
        case ChessPieces::Knight:
            pieceChar = 'n';
            break;
        case ChessPieces::Bishop:
            pieceChar = 'b';
            break;
        case ChessPieces::Queen:
            pieceChar = 'q';
            break;
        case ChessPieces::King:
            pieceChar = 'k';
            break;
        default:
            pieceChar = 'x';
    }

    if(color == Color::White) {
        pieceChar -= 32;
    }
    return pieceChar;
}

void SeaChessUtils::PrintBitBoard(std::bitset<64> bitBoard) {
    printf("\n");
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            printf("%s ", bitBoard[row*8 + col] ? "1": ".");
        }
        printf("\n");
    }
    printf("\n");
}

std::bitset<64> SeaChessUtils::CharMove_To_BitSetMove(const char *char_move) {
    return std::bitset<64>();
}

int SeaChessUtils::GetRowFromPosition(std::bitset<64> position) {
    int row = 7;
    while((position << 8).any())
    {
        row--;
        position = position << 8;
    }
    return row;
}



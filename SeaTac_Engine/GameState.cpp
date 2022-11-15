//
// Created by Jonathan Hall on 10/10/22.
//

#include "GameState.h"

void GameState::initBitBoards(char *board) {
    {
        //initialize bitboards to 0. check if this is needed.
        for(int pos = 0; pos < 64; pos++)
        {
            char piece = board[pos];

            std::map<ChessPieces, std::bitset<64>> *pieces = (piece - 'a' > 0) ? &blackPieces : &whitePieces;

            switch(piece){
                case '0':
                    break;
                case 'K' :
                case 'k':
                    (*pieces)[ChessPieces::King].set(pos);
                    break;
                case 'Q':
                case 'q':
                    (*pieces)[ChessPieces::Queen].set(pos);
                    break;
                case 'R':
                case 'r':
                    (*pieces)[ChessPieces::Rook].set(pos);
                    break;
                case 'B':
                case 'b':
                    (*pieces)[ChessPieces::Bishop].set(pos);
                    break;
                case 'N':
                case 'n':
                    (*pieces)[ChessPieces::Knight].set(pos);
                    break;
                case 'P':
                case 'p':
                    (*pieces)[ChessPieces::Pawn].set(pos);
                    break;
                default:
                    printf("couldn't find a match for piece");
            }
        }
        occSquares.reset();
        white.reset();
        black.reset();
        //now initialize other boards
        for(int i = 0; i < 6; i++)
        {
            white.board |= whitePieces[(ChessPieces)i];
            black.board |= blackPieces[(ChessPieces)i];
            occSquares.board |= whitePieces[(ChessPieces)i];
            occSquares.board |= blackPieces[(ChessPieces)i];
            openSquares.board = ~occSquares.board;
        }
    }
}

void GameState::PrintBitBoard(std::bitset<64> bitBoard) {
        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++)
            {
                printf("%s ", bitBoard[row*8 + col] ? "1": "0");
            }
            printf("\n");
        }
        printf("\n");
}



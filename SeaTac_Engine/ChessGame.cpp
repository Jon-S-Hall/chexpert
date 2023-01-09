//
// Created by Jonathan Hall on 10/9/22.
//

#include "ChessGame.h"
#include "ChessPlayer.h"
#include <iostream>

void ChessGame::DisplayBoard() {
    printf("Board Move: %d\n\n", m_MoveNumber);
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            printf("%c ", m_Board[row*8+col]);
        }
        printf("\n");
    }
    printf("\n\n");
}

//updates the chessGame chars that we display above.
void ChessGame::UpdateBoard() {
    char* newBoard = new char[64];

    for(int square = 0; square < 64; square++)
    {
        std::bitset<64> occSquare;
        occSquare[square] = 1;

        if((occSquare & m_GameState.whitePieces[ChessPieces::Pawn]) != 0)
        {
            newBoard[square] = 'P';
        }else if((occSquare & m_GameState.whitePieces[ChessPieces::King]) != 0)
        {
            newBoard[square] = 'K';
        }else if((occSquare & m_GameState.whitePieces[ChessPieces::Knight]) != 0)
        {
            newBoard[square] = 'N';
        }else if((occSquare & m_GameState.whitePieces[ChessPieces::Queen]) != 0)
        {
            newBoard[square] = 'Q';
        }else if((occSquare & m_GameState.whitePieces[ChessPieces::Bishop]) != 0)
        {
            newBoard[square] = 'B';
        }else if((occSquare & m_GameState.whitePieces[ChessPieces::Rook]) != 0)
        {
            newBoard[square] = 'R';
        }else if((occSquare & m_GameState.blackPieces[ChessPieces::Pawn]) != 0)
        {
            newBoard[square] = 'p';
        }else if((occSquare & m_GameState.blackPieces[ChessPieces::King]) != 0)
        {
            newBoard[square] = 'k';
        }else if((occSquare & m_GameState.blackPieces[ChessPieces::Knight]) != 0)
        {
            newBoard[square] = 'n';
        }else if((occSquare & m_GameState.blackPieces[ChessPieces::Queen]) != 0)
        {
            newBoard[square] = 'q';
        }else if((occSquare & m_GameState.blackPieces[ChessPieces::Bishop]) != 0)
        {
            newBoard[square] = 'b';
        }else if((occSquare & m_GameState.blackPieces[ChessPieces::Rook]) != 0)
        {
            newBoard[square] = 'r';
        }else
        {
            newBoard[square] = '.';
        }
    }
    m_Board = newBoard;
}

Color ChessGame::StartGame() {

    while(!GameOver())
    {
        DisplayBoard();
        // If it is an odd move, white is playing. Otherwise, black is playing.
        const ChessPlayer* current_player = (m_MoveNumber % 2 == 0) ? m_PlayerBlack : m_PlayerWhite;
        const GameState* c_GS = new GameState(m_GameState);
        std::bitset<64> legal_move = current_player->MakeMove(c_GS);

        GameState newGameState = m_GameState.GenerateGameStateFromMove(legal_move, current_player->m_color);


        m_GameState = newGameState;
        m_MoveNumber++;

        UpdateBoard();
    }
    return Color::White;
}

void ChessGame::UpdateGameWithMove(std::bitset<64> move) {
    m_MoveNumber++;
}


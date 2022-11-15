//
// Created by Jonathan Hall on 10/10/22.
//

#ifndef SEATAC_ENGINE_GAMESTATE_H
#define SEATAC_ENGINE_GAMESTATE_H
#include <map>
#include "bitboard.h"
#include <string>

class GameState {
public:
    GameState(char board[64])
    {
        initBitBoards(board);
        PrintBitBoard((whitePieces[ChessPieces::Rook]));
    }

    static void PrintBitBoard(std::bitset<64> bitBoard);

    void initBitBoards(char board[64]);

    void CalcMoveWhiteBoards();

    void CalcMoveBlackBoards();


    enum class ChessPieces{
        Pawn,
        Rook,
        Bishop,
        Knight,
        Queen,
        King
    };

    static int pieceValue(GameState::ChessPieces piece)
    {
        switch (piece)
        {
            case GameState::ChessPieces::King:
                return 500;
            case GameState::ChessPieces::Queen:
                return 100;
            case GameState::ChessPieces::Rook:
                return 50;
            case GameState::ChessPieces::Bishop:
                return 30;
            case GameState::ChessPieces::Knight:
                return 30;
            case GameState::ChessPieces::Pawn:
                return 10;
            default:
                return 0;

        }

    }


    //bitboards to represent state of the game
    bitboard occSquares, openSquares, white, black;
    std::map<ChessPieces, std::bitset<64>> whitePieces;
    std::map<ChessPieces, std::bitset<64>> blackPieces;
};

#endif //SEATAC_ENGINE_GAMESTATE_H

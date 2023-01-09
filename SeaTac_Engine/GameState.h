//
// Created by Jonathan Hall on 10/10/22.
//

#ifndef SEATAC_ENGINE_GAMESTATE_H
#define SEATAC_ENGINE_GAMESTATE_H
#include <map>
#include <string>
#include "SeaChessUtils.h"

class GameState {
public:
    GameState(char board[64])
    {
        initBitBoards(board);
    }

    void initBitBoards(char board[64]);

    void CalcMoveWhiteBoards();

    void CalcMoveBlackBoards();



    static int pieceValue(ChessPieces piece)
    {
        switch (piece)
        {
            case ChessPieces::King:
                return 500;
            case ChessPieces::Queen:
                return 100;
            case ChessPieces::Rook:
                return 50;
            case ChessPieces::Bishop:
                return 30;
            case ChessPieces::Knight:
                return 30;
            case ChessPieces::Pawn:
                return 10;
            default:
                return 0;

        }
    }

    std::bitset<64> CalculateLegalMoves(std::bitset<64> pp, ChessPieces piece, Color color) const;

    std::bitset<64> CalculateLegalMoves_Pawn(std::bitset<64> pp, Color color) const;

    std::bitset<64> CalculateLegalMoves_King(std::bitset<64> pp, Color color) const;

    std::bitset<64> CalculateLegalMoves_Queen(std::bitset<64> pp, Color color) const;
    std::bitset<64> CalculateLegalMoves_Knight(std::bitset<64> pp, Color color) const;

    std::bitset<64> CalculateLegalMoves_Rook(std::bitset<64> pp, Color color) const;

    std::bitset<64> CalculateLegalMoves_Bishop(std::bitset<64> pp, Color color) const;

    GameState GenerateGameStateFromMove(std::bitset<64> legal_move, Color color) const;

    ChessPieces GetPieceFromGameState(std::bitset<64> pp, Color color) const;
public:
    //bitboards to represent state of the game
    std::bitset<64> occSquares, white, black;
    std::map<ChessPieces, std::bitset<64>> whitePieces;
    std::map<ChessPieces, std::bitset<64>> blackPieces;

    //functional bitsets;
    std::map<int, std::bitset<64>> columns;
    std::map<int, std::bitset<64>> rows;

    ChessPieces GetPieceFromGameState(std::bitset<64> pp, Color color);
};

#endif //SEATAC_ENGINE_GAMESTATE_H

//
// Created by Jonathan Hall on 12/21/22.
//

#ifndef SEATAC_ENGINE_SEACHESSUTILS_H
#define SEATAC_ENGINE_SEACHESSUTILS_H
#include <iostream>
#include <map>

enum class ChessPieces{
    Pawn,
    Rook,
    Bishop,
    Knight,
    Queen,
    King
};

enum class Color{
    White,
    Black
};


class SeaChessUtils {
public:
    //converts ChessPieces class enumeration to character.
    static char ChessPieceClassToChar(ChessPieces chessPiece, Color color);

    //prints bitboard to standard output window
    static void PrintBitBoard(std::bitset<64> bitBoard);

    //validates user input move.
    static std::bitset<64> CharMove_To_BitSetMove(const char* char_move);


    static std::bitset<64> SouthOne(std::bitset<64> position) {
        return position << 8;
    }

    static std::bitset<64> NorthOne(std::bitset<64> position) {
        return position >> 8;
    }

    static std::bitset<64> SouthTwo(std::bitset<64> position)
    {
        return position << 16;
    }
    static std::bitset<64> NorthTwo(const std::bitset<64> position)
    {
        return position >> 16;
    }
    /*
     * ..00X...
     * ..0X0...
     */
    //Need to make sure we don't end up on the left side of the board.
    static std::bitset<64> DiagNE_One(std::bitset<64> position) {
        return position >> 9;
    }

    static Color otherColor(Color color)
    {
        return ((color == Color::White) ? Color::Black : Color::White);
    }

    static std::bitset<64> DiagNW_One(std::bitset<64> position);
    static std::bitset<64> DiagSE_One(std::bitset<64> position);
    static std::bitset<64> DiagSW_One(std::bitset<64> position);

    static int bitScanForward(std::bitset<64> board)
    {
        assert(board != 0);
        for(int i = 0; i < 64; i++){
            if(board[i])
            {
                return i;
            }
        }
        return -1;
    }

    static int GetRowFromPosition(std::bitset<64> position);

    static int GetColumnFromPosition(std::bitset<64> position);
};


#endif //SEATAC_ENGINE_SEACHESSUTILS_H

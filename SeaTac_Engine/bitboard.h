//
// Created by Jonathan Hall on 10/10/22.
//

#ifndef SEATAC_ENGINE_BITBOARD_H
#include <bitset>


class bitboard {
public:
    std::bitset<64> board;
    char symbol;
    int piece;
    int value;

    bitboard()
    {
        board.reset();
    }
    auto operator()(int x, int y){
        assert(0<=x && x<=7);
        assert(0<=y && y<=7);
        return board[8*y+x];
    }

    void set(int pos)
    {
        assert(pos >= 0 && pos < board.size());
        board.set(pos);
    }
    void set()
    {
        board.set();
    }
    void reset()
    {
        board.reset();
    }

    static std::bitset<64> SouthOne(std::bitset<64> position);

    static std::bitset<64> NorthOne(std::bitset<64> position);
};


#endif //SEATAC_ENGINE_BITBOARD_H

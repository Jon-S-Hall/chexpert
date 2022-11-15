//
// Created by Jonathan Hall on 10/10/22.
//

#include "bitboard.h"

std::bitset<64> bitboard::SouthOne(std::bitset<64> position) {

    return position << 8;
}

std::bitset<64> bitboard::NorthOne(std::bitset<64> position) {
    return position >> 8;
}
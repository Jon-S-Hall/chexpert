//
// Created by Jonathan Hall on 12/26/22.
//

#include "HumanPlayer.h"

std::bitset<64> HumanPlayer::MakeMove(const GameState *gameState) const{

    std::bitset<64> chess_move;

    while(chess_move.none()) {
        std::string str_chess_move;

        std::cout << "Please Enter a Move: \n";
        std::cin >> str_chess_move;

        const char *char_chess_move = str_chess_move.c_str();

        chess_move = SeaChessUtils::CharMove_To_BitSetMove(char_chess_move);
    }

    return chess_move;
}

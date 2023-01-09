//
// Created by Jonathan Hall on 12/26/22.
//

#ifndef SEATAC_ENGINE_HUMANPLAYER_H
#define SEATAC_ENGINE_HUMANPLAYER_H

#include <iostream>
#include "ChessPlayer.h"

class HumanPlayer : public ChessPlayer{
public:

    HumanPlayer(Color color) : ChessPlayer(color){};

    std::bitset<64> MakeMove(const GameState *gameState) const;

    ~HumanPlayer() = default;
};


#endif //SEATAC_ENGINE_HUMANPLAYER_H

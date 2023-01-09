//
// Created by Jonathan Hall on 12/26/22.
//

#ifndef SEATAC_ENGINE_CHESSPLAYER_H
#define SEATAC_ENGINE_CHESSPLAYER_H

#include "SeaChessUtils.h"
#include "GameState.h"

class ChessPlayer{
public:

    explicit ChessPlayer(Color color)
    {
        m_color = color;
    }

    virtual ~ChessPlayer() = default;

    Color m_color;

    virtual std::bitset<64> MakeMove(const GameState *gameState) const = 0;

};


#endif //SEATAC_ENGINE_CHESSPLAYER_H

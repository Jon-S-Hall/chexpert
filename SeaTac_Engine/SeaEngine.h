//
// Created by Jonathan Hall on 10/20/22.
//

#ifndef SEATAC_ENGINE_SEAENGINE_H
#define SEATAC_ENGINE_SEAENGINE_H

#include "GameState.h"
#include "ChessPlayer.h"
#include <chrono>

class SeaEngine : public ChessPlayer{
public:
    SeaEngine(Color color, int depth)
    :ChessPlayer(color)
    ,m_depth(depth)
    {}

    ~SeaEngine() override = default;

    std::bitset<64> MakeMove( const GameState *gameState) const override;

    static std::bitset<64> CalculateBestMove(const GameState* gameState, int depth, Color color);
    static float CalculateBestMove_internal(const GameState* gameState, int depth, Color color);

    static int CalculateScore(const GameState* gameState);

public:
    int m_depth;
};


#endif //SEATAC_ENGINE_SEAENGINE_H

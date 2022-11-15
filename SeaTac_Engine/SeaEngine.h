//
// Created by Jonathan Hall on 10/20/22.
//

#ifndef SEATAC_ENGINE_SEAENGINE_H
#define SEATAC_ENGINE_SEAENGINE_H

#include "GameState.h"

class SeaEngine {
public:
    static float CalcBestMove(GameState gameState, int depth, bool color);
    static GameState MakeMove(GameState gameState, std::bitset<64> moveBoard, GameState::ChessPieces piece, bool color);
    static int CalculateScore(GameState gameState);
};


#endif //SEATAC_ENGINE_SEAENGINE_H

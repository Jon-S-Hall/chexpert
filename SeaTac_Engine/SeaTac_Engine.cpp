//
// Created by Jonathan Hall on 10/9/22.
//

#include "SeaTac_Engine.h"

//generates the best next move given game state. returns the bitset for the move that results in highest score
std::bitset<64> SeaTac_Engine::FindBestMove(GameState gameState, int depth) {
    // return if we are as deep as we want to go
    if(depth <= 0)
    {
        return NULL; //maybe return negative?
    }
    // find one valid move, create new gamestate to reflect this move, and call FindBestMove on new gamestate.

    // first pawns
    std::bitset<64> pawnPos = gameState.whitePieces[GameState::ChessPieces::Pawn];




    //bishops
    //knights
    //rooks
    //king
    //queen

    //find which move resulted in the highest score.

}

// calculates board state score based on:
// pieces*value
int SeaTac_Engine::CalculateScore() {
    int score = 0;
    bitboard *pieces;

    for(int i = 0; i < 6; i++)
    {
        score += pieces[i].board.count()*pieces[i].value;
    }

    return score;
}

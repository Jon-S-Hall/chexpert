#include <iostream>
#include "ChessGame.h"
#include "SeaTac_Engine.h"
#include "SeaEngine.h"

int main() {

    ChessGame game01; //why don't I need to explicitly initialize?
    game01.winner = -1;
    while(game01.winner == -1 && game01.moveNumber < 40) {
        game01.DisplayBoard();
        SeaEngine::CalcBestMove(*game01.gameState, 0, true);

        //generate best move.

        int sourceMove= 0;
        int destMove = 0;
        game01.moveNumber++;
        game01.winner = 1;
    }

    return 0;
}

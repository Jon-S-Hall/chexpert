#include <iostream>
#include <stdio.h>
#include "ChessGame.h"
#include "SeaChessUtils.h"
#include "ChessPlayer.h"

//This is the executed to run the chess game.
int main() {
/*
    GameState test("..........................q..B................................");
    std::bitset<64> queen = test.blackPieces[ChessPieces::Queen];
    SeaChessUtils::PrintBitBoard(queen);
    std::bitset<64> queenMoves;
    queenMoves = test.CalculateLegalMoves_Queen(queen, Color::Black);
    SeaChessUtils::PrintBitBoard(queenMoves);
*/

    const SeaEngine *white = new SeaEngine(Color::White, 4);
    const SeaEngine *black = new SeaEngine(Color::Black, 4);

    ChessGame chess_game(white, black);

    chess_game.StartGame();

    return 0;
}

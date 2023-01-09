//
// Created by Jonathan Hall on 10/9/22.
//

#ifndef SEATAC_ENGINE_CHESSGAME_H
#define SEATAC_ENGINE_CHESSGAME_H

#include "GameState.h"
#include "SeaEngine.h"
#include "ChessPlayer.h"

class ChessGame {
public:
    ChessGame(const ChessPlayer *white, const ChessPlayer *black)
    :m_Board("rnbqkbnrpppppppp................................PPPPPPPPRNBQKBNR")
    ,m_MoveNumber(1)
    ,m_Winner(-1)
    ,m_MaxGameMoves(50)
    ,m_PlayerWhite(white)
    ,m_PlayerBlack(black)
    ,m_GameState(m_Board)
    {
    }

    Color StartGame();

    void DisplayBoard();

    void UpdateBoard();
    //method for player/engine to interact with the game, and move the piece. returns the moveNumber.

    void UpdateGameWithMove(std::bitset<64> move);

    static char* GameStateToCharBoard(GameState GS);

    bool GameOver()
    {
        if(m_Winner == -1 && m_MoveNumber < m_MaxGameMoves)
        {
            return false;
        }
        return true;
    }

public:
    char *m_Board;
    int m_MoveNumber;
    int m_MaxGameMoves;
    int m_Winner;
    GameState m_GameState;
    const ChessPlayer* m_PlayerWhite;
    const ChessPlayer* m_PlayerBlack;
};


#endif //SEATAC_ENGINE_CHESSGAME_H

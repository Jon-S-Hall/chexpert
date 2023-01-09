//
// Created by Jonathan Hall on 10/10/22.
//

#include "GameState.h"

void GameState::initBitBoards(char *board) {
    {
        //initialize bitboards to 0. check if this is needed.
        for(int pos = 0; pos < 64; pos++)
        {
            char piece = board[pos];

            std::map<ChessPieces, std::bitset<64>> *pieces = (piece - 'a' > 0) ? &blackPieces : &whitePieces;

            switch(piece){
                case '0':
                    break;
                case 'K' :
                case 'k':
                    (*pieces)[ChessPieces::King].set(pos);
                    break;
                case 'Q':
                case 'q':
                    (*pieces)[ChessPieces::Queen].set(pos);
                    break;
                case 'R':
                case 'r':
                    (*pieces)[ChessPieces::Rook].set(pos);
                    break;
                case 'B':
                case 'b':
                    (*pieces)[ChessPieces::Bishop].set(pos);
                    break;
                case 'N':
                case 'n':
                    (*pieces)[ChessPieces::Knight].set(pos);
                    break;
                case 'P':
                case 'p':
                    (*pieces)[ChessPieces::Pawn].set(pos);
                    break;
                default:
                    printf("couldn't find a match for piece");
            }
        }
        occSquares.reset();
        white.reset();
        black.reset();
        //now initialize other boards
        for(int i = 0; i < 6; i++)
        {
            white |= whitePieces[(ChessPieces)i];
            black |= blackPieces[(ChessPieces)i];
            occSquares |= whitePieces[(ChessPieces)i];
            occSquares |= blackPieces[(ChessPieces)i];
        }

        for(int row = 0; row < 8; row++)
        {
            for(int col = 0; col < 8; col++) {
                rows[row][8 * row + col] = 1;
                columns[col][8 * row + col] = 1;
            }
        }
    }
}

std::bitset<64> GameState::CalculateLegalMoves(std::bitset<64> pp, ChessPieces piece, Color color) const {

    std::bitset<64> moves;

    switch (piece) {
        case (ChessPieces::Pawn):
            return CalculateLegalMoves_Pawn(pp, color);
        case (ChessPieces::King):
            return CalculateLegalMoves_King(pp, color);
        case (ChessPieces::Knight):
            return CalculateLegalMoves_Knight(pp, color);
        case (ChessPieces::Rook):
            return CalculateLegalMoves_Rook(pp, color);
        case (ChessPieces::Bishop):
            return CalculateLegalMoves_Bishop(pp, color);
        case (ChessPieces::Queen):
            return CalculateLegalMoves_Queen(pp, color);

    }

    return moves;
}




GameState GameState::GenerateGameStateFromMove(std::bitset<64> legal_move, Color color) const {

    GameState out_GameState(*this);

    std::bitset<64> *ourSide, *otherSide;
    std::map<ChessPieces, std::bitset<64>> *ourPieces, *otherPieces;
    if(color == Color::White)
    {
        ourSide = &(out_GameState.white);
        otherSide = &(out_GameState.black);
        ourPieces = &(out_GameState.whitePieces);
        otherPieces = &(out_GameState.blackPieces);
    }else
    {
        otherSide = &(out_GameState.white);
        ourSide = &(out_GameState.black);
        otherPieces = &(out_GameState.whitePieces);
        ourPieces = &(out_GameState.blackPieces);
    }

    ChessPieces pieceType = this->GetPieceFromGameState(legal_move, color);
    *ourSide ^= legal_move;
    (*ourPieces)[pieceType] ^= legal_move; //dont think I need this.
    //we have to nand
    std::bitset<64> bANDmB = (*otherSide) & legal_move; //will be empty or just the square we're attacking
    std::bitset<64> not_bANDmB = ~bANDmB;
    *otherSide &= not_bANDmB;

    //and the other occupied pieces with individual pieces to get rid of whatever piece we took out.
    for(int otherPiece = 0; otherPiece < 6; otherPiece++)
    {
        (*otherPieces)[(ChessPieces) otherPiece] &= *otherSide;
    }

    //and the other occupied pieces with individual pieces to get rid of whatever piece we took out.
    for(int ourPiece = 0; ourPiece < 6; ourPiece++)
    {
        (*ourPieces)[(ChessPieces) ourPiece] &= *ourSide;
    }

    out_GameState.occSquares = (out_GameState.black | out_GameState.white);

    return out_GameState;
}

std::bitset<64> GameState::CalculateLegalMoves_Pawn(std::bitset<64> pp, Color color) const {

    std::bitset<64> moves;
    if(color == Color::White)
    {
        //calculate exclusive moves
        std::bitset<64> vacuumMoves;
        vacuumMoves |= SeaChessUtils::NorthTwo(pp);
        vacuumMoves &= rows.at(4); //make sure we only move twice if it's the first move
        vacuumMoves |= SeaChessUtils::NorthOne(pp);
        //remove moves into obstacles
        vacuumMoves &= ~(vacuumMoves & occSquares);

        //calculate attacks
        std::bitset<64> attacks, attackLeft, attackRight;
        attackRight |= ((pp>>7) & ~columns.at(0));
        attackLeft |= ((pp>>9) & ~columns.at(7));
        attacks |= (attackLeft | attackRight);
        attacks &= black;

        moves = vacuumMoves | attacks;
    }else
    {
        //calculate exclusive moves
        std::bitset<64> vacuumMoves;
        vacuumMoves |= SeaChessUtils::SouthTwo(pp);
        vacuumMoves &= rows.at(3); //make sure we only move twice if it's the first move
        vacuumMoves |= SeaChessUtils::SouthOne(pp);
        //remove moves into obstacles
        vacuumMoves &= ~(vacuumMoves & occSquares);

        //calculate attacks
        std::bitset<64> attacks, attackLeft, attackRight;
        attackLeft |= ((pp<<7) & ~columns.at(7));
        attackRight |= ((pp<<9) & ~columns.at(0));
        attacks |= (attackLeft | attackRight);
        attacks &= white;

        moves = vacuumMoves | attacks;
    }
    return moves;
}

std::bitset<64> GameState::CalculateLegalMoves_King(std::bitset<64> pp, Color color) const
{
    std::bitset<64> vacuumMoves;

    std::bitset<64> up, down, upRight, upLeft, downRight, downLeft, right, left;

    up = SeaChessUtils::NorthOne(pp);
    down = SeaChessUtils::SouthOne(pp);

    upRight |= ((pp>>7) & ~columns.at(0));
    upLeft |= ((pp>>9) & ~columns.at(7));

    right |= ((pp >> 1) & ~columns.at(0));
    left |= ((pp << 1) & ~columns.at(7));

    downRight |= ((pp<<9) & ~columns.at(0));
    downLeft |= ((pp<<7) & ~columns.at(7));

    vacuumMoves = up | down | upRight | upLeft | right | left | downRight | downLeft;
    if(color == Color::White)
    {
        vacuumMoves &= ~white;
    }else
    {
        vacuumMoves &= ~black;
    }

    return vacuumMoves;
}

ChessPieces GameState::GetPieceFromGameState(std::bitset<64> pp, Color color) const {

    std::map<ChessPieces, std::bitset<64>> ourPieces = (color==Color::White ? whitePieces: blackPieces);

    for(auto& iter : ourPieces){
        if((iter.second & pp).any())
        {
            return iter.first;
        }
    }
    return ChessPieces::Pawn;
}

/*
 *      . NW . NE .
 *      WN . . . EN
 *       . . N . .
 *      WS . . . ES
 *        SW . SE
 */
std::bitset<64> GameState::CalculateLegalMoves_Knight(std::bitset<64> pp, Color color) const {
    std::bitset<64> vacuumMoves, ne, nw, en, es, se, sw, wn, ws;

    ne = pp >> 15;
    ne &= ~columns.at(0);

    nw = pp >> 17;
    nw &= ~columns.at(7);

    en = pp >> 6;
    en &= ~columns.at(0);
    en &= ~columns.at(1);

    es = pp << 10;
    es &= ~columns.at(0);
    es &= ~columns.at(1);

    se = pp << 17;
    se &= ~columns.at(0);

    sw = pp << 15;
    sw &= ~columns.at(7);

    wn = pp >> 10;
    wn &= ~columns.at(6);
    wn &= ~columns.at(7);

    ws = pp << 6;
    ws &= ~columns.at(6);
    ws &= ~columns.at(7);

    vacuumMoves = ne | nw | en | es | se | sw | wn | ws;

    if(color == Color::White)
    {
        vacuumMoves &= ~white;
    }else
    {
        vacuumMoves &= ~black;
    }

    return vacuumMoves;
}

std::bitset<64> GameState::CalculateLegalMoves_Rook(std::bitset<64> pp, Color color) const {

    const std::bitset<64>* otherSide = color==Color::White ? &black : &white;
    std::bitset<64> vacuumMoves, north, south, east, west;

    //generate moves east.

    int moveN = 1;
    int row = SeaChessUtils::GetRowFromPosition(pp);
    std::bitset<64> currentMove = pp << moveN;
    while((currentMove & occSquares).none() && (rows.at(row) & currentMove).any()) //no collision && same row
    {
        east |= pp<<moveN;
        moveN++;
        currentMove = pp << moveN;
    }

    if((currentMove & *otherSide).any())
    {
        east |= currentMove;
    }

    //generate moves west.
    moveN = 1;
    currentMove = pp >> moveN;
    while((currentMove & occSquares).none() && (rows.at(row) & currentMove).any()) //no collision && same row
    {
        west |= pp>>moveN;
        moveN++;
        currentMove = pp >> moveN;
    }

    if((currentMove & *otherSide).any())
    {
        west |= currentMove;
    }

    //generate moves north
    moveN = 1;
    currentMove = pp >> moveN*8;
    while((currentMove & occSquares).none() && currentMove.any())
    {
        north |= pp >> moveN*8;
        moveN++;
        currentMove = pp >> moveN*8;
    }

    if((currentMove & *otherSide).any())
    {
        north |= currentMove;
    }

    //generate moves south
    moveN = 1;
    currentMove = pp << moveN*8;
    while((currentMove & occSquares).none() && currentMove.any())
    {
        south |= pp << moveN*8;
        moveN++;
        currentMove = pp << moveN*8;
    }

    if((currentMove & *otherSide).any())
    {
        south |= currentMove;
    }

    vacuumMoves = north | south | east | west;
    return vacuumMoves;
}

/*
 *  NW .  .  . NE  .
 *  . NW  . NE  .  .
 *  .  .  b  .  .  .
 *  . SW  . SE  .  .
 *  SW .  .  . SE  .
 */
std::bitset<64> GameState::CalculateLegalMoves_Bishop(std::bitset<64> pp, Color color) const {

    const std::bitset<64>* otherSide = color==Color::White ? &black : &white;
    std::bitset<64> vacuumMoves, ne, nw, se, sw;

    //generate moves for ne
    int moveN = 1;
    std::bitset<64> currentMove = pp >> moveN*7;

    while((currentMove & occSquares).none() && (columns.at(0) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        ne |= currentMove;
        moveN++;
        currentMove = pp >> moveN*7;
    }

    if((currentMove & *otherSide).any()&& (columns.at(0) & currentMove).none())
    {
        ne |= currentMove;
    }

    //generate moves for nw
    moveN = 1;
    currentMove = pp >> moveN*9;

    while((currentMove & occSquares).none() && (columns.at(7) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        nw |= currentMove;
        moveN++;
        currentMove = pp >> moveN*9;
    }

    if((currentMove & *otherSide).any() && (columns.at(7) & currentMove).none())
    {
        nw |= currentMove;
    }

    //generate moves for se
    moveN = 1;
    currentMove = pp << moveN*9;

    while((currentMove & occSquares).none() && (columns.at(0) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        se |= currentMove;
        moveN++;
        currentMove = pp << moveN*9;
    }

    if((currentMove & *otherSide).any() && (columns.at(0) & currentMove).none())
    {
        se |= currentMove;
    }

    //generate moves for sw
    moveN = 1;
    currentMove = pp << moveN*7;

    while((currentMove & occSquares).none() && (columns.at(7) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        sw |= currentMove;
        moveN++;
        currentMove = pp << moveN*7;
    }

    if((currentMove & *otherSide).any()&& (columns.at(7) & currentMove).none())
    {
        sw |= currentMove;
    }

    vacuumMoves = ne | nw | se | sw;
    return vacuumMoves;
}

std::bitset<64> GameState::CalculateLegalMoves_Queen(std::bitset<64> pp, Color color) const {

    std::bitset<64> vacuumMoves, ne, n, nw, w, sw, s, se, e;
    const std::bitset<64>* otherSide = color==Color::White ? &black : &white;

    //generate moves for ne
    int moveN = 1;
    std::bitset<64> currentMove = pp >> moveN*7;

    while((currentMove & occSquares).none() && (columns.at(0) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        ne |= currentMove;
        moveN++;
        currentMove = pp >> moveN*7;
    }

    if((currentMove & *otherSide).any()&& (columns.at(0) & currentMove).none())
    {
        ne |= currentMove;
    }

    //generate moves for nw
    moveN = 1;
    currentMove = pp >> moveN*9;

    while((currentMove & occSquares).none() && (columns.at(7) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        nw |= currentMove;
        moveN++;
        currentMove = pp >> moveN*9;
    }

    if((currentMove & *otherSide).any() && (columns.at(7) & currentMove).none())
    {
        nw |= currentMove;
    }

    //generate moves for se
    moveN = 1;
    currentMove = pp << moveN*9;

    while((currentMove & occSquares).none() && (columns.at(0) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        se |= currentMove;
        moveN++;
        currentMove = pp << moveN*9;
    }

    if((currentMove & *otherSide).any() && (columns.at(0) & currentMove).none())
    {
        se |= currentMove;
    }

    //generate moves for sw
    moveN = 1;
    currentMove = pp << moveN*7;

    while((currentMove & occSquares).none() && (columns.at(7) & currentMove).none() && currentMove.any()) //no collision && same row
    {
        sw |= currentMove;
        moveN++;
        currentMove = pp << moveN*7;
    }

    if((currentMove & *otherSide).any()&& (columns.at(7) & currentMove).none())
    {
        sw |= currentMove;
    }

    //generate moves east.

    moveN = 1;
    int row = SeaChessUtils::GetRowFromPosition(pp);
    currentMove = pp << moveN;
    while((currentMove & occSquares).none() && (rows.at(row) & currentMove).any()) //no collision && same row
    {
        e |= pp<<moveN;
        moveN++;
        currentMove = pp << moveN;
    }

    if((currentMove & *otherSide).any())
    {
        e |= currentMove;
    }

    //generate moves west.
    moveN = 1;
    currentMove = pp >> moveN;
    while((currentMove & occSquares).none() && (rows.at(row) & currentMove).any()) //no collision && same row
    {
        w |= pp>>moveN;
        moveN++;
        currentMove = pp >> moveN;
    }

    if((currentMove & *otherSide).any())
    {
        w |= currentMove;
    }

    //generate moves north
    moveN = 1;
    currentMove = pp >> moveN*8;
    while((currentMove & occSquares).none() && currentMove.any())
    {
        n |= pp >> moveN*8;
        moveN++;
        currentMove = pp >> moveN*8;
    }

    if((currentMove & *otherSide).any())
    {
        n |= currentMove;
    }

    //generate moves south
    moveN = 1;
    currentMove = pp << moveN*8;
    while((currentMove & occSquares).none() && currentMove.any())
    {
        s |= pp << moveN*8;
        moveN++;
        currentMove = pp << moveN*8;
    }

    if((currentMove & *otherSide).any())
    {
        s |= currentMove;
    }

    vacuumMoves = n | ne | nw | w| sw | s | se | e;

    return vacuumMoves;
}


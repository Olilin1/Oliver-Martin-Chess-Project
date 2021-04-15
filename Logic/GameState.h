#ifndef GAMESTATE
#define GAMESTATE

#include"Enums.hpp"
#include"Typedefs.hpp"

struct GameState {
    Player currentPlayer;
    int fullMoveClock;
    int halfMoveClock;
    square blackKingPos;
    square whiteKingPos;
    square enPassant;
    bool canEnPassant;
    bool blackCanCastleKingSide;
    bool blackCanCastleQueenSide;
    bool whiteCanCastleKingSide;
    bool whiteCanCastleQueenSide;
};

#endif
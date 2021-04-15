#ifndef GAMESTATE
#define GAMESTATE

#include"Enums.hpp"

struct GameState {
    Player currentPlayer;
    int fullMoveClock;
    int halfMoveClock;
    int blackKingPos;
    int whiteKingPos;
    int blackEnPassant;
    int whiteEnPassant;
    bool blackCanEnPassant;
    bool whiteCanEnPassant;
    bool whiteCanCastle;
    bool blackCanCastle;
    bool blackCanCastleKingSide;
    bool blackCanCastleQueenSide;
    bool whiteCanCastleKingSide;
    bool whiteCanCastleQueenSide;
};

#endif
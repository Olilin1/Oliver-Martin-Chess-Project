#ifndef GAMESTATE
#define GAMESTATE

#include"Enums.hpp"

struct GameState {
    Player currentPlayer;
    int blackKingPos;
    int whiteKingPos;
    int blackEnPassant;
    int whiteEnPassant;
    bool blackCanEnPassant;
    bool whiteCanEnPassant;
    bool whiteCanCastle;
    bool blackCanCastle;
};

#endif
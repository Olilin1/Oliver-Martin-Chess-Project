#pragma once

#include"Enums.hpp"
#include"Typedefs.hpp"

//Contains misc info about the game
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
    bool awaitingPromotion;
    square promotion;
};

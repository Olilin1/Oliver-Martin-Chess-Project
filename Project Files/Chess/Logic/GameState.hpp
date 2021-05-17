#pragma once
#include"Enums.hpp"

struct GameState{
    Player currentPlayer;
    Player winner;
    int fullMoveClock;
    int halfMoveClock;

    int blackKingPos;
    int whiteKingPos;
    int enPassant;

    bool canEnPassant;
    bool blackCanCastleKingSide;
    bool blackCanCastleQueenSide;
    bool whiteCanCastleKingSide;
    bool whiteCanCastleQueenSide;
    bool awaitingPromotion = false;
    int promotion;
};
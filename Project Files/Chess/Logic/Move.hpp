#pragma once
#include"Enums.hpp"
#include"GameState.hpp"

struct Move {
    GameState moveGameState;

    //Contains basic information about the move, which can easily be reversed
    int origin;
    int destination;
    Piece capturedPiece = Empty;

    //Contains some metadata around the move, that must be stored in each move in order to be reversed accordingly
    bool enPassantMove = false;
    bool castledKingSide = false;
    bool castledQueenSide = false;
    bool promotion = false;
};

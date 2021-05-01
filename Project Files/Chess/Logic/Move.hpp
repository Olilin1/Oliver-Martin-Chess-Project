#pragma once
#include"Enums.hpp"
#include"Typedefs.hpp"
#include"GameState.hpp"

struct Move {
    GameState previousGameState;

    //Contains basic information about the move, which can easily be reversed
    square origin;
    square destination;
    Piece capturedPiece;

    //Contains some metadata around the move, that must be stored in each move in order to be reversed accordingly
    bool enPassantMove;
    bool castledKingSide;
    bool castledQueenSide;
    bool Promotion;
};


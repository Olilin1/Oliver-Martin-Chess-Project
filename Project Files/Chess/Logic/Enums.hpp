#pragma once

enum Player{
    Black = -1,
    White = 1,
    None = 0
};

enum Piece{     //White pieces are odd numbers, black pieces are even
    Empty = 0,
    WhitePawn = 1,
    BlackPawn = 2,
    WhiteKnight = 3,
    BlackKnight = 4,
    WhiteBishop = 5,
    BlackBishop = 6,
    WhiteRook = 7,
    BlackRook = 8,
    WhiteQueen = 9,
    BlackQueen = 10,
    WhiteKing = 11,
    BlackKing = 12
};

enum UncoloredPiece{
    Pawn = 1,
    Rook = 3,
    Knight = 5,
    Bishop = 7,
    Queen = 9,
    King = 11
};

enum LaunchMode {
    PVP = 1,
    DEBUG = 2,
    PVEWHITE = 3,
    PVEBLACK = 4
};


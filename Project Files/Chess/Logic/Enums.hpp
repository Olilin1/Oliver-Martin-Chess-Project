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
    WhiteRook = 3,
    BlackRook = 4,
    WhiteKnight = 5,
    BlackKnight = 6,
    WhiteBishop = 7,
    BlackBishop = 8,
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

#pragma once
enum Piece {
    Empty = 0,
    BlackPawn = -1,
    BlackRook = -2,
    BlackKnight = -3,
    BlackBishop = -4,
    BlackQueen = -5,
    BlackKing = -6,
    WhitePawn = 1,
    WhiteRook = 2,
    WhiteKnight = 3,
    WhiteBishop = 4,
    WhiteQueen = 5,
    WhiteKing = 6,
    Pawn = 7,
    Rook = 8,
    Knight = 9,
    Bishop = 10,
    Queen = 11,
    King = 12,
};

enum Player {
    None = 0,
    Black = -1, 
    White = 1
};
enum LaunchMode {
    PVP,
    DEBUG,
    PVEWHITE,
    PVEBLACK
};

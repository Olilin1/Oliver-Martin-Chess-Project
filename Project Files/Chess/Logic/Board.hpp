#ifndef BOARD
#define BOARD

#include"Enums.hpp"
#include"Typedefs.hpp"
#include<string>
#include<iostream>
#include<set>

/*
    A class that keeps track of a board, but nothing else
    Has some logic to check if squares are under attack but that is it.
*/
class Board{
    private:
    Piece board[8][8];

    public:
    Board();

    bool IsAttacked(square pos, Player attacker);
    bool IsAttackedByRookQueen(square pos, Player attacker);
    bool IsAttackedByBishopQueen(square pos, Player attacker);
    bool IsAttackedByKnight(square pos, Player attacker);
    bool IsAttackedByPawn(square pos, Player attacker);
    bool IsAttackedByKing(square pos, Player attacker);
    void MakeMove(square origin, square destination);

    //A lot of these helper functions are identical to the ones in the game class, so they should probably be moved to a separate file.
    //Especially the ones that don't require access to members.
    square AlgebraicToSquare(std::string);
    Player pieceColor(Piece);
    Player oppositePlayer(Player);
    Piece pieceType(Piece);
    bool isBlackPiece(Piece);
    bool isWhitePiece(Piece);
    std::string ConvertToUnicode(Piece i);
    void PrintBoard();
    bool OnBoard(square);
    bool IsEmpty(square);

    Piece& operator[](square);

};

#endif
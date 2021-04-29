#pragma once

#include"Enums.hpp"
#include"Typedefs.hpp"
#include"HelperFunctions.hpp"
#include"Constants.hpp"
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

    std::set<square> CalculateSlidingMoves(square, std::vector<std::pair<int,int>>);
    bool IsAttacked(square pos, Player attacker);
    bool IsAttackedByRook(square pos, Player attacker);
    bool IsAttackedByBishop(square pos, Player attacker);
    bool IsAttackedByQueen(square pos, Player attacker);
    bool IsAttackedByKnight(square pos, Player attacker);
    bool IsAttackedByPawn(square pos, Player attacker);
    bool IsAttackedByKing(square pos, Player attacker);
    
    
    //Simple helper functions
    void PrintBoard();
    bool IsEmpty(square);
    void RemovePiece(square);
    void MakeMove(square origin, square destination);

    Piece& operator[](square);

};
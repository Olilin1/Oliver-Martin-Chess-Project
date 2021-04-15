#ifndef GAME
#define GAME

#include"Enums.hpp"
#include"GameState.h"
#include"Typedefs.hpp"
#include<utility>
#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<sstream>



class Game{
private:
    Piece board[8][8];
    GameState gameState;

public:
    Game();
    void SetupGame(std::string fen);

    void MakeMove(square origin, square destination);
    std::set<square> AvailableMoves(square origin);
    bool IsLegal(square origin, square destination);
    bool IsAttacking(square, Player attacker);

    //Helper functions
    square AlgebraicToSquare(std::string);
    bool isBlackPiece(Piece);
    bool isWhitePiece(Piece);
    std::string ConvertToUnicode(Piece i);
    void PrintBoard();


};

#endif
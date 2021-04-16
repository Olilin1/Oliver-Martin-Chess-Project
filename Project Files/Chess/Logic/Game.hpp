#ifndef GAME
#define GAME

#include"Enums.hpp"
#include"GameState.hpp"
#include"Typedefs.hpp"
#include<utility>
#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<set>
#include<unordered_set>
#include<map>
#include<sstream>



class Game{
private:
    Piece board[8][8];
    GameState gameState;
    std::map<square, Piece> whitePieces;
    std::map<square, Piece> blackPieces;

public:
    Game();
    void SetupGame(std::string fen);

    void MakeMove(square origin, square destination);
    std::set<square> AvailableMoves(square origin);
    bool IsLegal(square origin, square destination);
    bool IsAttacking(square, Player attacker);
    bool CanGoTo(square origin, square destination);
    


    //Helper functions
    square AlgebraicToSquare(std::string);
    bool isBlackPiece(Piece);
    bool isWhitePiece(Piece);
    std::string ConvertToUnicode(Piece i);
    void PrintBoard();
    bool OnBoard(square);
    bool SameSidePieces(Piece a, Piece b);
    bool IsEmpty(square);
    void PlacePiece(square, Piece);
    void RemovePiece(square);


};

#endif
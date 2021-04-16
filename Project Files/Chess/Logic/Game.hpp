#ifndef GAME
#define GAME

#include"Enums.hpp"
#include"GameState.hpp"
#include"Typedefs.hpp"
#include"Board.hpp"
#include"Constants.hpp"
#include<cmath>
#include<utility>
#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<set>
#include<unordered_set>
#include<map>
#include<sstream>
/*
A class that handles all the logic for the game,
Board represents the board as a 2d array, gameState keeps track of misc things like player, castling, and so on
whitePieces and blackPieces are maps that make sure we don't have to iterate over the entire board to find whites pieces
Function explanations can be found at their definitions. Your IDE/Editor should have functionality to jump around between files.
*/




class Game{


private:
    

    Board board;
    GameState gameState;
    std::map<square, Piece> whitePieces;
    std::map<square, Piece> blackPieces;


public:
    Game();
    void SetupGame(std::string fen);

    void MakeMove(square origin, square destination);
    std::set<square> LegalPawnMoves(square);
    std::set<square> LegalBishopMoves(square);
    std::set<square> LegalRookMoves(square);
    std::set<square> LegalQueenMoves(square);  
    std::set<square> LegalKingMoves(square);
    std::set<square> LegalKnightMoves(square);
    std::set<square> CalculateSlidingMoves(square, std::vector<std::pair<int,int>>);



    //Short(ish)Helper functions, some of these should be private, and some should probably be static, 
    //and some might not be helper functions (ex printboard)
    //A lot of these are identical to functions in board.hpp and should be reworked to call on those, or moved to another file
    square CurrPlayerKingPostion();
    square AlgebraicToSquare(std::string);
    Player pieceColor(Piece);
    Player oppositePlayer(Player);
    Piece pieceType(Piece);
    bool canMove(square);
    bool isBlackPiece(Piece);
    bool isWhitePiece(Piece);
    bool isLegal(square origin, square destination);
    std::string ConvertToUnicode(Piece i);
    void PrintBoard();
    bool OnBoard(square);
    bool IsEmpty(square);
    void PlacePiece(square, Piece);
    void RemovePiece(square);


};

#endif
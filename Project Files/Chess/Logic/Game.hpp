#pragma once

#include"Enums.hpp"
#include"GameState.hpp"
#include"Typedefs.hpp"
#include"Board.hpp"
#include"Constants.hpp"
#include"HelperFunctions.hpp"
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

    bool MakeMove(square origin, square destination, Piece promotion = Empty);
    std::set<square> LegalPawnMoves(square);
    std::set<square> LegalKingMoves(square);
    std::set<square> LegalKnightMoves(square);
    std::set<square> LegalSlidingMoves(square, std::vector<std::pair<int,int>>);
    std::set<square> LegalMoves(square);
    Board getBoard();

    long long int SumOfAllMoves(int depth);
    std::set<std::pair<square,square>> CalculateAllMoves();

    bool gameIsOver();
    bool awaitingPromotion();

    //Short(ish)Helper functions, some of these should be private, and some should probably be static, 
    //and some might not be helper functions (ex printboard)
    square CurrPlayerKingPostion();

    bool canMove(square);
    bool isLegal(square origin, square destination);
    void PrintBoard();
    bool IsEmpty(square);
    void PlacePiece(square, Piece);
    void RemovePiece(square);
    Piece toCurrPlayer(Piece);
    


    };


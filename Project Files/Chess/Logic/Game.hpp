#pragma once

#include"Enums.hpp"
#include"GameState.hpp"
#include"Typedefs.hpp"
#include"Board.hpp"
#include"Constants.hpp"
#include"HelperFunctions.hpp"
#include"Move.hpp"
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
#include<stack>
#include"Bitboard.hpp"
/*A class that handles all the logic for the game,
Board represents the board as a 2d array, gameState keeps track of misc things like player, castling, and so on
whitePieces and blackPieces are maps that make sure we don't have to iterate over the entire board to find whites pieces
Function explanations can be found at their definitions. Your IDE/Editor should have functionality to jump around between files.
*/

class Game{


private:
    Board board;
    GameState gameState;

    Bitboard pieceBitboards[6];
    Bitboard whitePiecesBB;
    Bitboard blackPiecesBB;
public:
    Bitboard BishopBlockerBoards[64];
    Bitboard RookBlockerBoards[64];

    Game();
    void SetupGame(std::string fen);

    bool MakeMove(square origin, square destination, Piece promotion = Empty);
    void UnmakeMove();
    void LegalPawnMoves(int position, Bitboard& bitBoard);
    void LegalKingMoves(int position, Bitboard& bitBoard);
    void LegalKnightMoves(int position, Bitboard& bitBoard);
    void LegalRookMoves(int position, Bitboard& bitBoard);
    void LegalBishopMoves(int position, Bitboard& bitBoard);
    Bitboard LegalMoves(int position);
    Board getBoard();

    //Functions to generate the blocker boards for bishops and rooks
    void GenerateBishopBlockerBoards();
    void GenerateRookBlockerBoards();


    long long int SumOfAllMoves(int depth);
    void CalculateAllMoves(std::set<std::pair<square,square>>& );

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


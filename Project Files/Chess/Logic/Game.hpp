#ifndef GAME
#define GAME

#include"Enums.hpp"
#include"GameState.hpp"
#include"Typedefs.hpp"
#include"Board.hpp"
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
    void IsLegal(square origin, square destination); 
    std::set<square> LegalPawnMoves(square);
    std::set<square> LegalBishopMoves(square);
    std::set<square> LegalRookMoves(square);
    std::set<square> LegalQueenMoves(square);  
    std::set<square> LegalKingMoves(square);
    std::set<square> LegalKnightMoves(square);
    bool IsAttacked(square pos, Player attacker);
    bool IsAttackedByRookQueen(square pos, Player attacker);
    bool IsAttackedByBishopQueen(square pos, Player attacker);
    bool IsAttackedByKnight(square pos, Player attacker);
    bool IsAttackedByPawn(square pos, Player attacker);
    bool IsAttackedByKing(square pos, Player attacker);


    //Helper functions, some of these should be private, and some should probably be static
    square AlgebraicToSquare(std::string);
    Player pieceColor(Piece);
    Player oppositePlayer(Player);
    Piece pieceType(Piece);
    bool isBlackPiece(Piece);
    bool isWhitePiece(Piece);
    std::string ConvertToUnicode(Piece i);
    void PrintBoard();
    bool OnBoard(square);
    bool SameSidePieces(Piece a, Piece b);
    bool IsEmpty(square);
    void PlacePiece(square, Piece);
    void RemovePiece(square);
//    void Capture(square origin, square destination); //Combined place and remove


};

#endif
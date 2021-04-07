#pragma once
#include"Board.h"
#include"CastlingEnPassantCalculator.h"

//This class has different functions for calculating all the possible moves that each piece can make
class MoveCalculators {
private:
    std::unique_ptr<CastlingEnPassantCalculator> castlingEnPassantCalc; 
    CheckCalculator checkCalculator;
    Board& chessBoard;
public: 
    MoveCalculators(Board& board) : chessBoard(board){
        castlingEnPassantCalc = std::make_unique<CastlingEnPassantCalculator>(board);
    }
    //Each of the functions below calculate all of the possible moves of a piece of corresponding type, and returns a vector containing all the coordinates that the piece can move to
    std::set<std::pair<int, int>> CalculatePawnMoves(std::pair<int, int> startingPos) {
        std::set<std::pair<int, int>> legalMoves;
        //If it's white turn and the piece is at row 2, then it can move 2 steps forward (if it isn't blocked), otherwise it can move 1 step forward (if it isn't blocked and it's not outside the edge)
        if(chessBoard.currentPlayer == Black) {     
            //If it can capture an enemy piece or has en passant, then it can move diagonally
            if(CanGoTo(startingPos, {startingPos.first - 1, startingPos.second + 1})) legalMoves.insert({startingPos.first - 1, startingPos.second+1});
            if(CanGoTo(startingPos, {startingPos.first - 1, startingPos.second - 1})) legalMoves.insert({startingPos.first - 1, startingPos.second-1});

            if(CanGoTo(startingPos, {startingPos.first - 1, startingPos.second})) {     //The square one step in front of the pawn
                legalMoves.insert({startingPos.first - 1, startingPos.second});
                if(startingPos.first == 7 && CanGoTo(startingPos, {5, startingPos.second})) {    //The pawn is at row 7 and can thus can move two steps forward if it isn't blocked
                    legalMoves.insert({5, startingPos.second});
                }
            }
        }
        else if(chessBoard.currentPlayer == White) {
            if(CanGoTo(startingPos, {startingPos.first + 1, startingPos.second + 1})) legalMoves.insert({startingPos.first+1, startingPos.second+1});
            if(CanGoTo(startingPos, {startingPos.first + 1, startingPos.second - 1})) legalMoves.insert({startingPos.first + 1, startingPos.second-1});

            if(CanGoTo(startingPos, {startingPos.first + 1, startingPos.second})) {     //The square one step in front of the pawn is empty, and not outside the edge of the board
                legalMoves.insert({startingPos.first + 1, startingPos.second});
                if(startingPos.first == 2 && CanGoTo(startingPos, {4, startingPos.second})) {    //The pawn is at row 2 and can thus move two steps forward if it isn't blocked
                    legalMoves.insert({4, startingPos.second});
                }
            }
        }
        return legalMoves;
    }

    std::set<std::pair<int, int>> CalculateKnightMoves(std::pair<int, int> startingPos) {
        std::set<std::pair<int, int>> legalMoves;
        //The knight can move to several different positions. This simply checks if each of these positions contain a piece that is not the enemy piece and that it isn't outside the edge of the board
        for(int i : {2, -2}) {
            for(int j : {1, -1}) {
                if(CanGoTo(startingPos, {startingPos.first + i, startingPos.second + j})) {
                    legalMoves.insert({startingPos.first + i, startingPos.second + j});
                }
                if(CanGoTo(startingPos, {startingPos.first + j, startingPos.second + i})) {
                    legalMoves.insert({startingPos.first + j, startingPos.second + i});
                }
            }
        }   
        return legalMoves;
        //std::pair<int, int> distanceToClosestEdge;      Maybe an optimization for later: check the distance to the closest edge and immediately rule out some options depending on this distance
    }

    std::set<std::pair<int, int>> CalculateKingMoves(std::pair<int, int> startingPos) {
        std::set<std::pair<int, int>> legalMoves;
        //Calculates each move that the king can make 
        for(int i = -1; i <= 1; i++) {
            for(int j = -1; j<=1;j++) {
                if(!i && !j) continue;
                if(CanGoTo(startingPos, {startingPos.first + i, startingPos.second + j})) legalMoves.insert({startingPos.first + i, startingPos.second + j});
            }
        }
        if(chessBoard.currentPlayer == Black && chessBoard.gameState.blackCanCastle) {
            std::set<std::pair<int, int>> castleMoves = castlingEnPassantCalc->BlackCastle();
            legalMoves.insert(castleMoves.begin(), castleMoves.end());
        }
        else if(chessBoard.gameState.whiteCanCastle) {
            std::set<std::pair<int, int>> castleMoves = castlingEnPassantCalc->WhiteCastle();
            legalMoves.insert(castleMoves.begin(), castleMoves.end());
        }
        return legalMoves;
    }

    std::set<std::pair<int, int>> CalculateSlidingMoves(std::pair<int, int> startingPos) {
        std::set<std::pair<int, int>> legalMoves;
        int pieceType = abs(chessBoard.GetPieceType(startingPos.first, startingPos.second));
        //Loops through all 8 diagonal and horizontal/vertical directions and checks how far the piece can move in each direction
        std::pair<int, int> nextPos; 
        if(pieceType != 4) {        //It's not a bishop
            for(int i : {1, -1}) {
                nextPos = {startingPos.first + i, startingPos.second};
                while(CanGoTo(startingPos, nextPos)) {
                    legalMoves.insert(nextPos);
                    if(CheckIfLastPosWasCollision(nextPos)) break;
                    nextPos = {nextPos.first + i, nextPos.second}; 
                }
                nextPos = {startingPos.first, startingPos.second + i};
                while(CanGoTo(startingPos, nextPos)) {
                    legalMoves.insert(nextPos);
                    if(CheckIfLastPosWasCollision(nextPos)) break;
                    nextPos = {nextPos.first, nextPos.second + i}; 
                }  
            }
        }
        if(pieceType != 2) {   //It's not a rook
            for(int i : {1, -1}) {
                for(int j : {-1, 1}) {
                    nextPos = {startingPos.first + i, startingPos.second + j};
                    while(CanGoTo(startingPos, nextPos)) {
                        legalMoves.insert(nextPos);
                        if(CheckIfLastPosWasCollision(nextPos)) break;
                        nextPos = {nextPos.first + i, nextPos.second + j}; 
                    }   
                }
            } 
        }
        return legalMoves;
    }   

    //If the last pos was an opposing piece, then the sliding piece should not be able to keep sliding. This function checks if the currently moving sliding piece has collided with an opposing piece
    bool CheckIfLastPosWasCollision(std::pair<int, int> pos) {
        if(chessBoard.currentPlayer == Black)   {
            return (chessBoard.GetPieceType(pos.first, pos.second) > 0);
        } else {
            return (chessBoard.GetPieceType(pos.first, pos.second) < 0);
        }
    }

    std::pair<int, int> ConvertToPair (int oneD) {
        return {(oneD - (oneD % 8))/8 +1, 1 + oneD%8}; 
    }

    bool CanGoTo(std::pair<int, int> startingPos, std::pair<int, int> pos) {
        if(OnBoard(pos)) {
            if(chessBoard.currentPlayer == Black) {    
                Piece currentPiece = chessBoard.GetPieceType(startingPos.first, startingPos.second);
                if(currentPiece < -1) {
                    if(chessBoard.GetPieceType(pos.first,pos.second) >= 0) {        //If the value at the position is greater than or equal to 0, then it contains a white piece or is empty and black can therefore move to it
                        std::pair<int, int> blackKingPos = (chessBoard.GetPieceType(startingPos.first, startingPos.second) == BlackKing) ? pos : ConvertToPair(chessBoard.gameState.blackKingPos);
                        Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                        return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard, blackKingPos);   //If someone has check CheckIfSomeoneHasCheck() returns true and GoTo() should thus return false
                    }
                }       //Because the pawn is the only piece that can't always capture the piece at the same square that it can move to (if the piece is of opposite color and no check occurs), I need to separate it from the other cases in this if statement
                else if(currentPiece == BlackPawn){
                    return castlingEnPassantCalc->CheckPawnMove(startingPos, pos);
                }
                return false;
            }
            else {
                Piece currentPiece = chessBoard.GetPieceType(startingPos.first, startingPos.second);
                if(currentPiece > 1) {    //It's a white piece, but not a pawn
                    if(chessBoard.GetPieceType(pos.first, pos.second) <= 0) {
                        std::pair<int, int> whiteKingPos = (chessBoard.GetPieceType(startingPos.first, startingPos.second) == WhiteKing) ? pos : ConvertToPair(chessBoard.gameState.whiteKingPos);
                        Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                        return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard, whiteKingPos);  
                    }
                }
                else if(currentPiece == WhitePawn){
                    return castlingEnPassantCalc->CheckPawnMove(startingPos, pos);
                }
                return false;
            }
        }
        return false;
    }

    bool OnBoard(std::pair<int, int> pos) {
        if(pos.first <= 8 && pos.first >= 1 && pos.second <= 8 && pos.second >= 1) {
            return true;
        }
        return false;
    }
};
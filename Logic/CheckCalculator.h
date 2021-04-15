#pragma once
#include"Board.h"
#include<memory>

//This class has the king as starting position and checks all possible attacks on the king
class CheckCalculator {
private:
    std::unique_ptr<Board> chessBoard;
    bool IsAttackedByKnights (std::pair<int, int> pos) {
        for(int i : {2, -2}) {
            for(int j : {1, -1}) {
                if(OnBoard({pos.first + i, pos.second + j}) && chessBoard->GetPieceType(pos.first + i, pos.second + j) == ((chessBoard->gameState.currentPlayer == Black) ? WhiteKnight : BlackKnight)) {
                    return true;
                }
                if(OnBoard({pos.first + j, pos.second + i}) && chessBoard->GetPieceType(pos.first + j, pos.second + i) == ((chessBoard->gameState.currentPlayer == Black) ? WhiteKnight : BlackKnight)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool IsAttackedVerticallyHorizontally(std::pair<int, int> pos) {
        if(CheckDirection(pos, 0, 1) || CheckDirection(pos, 0, -1) || CheckDirection(pos, 1, 0) || CheckDirection(pos, -1, 0)) {
            return true; 
        }
        return false;
    }

    bool IsAttackedDiagonally(std::pair<int, int> position) {
        if(CheckDirection(position, 1, 1) || CheckDirection(position, -1, 1) || CheckDirection(position, -1, -1) || CheckDirection(position, 1, -1)) {
            return true;
        }
        return false;
    }

    //Checks the direction (directionY, directionX) (a bit confusion because a piece has coordinates (row, columns)). Returns true if the king is attacked in the direction, returns false otherwise
    bool CheckDirection(std::pair<int, int> startingPos, int directionX, int directionY) {
        std::pair<int, int> nextPos = {startingPos.first + directionX, startingPos.second + directionY};
        while(OnBoard(nextPos) && chessBoard->GetPieceType(nextPos.first, nextPos.second) == Empty) {
            nextPos = {nextPos.first + directionX, nextPos.second + directionY};
        }
        Piece blockingPiece;
        if(OnBoard(nextPos)) {
            blockingPiece = chessBoard->GetPieceType(nextPos.first, nextPos.second);
        }
        else {
            return false;   //There was no piece blocking up until an edge, therefore return false
        }
        if(chessBoard->gameState.currentPlayer == Black) {
            if(directionX != 0 && directionY != 0) {        //It was a diagonal direction
                return ((blockingPiece == WhiteBishop || blockingPiece == WhiteQueen) ? true : false);    //If the black piece at the startingPos has an open diagonal with a white piece at the end, then it is under attack if that white piece is a white queen or bishop
            }
            else {      //It was a horizontal/vertical direction                                          //Same as above applies for horizontal/vertical directions and when the white piece is a rook or a queen
                return ((blockingPiece == WhiteRook || blockingPiece == WhiteQueen) ? true : false);
            }
        }
        else if(chessBoard->gameState.currentPlayer == White) {
            if(directionX != 0 && directionY != 0) {
                return ((blockingPiece == BlackBishop || blockingPiece == BlackQueen) ? true : false);    
            }
            else {
                return ((blockingPiece == BlackRook || blockingPiece == BlackQueen) ? true : false);
            }
        }
        return false;
    }

    bool IsAttackedByPawns(std::pair<int, int> position) {
        if(chessBoard->gameState.currentPlayer == Black) {
            if(OnBoard({position.first - 1, position.second - 1}) && chessBoard->GetPieceType(position.first - 1, position.second - 1) == WhitePawn 
            || OnBoard({position.first - 1, position.second + 1}) && chessBoard->GetPieceType(position.first - 1, position.second + 1) == WhitePawn){
                return true;
            }
        }
        else if(chessBoard->gameState.currentPlayer == White) {
            if(OnBoard({position.first + 1, position.second - 1}) && chessBoard->GetPieceType(position.first + 1, position.second - 1) == BlackPawn   
            || OnBoard({position.first + 1, position.second + 1}) && chessBoard->GetPieceType(position.first + 1, position.second + 1) == BlackPawn){
                return true;
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

     //Converts a coordinate consisting of one integer to a coordinate of a pair of two integers
    std::pair<int, int> ConvertToPair (int oneD) {
        return {(oneD - (oneD % 8))/8 +1, 1 + oneD%8}; 
    }

public:
    bool CheckIfSomeoneHasCheck(Board& board) {
        std::pair<int, int> kingPos;
        if(board.gameState.currentPlayer == Black) {
            kingPos = ConvertToPair(board.gameState.blackKingPos);
        }   
        else {
            kingPos = ConvertToPair(board.gameState.whiteKingPos); 
        }
        chessBoard = std::make_unique<Board>(board);
        if(IsAttackedDiagonally(kingPos) || IsAttackedVerticallyHorizontally(kingPos) || IsAttackedByPawns(kingPos) || IsAttackedByKnights(kingPos)) {
            return true;
        }
        return false;
    }
};
#pragma once
#include"CalculateMoves.h"
#include"CheckCalculator.h"

class CastlingEnPassantCalculator {
private:
    Board& chessBoard;
    CheckCalculator checkCalculator;
    std::unique_ptr<GameState> gameState;
public:
    CastlingEnPassantCalculator(Board& board) : chessBoard(board) {
        gameState = std::make_unique<GameState>(board.gameState);
    }

    std::set<std::pair<int, int>> BlackCastle() {
        std::set<std::pair<int, int>> legalMoves;
        for(int i : {2, 3, 4}) {
            if(chessBoard.GetPieceType(8, i) != Empty) {
                break;
            }
            legalMoves.insert({8, 2});
        }
        for(int i : {7, 6}) {
            if(chessBoard.GetPieceType(8, i) != Empty) {
                break;
            }
            legalMoves.insert({8, 7});
        } 
        return legalMoves;
    }

    std::set<std::pair<int, int>> WhiteCastle() {
        std::set<std::pair<int, int>> legalMoves;
        for(int i : {2, 3, 4}) {
            if(chessBoard.GetPieceType(1, i) != Empty) {
                break;
            }
            legalMoves.insert({1, 2});
        }
        for(int i : {7, 6}) {
            if(chessBoard.GetPieceType(1, i) != Empty) {
                break;
            }
            legalMoves.insert({1, 7});
        } 
        return legalMoves;
    } 
    
    //Converts a coordinate consisting of one integer to a coordinate of a pair of two integers
    std::pair<int, int> ConvertToPair (int oneD) {
        return {(oneD - (oneD % 8))/8 +1, 1 + oneD%8}; 
    }

    int ConvertToSingle(int x, int y) {
        return (x-1)*8 + (y-1);
    }

    bool CheckPawnMove(std::pair<int, int> startingPos, std::pair<int, int> pos) {
        if(pos.second != startingPos.second) {        //The pawn is trying to move diagonally
            if(chessBoard.currentPlayer == Black) {
                if(chessBoard.GetPieceType(pos.first, pos.second) > 0 || BlackCanEnPassantFrom(pos)) {
                    Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                    return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard, ConvertToPair(gameState->blackKingPos));    
                }
            }
            else {
                if(chessBoard.GetPieceType(pos.first, pos.second) < 0 || WhiteCanEnPassantFrom(pos)) {
                    Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                    return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard, ConvertToPair(gameState->whiteKingPos));    
                }
            }
        }
        else {
            if(chessBoard.GetPieceType(pos.first, pos.second) == Empty) {       //If the pawn is not moving diagonally, then the square has to be empty
                Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard, ((chessBoard.currentPlayer == Black) ? ConvertToPair(gameState->blackKingPos) : ConvertToPair(gameState->whiteKingPos)));     
            }
        }
        return false;
    }
    bool BlackCanEnPassantFrom(std::pair<int, int> pos) {
        return gameState->blackCanEnPassant && gameState->blackEnPassant == ConvertToSingle(pos.first, pos.second);
    }
    bool WhiteCanEnPassantFrom(std::pair<int, int> pos) {
       return gameState->whiteCanEnPassant && gameState->whiteEnPassant == ConvertToSingle(pos.first, pos.second);
    }
};
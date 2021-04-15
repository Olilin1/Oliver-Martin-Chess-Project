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

    //If this function is called it is guaranteed that black still has the abillity to castle. 
    //This function checks if all the squares between the king and the rook in both directions are empty. If they are, and no check occurs after a castling, then a castling move is added to legalMoves
    std::set<std::pair<int, int>> BlackCastle() {
        std::set<std::pair<int, int>> legalMoves;
        if(chessBoard.GetPieceType(8, 2) == Empty
        && chessBoard.GetPieceType(8, 3) == Empty
        && chessBoard.GetPieceType(8, 4) == Empty) {
            Board tempBoard = chessBoard.UpdateBoardCopy({8, 5}, {8, 3}, chessBoard);
            if(!checkCalculator.CheckIfSomeoneHasCheck(tempBoard)) {
                legalMoves.insert({8, 3});
            }
        }
        
        if(chessBoard.GetPieceType(8, 7) == Empty
        && chessBoard.GetPieceType(8, 6) == Empty) {
            Board tempBoard = chessBoard.UpdateBoardCopy({8, 5}, {8, 7}, chessBoard);
            if(!checkCalculator.CheckIfSomeoneHasCheck(tempBoard)) {
                legalMoves.insert({8, 7});
            }
        }
        return legalMoves;
    }

    std::set<std::pair<int, int>> WhiteCastle() {
        std::set<std::pair<int, int>> legalMoves;
        if(chessBoard.GetPieceType(1, 2) == Empty
        && chessBoard.GetPieceType(1, 3) == Empty
        && chessBoard.GetPieceType(1, 4) == Empty) {
            Board tempBoard = chessBoard.UpdateBoardCopy({1, 5}, {1, 3}, chessBoard);
            if(!checkCalculator.CheckIfSomeoneHasCheck(tempBoard)) {
                legalMoves.insert({1, 3});
            }
        }

        if(chessBoard.GetPieceType(1, 7) == Empty
        && chessBoard.GetPieceType(1, 6) == Empty) {
            Board tempBoard = chessBoard.UpdateBoardCopy({1, 5}, {1, 7}, chessBoard);
            if(!checkCalculator.CheckIfSomeoneHasCheck(tempBoard)) {
                legalMoves.insert({1, 7});
            }
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

    //This function checks if a pawn can make a certain move, from startingPos to pos. 
    //I already know that the move is legal in the sense that it is a move that a pawn could potentially make. The function CalculatePawnMoves in MoveCalculators ensures this
    bool CheckPawnMove(std::pair<int, int> startingPos, std::pair<int, int> pos) {
        if(pos.second != startingPos.second) {        //The pawn is trying to move diagonally
            if(chessBoard.gameState.currentPlayer == Black) {
                if(chessBoard.GetPieceType(pos.first, pos.second) > 0 || BlackCanEnPassantFrom(pos)) {      //A pawn can make a diagonal move if it is either en passant, or the piece diagonal to the pawn is of opposite color
                    Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                    return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard);    
                }
            }
            else {
                if(chessBoard.GetPieceType(pos.first, pos.second) < 0 || WhiteCanEnPassantFrom(pos)) {
                    Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                    return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard);    
                }
            }
        }
        else {
            if(chessBoard.GetPieceType(pos.first, pos.second) == Empty) {       //If the pawn is not moving diagonally, then the square has to be empty
                Board tempBoard = chessBoard.UpdateBoardCopy(startingPos, pos, chessBoard);
                return !checkCalculator.CheckIfSomeoneHasCheck(tempBoard);     
            }
        }
        return false;
    }
    bool BlackCanEnPassantFrom(std::pair<int, int> pos) {
        return (gameState->blackCanEnPassant && gameState->blackEnPassant == ConvertToSingle(pos.first, pos.second));
    }
    bool WhiteCanEnPassantFrom(std::pair<int, int> pos) {
       return (gameState->whiteCanEnPassant && gameState->whiteEnPassant == ConvertToSingle(pos.first, pos.second));
    }
};
#pragma once
#include<unordered_map>
#include<utility>
#include<vector>
#include<stdlib.h>
#include<set>
#include"Board.h"
#include"CheckCalculator.h"
#include"MoveCalculators.h"

class CalculateMoves {
private: 
    Board& chessBoard;
    //std::unique_ptr<MoveCalculators> moveCalculators;
public:
    CalculateMoves(Board& board) : chessBoard(board)  {
        //moveCalculators = std::make_unique<MoveCalculators>(chessBoard);
    }

    int SumOfAllMoves(int depth) {
        int sum = 0;
        CalculateAllMoves(depth, sum);
        return sum;
    }

    //In this tree where edges are moves and nodes are game configurations, the leaves represent all the unique games for a game with n moves, where the tree has
    //height logn. This function counts all those leaves for depth moves.
    void CalculateAllMoves(int depth, int& sum) {
        if(depth == 0) {
            sum += 1;
            return;
        }
        if(chessBoard.currentPlayer == White) {
            for(auto posIterator = chessBoard.getWhitePositions().first; posIterator != chessBoard.getWhitePositions().second; posIterator++) {
                std::pair<int, int> currentPos = ConvertToPair(posIterator->first);
                Piece currentPiece = chessBoard.GetPieceType(currentPos.first, currentPos.second);
                std::set<std::pair<int, int>> allMovesForOnePiece = CalculatePieceMove(currentPos);
                for(auto it : allMovesForOnePiece) {
                    chessBoard.UpdateBoard(currentPos, it, currentPiece);
                    CalculateAllMoves(depth - 1, sum);
                    chessBoard.UnUpdateBoard();
                }
            }
        }
        else {
            for(auto posIterator = chessBoard.getBlackPositions().first; posIterator != chessBoard.getBlackPositions().second; posIterator++) {
                std::pair<int, int> currentPos = ConvertToPair(posIterator->first);
                std::set<std::pair<int, int>> allMovesForOnePiece = CalculatePieceMove(currentPos);
                Piece currentPiece = chessBoard.GetPieceType(currentPos.first, currentPos.second);
                for(auto it : allMovesForOnePiece) {
                    chessBoard.UpdateBoard(currentPos, it, currentPiece);
                    CalculateAllMoves(depth - 1, sum);
                    chessBoard.UnUpdateBoard();
                }
            }
        }
    }

    std::pair<int, int> ConvertToPair (int oneD) {
        return {(oneD - (oneD % 8))/8 +1, 1 + oneD%8}; 
    }

    std::set<std::pair<int, int>> CalculatePieceMove(std::pair<int, int> startingPos) {
        MoveCalculators moveCalculators(chessBoard);
        int pieceType = chessBoard.GetPieceType(startingPos.first, startingPos.second);
        if(pieceType == Empty) {
            return std::set<std::pair<int, int>>(); 
        }
        switch (abs(pieceType)) {   //We know the function is called for the pieces of either white or black so the sign is irrelevant here
            case 1:
                return moveCalculators.CalculatePawnMoves(startingPos);
            case 3:
                return moveCalculators.CalculateKnightMoves(startingPos);
            case 6:
                return moveCalculators.CalculateKingMoves(startingPos);
            default:
                return moveCalculators.CalculateSlidingMoves(startingPos);    //I can group the moves of the rook, bishop and queen into one function because they all have similar behaviour
        }
    }
};
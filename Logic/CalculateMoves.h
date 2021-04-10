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
        CalculateAllMoves(chessBoard, depth, sum);
        return sum;
    }

    //In this tree where edges are moves and nodes are game configurations, the leaves represent all the unique games for a game with n moves, where the tree has
    //height logn. This function counts all those leaves for depth moves.
    void CalculateAllMoves(Board currentBoard, int depth, int& sum) {
        if(depth == 0) {
            sum += 1;
            return;
        }
        if(currentBoard.currentPlayer == White) {
            for(auto posIterator = currentBoard.getWhitePositions().first; posIterator != currentBoard.getWhitePositions().second; posIterator++) {
                std::pair<int, int> currentPos = ConvertToPair(posIterator->first);
                std::set<std::pair<int, int>> allMovesForOnePiece = CalculatePieceMove(currentPos, currentBoard);
                for(auto it : allMovesForOnePiece) {
                    Board tempBoard = currentBoard.UpdateBoardCopy(currentPos, it, currentBoard);
                    tempBoard.NewTurn();
                    CalculateAllMoves(tempBoard, depth - 1, sum);
                }
            }
        }
        else {
            for(auto posIterator = currentBoard.getBlackPositions().first; posIterator != currentBoard.getBlackPositions().second; posIterator++) {
                std::pair<int, int> currentPos = ConvertToPair(posIterator->first);
                std::set<std::pair<int, int>> allMovesForOnePiece = CalculatePieceMove(currentPos, currentBoard);
                for(auto it : allMovesForOnePiece) {
                    Board tempBoard = currentBoard.UpdateBoardCopy(currentPos, it, currentBoard);
                    tempBoard.NewTurn();
                    CalculateAllMoves(tempBoard, depth - 1, sum);
                }
            }
        }
    }

    std::pair<int, int> ConvertToPair (int oneD) {
        return {(oneD - (oneD % 8))/8 +1, 1 + oneD%8}; 
    }

    std::set<std::pair<int, int>> CalculatePieceMove(std::pair<int, int> startingPos, Board chessBoard) {
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
#include"Board.h"
#include<string>
#include<algorithm>
#include<vector>
#include<utility>
#include"CalculateMoves.h"
#include<iostream>
#include<set>

//Struct that contains the relevant information about the move that was made
struct Move {
    std::pair<int, int> moveFrom;
    std::pair<int, int> moveTo;
    Piece pieceType;
    bool captureMove;   //True if the moved piece captures another piece
    bool castling;  //True if the move was a castling move. If it was, then no more castling can be done for that player
    bool enPassant;     //True if the move enables the opponent to do an en passant on the upcoming move
    Move(std::pair<int, int> mF, std::pair<int, int> mT, Piece pTWM) : moveFrom(mF), moveTo(mT), pieceType(pTWM) {}
};

//This class is for later, in case that we add functionality to store each move in a vector of moves, so that we don't need to create a new board after each move. The idea came from the first section of https://www.cs.cornell.edu/boom/2004sp/ProjectArch/Chess/algorithms.html
class MoveTracker {
private:
    Board& board;
    //Vector that stores all the moves that have been made since the previous update. 
    //This makes it so that the board doesn't need to be completely updated after each move, which will save time and space later when implementing algorithms for the ai that will search through many moves
    std::vector<Move> listOfMoves;     
public:
    MoveTracker(Board& b) : board(b) {}

    //Moves a piece of type pieceType from firstPos to secondPos
    void MakeTheMove(std::pair<int, int> firstPos, std::pair<int, int> secondPos) {
        Piece pieceType = board.GetPieceType(firstPos.first, firstPos.second);
        listOfMoves.push_back(Move(firstPos, secondPos, pieceType));
    }

    //Update all the moves
    void UpdateMoves() {
        for(auto m : listOfMoves) {
            board.UpdateBoard(m.moveFrom, m.moveTo, m.pieceType);
        }
    }
};
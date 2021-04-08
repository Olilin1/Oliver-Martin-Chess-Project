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
    // bool captureMove;   //True if the moved piece captures another piece
    // bool castling;  //True if the move was a castling move. If it was, then no more castling can be done for that player
    // bool enPassant;     //True if the move enables the opponent to do an en passant on the upcoming move
    Move(std::pair<int, int> mF, std::pair<int, int> mT, Piece pTWM) : moveFrom(mF), moveTo(mT), pieceType(pTWM) {}
};

class MakeMove {
private:
    Board& board;
    //Vector that stores all the moves that have been made since the previous update. 
    //This makes it so that the board doesn't need to be completely updated after each move, which will save time and space later when implementing algorithms for the ai that will search through many moves
    std::vector<Move> listOfMoves;     
public:
    MakeMove(Board& b) : board(b) {}

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

void MakeLegalMove(MakeMove& m, Board& chessBoard, CalculateMoves& moveCalc, std::pair<int, int> startingPos, std::pair<int, int> nextPos) {
    m.MakeTheMove(startingPos, nextPos);
    Piece pieceType = chessBoard.GetPieceType(startingPos.first, startingPos.second);
    chessBoard.UpdateBoard(startingPos, nextPos, pieceType);
    chessBoard.NewTurn();
    chessBoard.PrintBoard();
}

Board chessBoard;
CalculateMoves moveCalc(chessBoard);
MakeMove m(chessBoard);   

int main() {
    chessBoard.PrintBoard();
    // int sum = moveCalc.SumOfAllMoves(3);
    // std::cout<<sum<<std::endl;
    while(true) {
        int x, y, xNew, yNew;
        std::cin >> x >> y >> xNew >> yNew;
        // MakeLegalMove(m ,chessBoard, moveCalc, {2, 5}, {3, 5});
        // MakeLegalMove(m, chessBoard, moveCalc, {7, 5}, {5, 5});
        // MakeLegalMove(m, chessBoard, moveCalc, {1, 4}, {5, 8});
        // x = 8;
        // y = 7;
        // xNew = 6;
        // yNew = 6;
        std::set<std::pair<int, int>> legalMoves = moveCalc.CalculatePieceMove({x, y}, chessBoard); 
        for(auto it : legalMoves) {
            std::cout<<it.first<<" "<<it.second<<std::endl;
        }       
        if(legalMoves.count({xNew, yNew})) {
            MakeLegalMove(m, chessBoard, moveCalc, {x, y}, {xNew, yNew});
        }
        else {
            std::cout<<"Illegal move!"<<std::endl;
        }
    }
}
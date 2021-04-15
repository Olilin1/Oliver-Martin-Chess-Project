#include"Board.h"
#include"CalculateMoves.h"
#include <unistd.h>

void MakeMove(Board& chessBoard, std::pair<int, int> startingPos, std::pair<int, int> nextPos) {
    Piece pieceType = chessBoard.GetPieceType(startingPos.first, startingPos.second);
    chessBoard.UpdateBoard(startingPos, nextPos, pieceType);
    chessBoard.PrintBoard();
    usleep(1000000);
    chessBoard.UnUpdateBoard();
    chessBoard.PrintBoard();
    usleep(1000000);
    chessBoard.UpdateBoard(startingPos, nextPos, pieceType);
    chessBoard.PrintBoard();
}

//If you want to play chess against yourself, comment out everything in main
//If you want to calculate all possible game configurations, run the third line in main
int main() {
    Board chessBoard;
    CalculateMoves moveCalc(chessBoard);
    std::cout<<moveCalc.SumOfAllMoves(1)<<std::endl;
    // chessBoard.PrintBoard();
    // while(true) {
    //     int x, y, xNew, yNew;
    //     std::cin >> x >> y >> xNew >> yNew;
    //     std::set<std::pair<int, int>> legalMoves = moveCalc.CalculatePieceMove({x, y}); 
    //     std::cout<<"Available moves: "<<std::endl;
    //     for(auto it : legalMoves) {      //Print out all possible moves for the specific piece
    //         std::cout<<it.first<<" "<<it.second<<std::endl;
    //     }       
    //     if(legalMoves.count({xNew, yNew})) {
    //         MakeMove(chessBoard, {x, y}, {xNew, yNew});
    //     }
    //     else {
    //         std::cout<<"Illegal move!"<<std::endl;
    //     }
    // }
}
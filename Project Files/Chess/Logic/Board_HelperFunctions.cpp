#include "Board.hpp"

//Prints the board to console, using unicode charachters
void Board::PrintBoard()
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != Empty)
            {
                std::cout << ConvertToUnicode(board[i][j]);
            }
            else{
                std::cout << (((i+j)%2) ? "\u25A1" : "\u25A0");
            }
        }
        std::cout << std::endl;
    }
}

//Checks if a square is empty
bool Board::IsEmpty(square pos){
    return board[pos.first][pos.second] == Empty;
}

//Removes a piece from the board
void Board::RemovePiece(square pos){
    board[pos.first][pos.second] = Empty;
}

//Moves a piece on the board from origin to destination
void Board::MakeMove(square origin, square destination){
    Move currentMove;
    currentMove.origin = origin;
    currentMove.destination = destination;
    currentMove.capturedPiece = board[destination.first][destination.second];
    board[destination.first][destination.second] = board[origin.first][origin.second];
    RemovePiece(origin);
    moveStack.push(currentMove);
    return;
}

void Board::UnmakeMove() {
    Move currentMove = moveStack.top();
    board[currentMove.origin.first][currentMove.origin.second] = board[currentMove.destination.first][currentMove.destination.second];
    board[currentMove.destination.first][currentMove.destination.second] = currentMove.capturedPiece;
    moveStack.pop();
}

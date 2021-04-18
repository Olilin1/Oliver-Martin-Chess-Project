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

void Board::RemovePiece(square pos){
    board[pos.first][pos.second] = Empty;
}
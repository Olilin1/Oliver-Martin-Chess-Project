#include "Board.hpp"

Board::Board(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = Empty;
        }
    }
}

Piece& Board::operator[](square pos){
    return board[pos.first][pos.second];
}
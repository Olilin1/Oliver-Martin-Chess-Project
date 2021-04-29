#include "Board.hpp"

//Standard constructor just sets all squares to empty
Board::Board(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = Empty;
        }
    }
    return;
}

//Allows us to use board[pair] instead of board.board[pair.first][pair.second]
Piece& Board::operator[](square pos){
    return board[pos.first][pos.second];
}
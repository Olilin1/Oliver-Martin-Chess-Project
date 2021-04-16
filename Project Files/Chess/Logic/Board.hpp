#ifndef BOARD
#define BOARD

#include"Enums.hpp"
#include"Typedefs.hpp"

//Simple class that allows us to use board[pos] instead of board[pos.first][pos.second]
class Board{
    private:
    Piece board[8][8];

    public:
    Board();
    Piece& operator[](square);

};

#endif
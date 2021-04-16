#ifndef BOARD
#define BOARD

#include"Enums.hpp"
#include"Typedefs.hpp"

class Board{
    private:
    Piece board[8][8];

    public:
    Board();
    Piece& operator[](square);

};

#endif
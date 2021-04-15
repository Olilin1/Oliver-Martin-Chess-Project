#ifndef GAME
#define GAME

#include"Enums.hpp"
#include"GameState.h"
#include<utility>

typedef std::pair<int, int> square;

class Game{
private:
    Piece board[8][8];
    GameState gameState;

public:
    Game();
    void MakeMove(square origin, square destination);

};

#endif
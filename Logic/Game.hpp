#ifndef GAME
#define GAME

#include"Enums.hpp"
#include"GameState.h"

class Game{
private:
    Piece board[8][8];
    GameState gameState;

public:
    Game();

};

#endif
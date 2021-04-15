#ifndef GAME
#define GAME

#include"Enums.hpp"
#include"GameState.h"
#include"Typedefs.hpp"
#include<utility>
#include<set>
#include<vector>
#include<string>
#include<sstream>



class Game{
private:
    Piece board[8][8];
    GameState gameState;

public:
    Game();
    void SetupGame(std::string fen);
    void MakeMove(square origin, square destination);
    std::set<square> AvailableMoves(square origin);
    bool IsLegal(square origin, square destination);

};

#endif
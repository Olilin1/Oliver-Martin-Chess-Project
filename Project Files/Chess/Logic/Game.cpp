#include "Game.hpp"

//Just initialises the game
Game::Game(){
    SetupGame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

}

Board Game::getBoard(){
    return board;
}

int main() {
    Game g;
    std::cout<<g.SumOfAllMoves(3)<<std::endl;
}
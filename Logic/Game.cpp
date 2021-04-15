#include "Game.hpp"

void Game::SetupGame(std::string fen){
    int row = 7, col = 0; //Fenwick notation starts placing pieces from the 8th row
    std::stringstream ss(fen);
    std::string placement, color, castling, enPassant, halfMove, fullMove;


}
#include "Game.hpp"

square Game::AlgebraicToSquare(std::string s){
    int row, col;
    row = s[1]-'0';
    col = s[0]-'a';
    return {row, col};
}

bool Game::isBlackPiece(Piece p){
    return p < 0;
}

bool Game::isWhitePiece(Piece p){
    return p > 0;
}
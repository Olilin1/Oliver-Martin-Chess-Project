#include"Game.hpp"

bool Game::CanGoTo(square origin, square destination){
    if(!IsEmpty(destination) && SameSidePieces(board[origin.first][origin.second], board[destination.first][destination.second])) return false;
    

}
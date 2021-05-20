#include "Game.hpp"

//Will check if the game is over or not.
bool Game::GameIsOver(){
    std::set<std::pair<int,int>> moves;
    MakeAllLegalMoves(moves);
    if(moves.empty()){
        if(IsAttacked(CurrPlayerKingPostion())){    //Checkmate
            gameState.winner = oppositePlayer();
        }
        else{       //Stalemate
            gameState.winner = None;
        }
        return true;
    }
    else{
        return false;
    }
}

Player Game::getWinner(){
    return gameState.winner;
}
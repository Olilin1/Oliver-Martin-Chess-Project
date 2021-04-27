#include "Game.hpp"

bool Game::gameIsOver(){
    if(CalculateAllMoves().empty()){
        if(board.IsAttacked(CurrPlayerKingPostion(), oppositePlayer(gameState.currentPlayer))){
            gameState.winner = oppositePlayer(gameState.currentPlayer);
        }
        return true;
    }
    else{
        return false;
    }
}
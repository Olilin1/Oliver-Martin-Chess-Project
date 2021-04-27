#include "Game.hpp"

bool Game::gameIsOver(){
    std::set<std::pair<square,square>> moves;
    CalculateAllMoves(moves);
    if(moves.empty()){
        if(board.IsAttacked(CurrPlayerKingPostion(), oppositePlayer(gameState.currentPlayer))){
            gameState.winner = oppositePlayer(gameState.currentPlayer);
        }
        return true;
    }
    else{
        return false;
    }
}
#include"Game.hpp"

float Game::evaluatePosition(){
    float score = 0;

    if(gameIsOver()){
        return inf * gameState.winner;
    }

    int mult;
    for(int i = 0; i< 8; i++){
        for(int j = 0; j<8; j++){
            mult = pieceColor(board[{i,j}]);
            switch (pieceType(board[{i,j}]))
            {
            case Knight:
                score += 3*mult;
                break;
            case Bishop:
                score += 3*mult;
                break;
            case Rook:
                score += 5*mult;
                break;
            case Queen:
                score += 9*mult;
                break;
            case Pawn:
                score += 1*mult;
                break;
            case King:
                break;
            default:
                break;
            }
        }
    }
    return score;
}
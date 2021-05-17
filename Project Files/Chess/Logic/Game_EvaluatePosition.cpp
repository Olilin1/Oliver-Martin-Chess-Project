#include"Game.hpp"

float Game::evaluatePosition(){
    float score = 0;

    if(GameIsOver()){
        return inf * gameState.winner;
    }

    int mult;
    for(int i = 0; i< 64; i++){
            mult = pieceColor(Board[i]);
            switch (Board[i])
            {
            case BlackKnight:
            case WhiteKnight:
            case WhiteBishop:
            case BlackBishop:
                score += 3*mult;
                break;
            case BlackRook:
            case WhiteRook:
                score += 5*mult;
                break;
            case WhiteQueen:
            case BlackQueen:
                score += 9*mult;
                break;
            case BlackPawn:
            case WhitePawn:
                score += 1*mult;
                break;
            case WhiteKing:
            case BlackKing:
                break;
            default:
                break;
        }
    }
    return score;
}

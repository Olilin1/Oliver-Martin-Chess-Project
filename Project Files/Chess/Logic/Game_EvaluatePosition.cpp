#include"Game.hpp"

int Game::evaluatePosition(){
    int score = 0;

    if(GameIsOver()){
        return inf * gameState.winner;
    }
    //Setting the value of bishops and knights a bit above 3 pawn values avoids the AI exchanging one of these pieces for three pawns (Generally this is a bad thing to do)
    for(int i = 0; i< 64; i++){
            switch (Board[i])
            {
            case BlackBishop:
                score -= (340 + bishopPieceSquareTable[63-i]);
                break;
            case WhiteBishop:       //Bishop is a bit higher than knight because it's beneficial to have a pair of bishops and the AI should prioritize that over a pair of knights
                score += 340 + bishopPieceSquareTable[i];
                break;
            case BlackKnight:
                score -= (325 + knightPieceSquareTable[63-i]);
                break;
            case WhiteKnight:
                score += 325 + knightPieceSquareTable[i];
                break;
            case BlackRook:
                score -= (500 + rookPieceSquareTable[63-i]);
                break;
            case WhiteRook:
                score += 500 + rookPieceSquareTable[i];
                break;
            case BlackQueen:
                score -= (900 + queenPieceSquareTable[63-i]);
                break;
            case WhiteQueen:
                score += 900 + queenPieceSquareTable[i];
                break;
            case BlackPawn:
                score -= (100 + pawnPieceSquareTable[63-i]);
                break;
            case WhitePawn:
                score += 100 + pawnPieceSquareTable[i];
                break;
            case BlackKing:
                score -= (10000 + kingPieceSquareTable[63-i]);    //it is assumed that kings will always be on the board, but when they are not, the opponent should always make the move resulting in that
                break;
            case WhiteKing:
                score += 10000 + kingPieceSquareTable[i];
                break;
            default:
                break;
        }
    }
    return score;
}

int Game::PieceValue(int p){
    switch (p)
    {
    case BlackBishop:
    case WhiteBishop:
        return 340;
    case BlackKnight:
    case WhiteKnight:
        return 325;
        break;
    case BlackRook:
    case WhiteRook:
        return 500;
    case BlackQueen:
    case WhiteQueen:
        return 900;
    case BlackPawn:
    case WhitePawn:
        return 100;
        break;
    case BlackKing:
    case WhiteKing:
        return 10000;
        break;
    default:
        return 0;
        break;
}
}

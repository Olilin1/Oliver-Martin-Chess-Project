#include "Game.hpp"

void Game::AiMove(){
    int depth = 3;
    float maxEval = (depth+1) * inf + 1;
    float beta = maxEval;
    float alpha = -maxEval;
    float eval;
    
    std::pair<int,int> bestMove;
    Piece promotion;

    std::set<std::pair<int, int>> allMoves;
    MakeAllPseudoMoves(allMoves);
    for(auto move : allMoves){
        if(gameState.awaitingPromotion){
            for(auto p : {Queen,Knight,Rook,Bishop}){
                Piece promotionPiece = ConvertToOppositeColoredPiece(p);
                MakeBoardMove(-1, -1, promotionPiece);
                eval = -miniMax(depth,-beta,-alpha);
                if(eval > alpha){
                    alpha = eval;
                    bestMove = move;
                    promotion = promotionPiece;
                }
                gameState.awaitingPromotion = true;
            }
            gameState.awaitingPromotion = false;
        }
        else if(MakeGameMove(move.first,move.second)){
            eval = -miniMax(depth-1,-beta,-alpha);
            if(eval > alpha){
                alpha = eval;
                bestMove = move;
            }
            UnmakeMove();
        }
    }

    MakeGameMove(bestMove.first,bestMove.second);
    if(gameState.awaitingPromotion){
        MakeBoardMove(-1, -1, promotion);
    }
}

float Game::miniMax(int depth, float alpha, float beta){
    float maxEval = depth * inf + 1;
    float eval;
    if(depth == 0) return evaluatePosition()*(depth+1) * gameState.currentPlayer;

    if(beta > maxEval){
        beta = maxEval;
        if(alpha >= beta) return beta; //No possible moves within [alpha:beta] window
    }

    bool madeMove = false;
    std::set<std::pair<int,int>> allMoves;
    MakeAllPseudoMoves(allMoves);
    for(auto move : allMoves){
        
        if(gameState.awaitingPromotion){
            madeMove = true;
            for(auto p : {Queen,Knight,Rook,Bishop}){
                MakeBoardMove(-1, -1, ConvertToOppositeColoredPiece(p));
                eval = -miniMax(depth,-beta,-alpha);
                if (eval >= beta){
                    return eval;
                }
                if(eval > alpha) alpha = eval;
                gameState.awaitingPromotion = true;
            }
            gameState.awaitingPromotion = false;
        }
        else if(MakeGameMove(move.first,move.second)){
            madeMove = true;
            eval = -miniMax(depth-1,-beta,-alpha);
            if (eval >= beta){
                UnmakeMove();
                return eval;
            }
            if(eval > alpha) alpha = eval;
            UnmakeMove();
        }
    }
    if(madeMove){
        return alpha;
    }
    else return evaluatePosition()*(depth+1) * gameState.currentPlayer;
}

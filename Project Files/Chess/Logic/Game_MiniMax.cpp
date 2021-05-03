#include "Game.hpp"

void Game::AiMove(){
    int depth = 3;
    float maxEval = (depth+1) * inf + 1;
    float beta = maxEval;
    float alpha = -maxEval;
    float eval;
    
    std::pair<square,square> bestMove;
    Piece promotion;

    //TODO: FIX!
    if(gameState.awaitingPromotion){
        for(auto p : neutralPromotions){
            Game g(*this);
            g.MakeMove({-1,-1},{-1,-1}, p);
            eval = -g.miniMax(depth);
            if (eval > maxEval){
                maxEval = eval;
                promotion = p;
            }
        }
        MakeMove({-1,-1},{-1,-1}, promotion);
        return;
    }


    std::set<std::pair<square,square>> allMoves;
    CalculateAllMoves(allMoves);
    for(auto move : allMoves){
        Game g(*this);
        g.MakeMove(move.first,move.second);
        eval = -g.miniMax(depth-1,-beta,-alpha);
        if (eval > beta){
            bestMove = move;
            break;
        }
        if(eval > alpha){
            alpha = eval;
            bestMove = move;
        }
    }
    MakeMove(bestMove.first,bestMove.second);
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
    std::set<std::pair<square,square>> allMoves;
    CalculateAllMoves(allMoves);
    for(auto move : allMoves){
        madeMove = true;
        Game g(*this);
        g.MakeMove(move.first,move.second);


        if(gameState.awaitingPromotion){
            for(auto p : neutralPromotions){
                Game g2(g);
                g2.MakeMove({-1,-1},{-1,-1}, p);
                eval = -g2.miniMax(depth,-beta,-alpha);
                if (eval >= beta){
                    return eval;
                }
                if(eval > alpha) alpha = eval;
            }   
        }
        else{
            eval = -g.miniMax(depth-1,-beta,-alpha);
            if (eval >= beta){
                return eval;
            }
            if(eval > alpha) alpha = eval;
        }
    }
    if(madeMove){
        return alpha;
    }
    else return evaluatePosition()*(depth+1) * gameState.currentPlayer;
}
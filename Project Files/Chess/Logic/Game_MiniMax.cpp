#include "Game.hpp"

void Game::AiMove(int depth){
    float maxEval = (depth+1) * -inf + 1;
    float eval;
    std::pair<square,square> bestMove;
    Piece promotion;

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
        eval = -g.miniMax(depth-1);
        if (eval > maxEval){
            maxEval = eval;
            bestMove = move;
        }
    }
    MakeMove(bestMove.first,bestMove.second);
}

float Game::miniMax(int depth, float alpha, float beta){
    float maxEval = depth * -inf + 1;
    float eval;
    if(depth == 0) return evaluatePosition()*(depth+1) * gameState.currentPlayer;

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
                eval = -g2.miniMax(depth);
                if (eval > maxEval){
                    maxEval = eval;
                }
            }   
        }
        else{
            float eval = -g.miniMax(depth-1);
            if (eval > maxEval){
                maxEval = eval;
            }
        }
    }
    if(madeMove){
        return maxEval;
    }
    else return evaluatePosition()*(depth+1) * gameState.currentPlayer;
}
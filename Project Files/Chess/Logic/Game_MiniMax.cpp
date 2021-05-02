#include "Game.hpp"

void Game::AiMove(int depth){
    float maxEval = (gameState.currentPlayer == White ? -inf : inf);
    float eval;
    std::pair<square,square> bestMove;
    Piece promotion;

    if(gameState.awaitingPromotion){
        for(auto p : neutralPromotions){
            Game g(*this);
            g.MakeMove({-1,-1},{-1,-1}, p);
            eval = g.miniMax(depth);
            if (gameState.currentPlayer == White && eval >= maxEval){
                promotion = p;
                maxEval = eval;
            }
            else if(gameState.currentPlayer == Black && eval <= maxEval){
                promotion = p;
                maxEval = eval;
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
        eval = g.miniMax(depth-1);
        if (gameState.currentPlayer == White && eval >= maxEval){
            maxEval = eval;
            bestMove = move;
        }
        else if(gameState.currentPlayer == Black && eval <= maxEval){
            maxEval = eval;
            bestMove = move;
        }
    }
    MakeMove(bestMove.first,bestMove.second);
}

float Game::miniMax(int depth, float alpha, float beta){
    float maxEval = (gameState.currentPlayer == White ? -inf : inf);
    float eval;
    if(gameState.awaitingPromotion){
        for(auto p : neutralPromotions){
            Game g(*this);
            g.MakeMove({-1,-1},{-1,-1}, p);
            eval = g.miniMax(depth);
            if (gameState.currentPlayer == White && eval >= maxEval){
                maxEval = eval;
            }
            else if(gameState.currentPlayer == Black && eval <= maxEval){
                maxEval = eval;
            }
            
        }
        return maxEval;
    }
    
    if(depth == 0) return evaluatePosition()*(depth+1);

    bool madeMove = false;
    std::set<std::pair<square,square>> allMoves;
    CalculateAllMoves(allMoves);
    for(auto move : allMoves){
        madeMove = true;
        Game g(*this);
        g.MakeMove(move.first,move.second);
        float eval = g.miniMax(depth-1);
        if (gameState.currentPlayer == White && eval >= maxEval){
            maxEval = eval;
        }
        else if(gameState.currentPlayer == Black && eval <= maxEval){
            maxEval = eval;
        }
    }
    if(madeMove){
        return maxEval;
    }
    else return evaluatePosition()*(depth+1);
}
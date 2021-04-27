#include "Game.hpp"

long long int Game::SumOfAllMoves(int depth) {

    if(gameState.awaitingPromotion){
        long long int ans = 0;
        if(gameState.currentPlayer == Black){
            for(auto p : blackPromotions){
                Game g(*this);
                g.MakeMove({-1,-1},{-1,-1}, p);
                ans += g.SumOfAllMoves(depth);
            }
        }
        else{
            for(auto p : whitePromotions){
                Game g(*this);
                g.MakeMove({-1,-1},{-1,-1}, p);
                ans += g.SumOfAllMoves(depth);
            }
        }
        return ans;
    }

    if(depth == 0) return 1;

    long long int ans = 0;
    for(auto move : CalculateAllMoves()){
        Game g(*this);
        g.MakeMove(move.first,move.second);
        ans += g.SumOfAllMoves(depth-1);
    }

    return ans;
}

std::set<std::pair<square,square>> Game::CalculateAllMoves(){
    std::set<std::pair<square,square>> allMoves;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            for(auto dest : LegalMoves({i,j})){
                
                allMoves.insert({{i,j},dest});
            }
        }
    }
    return allMoves;
}
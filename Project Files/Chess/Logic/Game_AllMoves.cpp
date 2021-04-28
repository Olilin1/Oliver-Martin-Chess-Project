#include "Game.hpp"

long long int Game::SumOfAllMoves(int depth) {

    
    if(gameState.awaitingPromotion){
        long long int ans = 0;
        for(auto p : neutralPromotions){
            Game g(*this);
            g.MakeMove({-1,-1},{-1,-1}, p);
            ans += g.SumOfAllMoves(depth);
        }
    
        return ans;
    }

    
    if(depth == 0) return 1;

    long long int ans = 0;
    long long int t;
    std::set<std::pair<square,square>> allMoves;
    CalculateAllMoves(allMoves);
    for(auto move : allMoves){
        Game g(*this);
        g.MakeMove(move.first,move.second);
        t = g.SumOfAllMoves(depth-1);
        /*if(depth == 2){
            std::cout << SquareToAlgebraic(move.first) << SquareToAlgebraic(move.second) << ' '<<t << std::endl;
        }*/
        ans+=t;
    }
    return ans;
}

void Game::CalculateAllMoves(std::set<std::pair<square,square>>& allMoves){
    

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            std::set<square> moves;
            LegalMoves({i,j}, moves);
            for(auto dest : moves){
                allMoves.insert({{i,j},dest});
            }
        }
    }
    return;
}
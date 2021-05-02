#include "Game.hpp"

//Calculates the total number of (non-unique) positions at a certain depth
long long int Game::SumOfAllMoves(int depth) {    
    if(gameState.awaitingPromotion){
        long long int ans = 0;
        for(auto p : neutralPromotions){
            MakeMove({-1,-1},{-1,-1}, p);
            ans += SumOfAllMoves(depth);
            UnmakeMove();
        }
    
        return ans;
    }
    
    if(depth == 0) return 1;

    long long int ans = 0;
    long long int t;
    std::set<std::pair<square,square>> allMoves;
    CalculateAllMoves(allMoves);
    for(auto move : allMoves){
        MakeMove(move.first,move.second);
        t = SumOfAllMoves(depth-1);
        UnmakeMove();
        ans+=t;
        /*
        //Allows a trace of the stack similar to stockfish
        if(depth == 2){
            std::cout << SquareToAlgebraic(move.first) << SquareToAlgebraic(move.second) << ' '<<t << std::endl;
        }
        */
        
    }
    return ans;
}

//All moves will contain the origin and destination of all possible moves currently available
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

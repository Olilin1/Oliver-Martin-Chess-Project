#include"Game.hpp"

//Calculates the total number of (non-unique) positions at a certain depth
uint64_t Game::SumOfAllMoves(int depth, bool perftAnalysis) {   
    if(gameState.awaitingPromotion){
        uint64_t ans = 0;
        for(auto p : {Queen,Knight,Rook,Bishop}){   //ORDER IS IMPORTANT!!!!!!!!!!!!!!  DO NOT CHANGE WIHTOUT VERY GOOD REASON
            MakeBoardMove(-1, -1, ConvertToOppositeColoredPiece(p));    //Note that player side is changed before promotion is done, so the piece has to be reversed
            ans += SumOfAllMoves(depth, false);
            gameState.awaitingPromotion = true;
        }
        gameState.awaitingPromotion = false;
        return ans;
    }

    if(depth == 0) return 1;

    std::set<std::pair<int, int>> allMoves;
    MakeAllPseudoMoves(allMoves);
    uint64_t ans = 0;
    uint64_t t;
    for(auto move : allMoves){
        if(MakeGameMove(move.first, move.second)){
            t = SumOfAllMoves(depth-1, false);
            ans+=t; 
            UnmakeMove();

             //Allows a trace of the stack similar to stockfish
            if(perftAnalysis){
                std::cout << SquareToAlgebraic(move.first) << SquareToAlgebraic(move.second) << ": "<<t << std::endl;
            }
        }
    }
    return ans;
}

void Game::MakeAllPseudoMoves(std::set<std::pair<int, int>>& allMoves){ 
    GeneratePawnAttackSet(allMoves);
    GenerateRookAttackSet(allMoves);
    GenerateKnightAttackSet(allMoves);
    GenerateBishopAttackSet(allMoves);
    GenerateQueenAttackSet(allMoves);
    GenerateKingAttackSet(allMoves);
}

void Game::MakeAllLegalMoves(std::set<std::pair<int, int>>& allMoves){
    std::set<std::pair<int, int>> allPseudoMoves;
    MakeAllPseudoMoves(allPseudoMoves);
    for(auto move : allPseudoMoves){
        if(MakeGameMove(move.first, move.second)){
            allMoves.insert(move);
            UnmakeMove();
        }
    }
}

void Game::MakeAllLegalMovesFromSquare(std::set<int>& allMoves, int square){
    std::set<std::pair<int, int>> allLegalMoves;
    MakeAllLegalMoves(allLegalMoves);
    for(auto move : allLegalMoves){
        if(move.first == square){
            allMoves.insert(move.second);
        }
    }
}

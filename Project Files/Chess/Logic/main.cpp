#include"Game.hpp"
#include"Bitboard.hpp"
#include"Tests.hpp"
#include<bitset>
#include<iostream>
#include <sstream>      // std::stringstream
#include <ctime>

//(Note) I haven't ran this method, but I have ran each separate test separately and gotten the correct results
//These tests might fail because I output the results in the wrong way but it should be easy to fix that
void runTests(int depth){
    for(test t : tests){
        
        clock_t tStart = clock();
        Game* g = new Game();
        g->SetupGame(t.fen);
        std::cout << "Running test: " << t.testName << std::endl;
        for(int i = 0; i <= depth; i++){
            int ans = g->SumOfAllMoves(i, false);
            if(ans == t.expected[i]){
                std::cout << t.testName << " depth " << i << " PASS"<<std::endl;
                //printf("Time taken: %.2fm\n", ((double)(clock() - tStart) / CLOCKS_PER_SEC)/60);
            }
            else{
                std::cout << t.testName << " depth " << i << " FAIL"<< "expected " << t.expected[i] << " but got "<<ans <<std::endl;
                //printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
            }
        }
        std::cout << std::endl;
        delete g;
    }
}

/*Copy line below to run in terminal (at least on mac you have to do this...)
g++ main.cpp Bitboard.cpp Game\_GenerateBlockerMoves.cpp Game\_MagicNumberGeneration.cpp Game\_KingKnightMoves.cpp Game\_GeneratePseudoMoves.cpp Game\_InitializeGame.cpp Game\_HelperFunctions.cpp Game\_MakeLegalMove.cpp Game\_MakeAllMoves.cpp Game\_GenerateAttackSets.cpp Game\_Minimax.cpp Game\_EvaluatePosition.cpp Game\_IsOver.cpp -std=c++17
*/

int main() {
    Game* g = new Game();
    g->SetupGame("rnbqkbnr/2pppppp/8/8/p7/p7/PPPPPPPP/1RBQKBNR w Kkq - 0 1");
    std::cout << g->SumOfAllMoves(3, false);
}
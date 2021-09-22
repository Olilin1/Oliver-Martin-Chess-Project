#include"Game.hpp"
#include"Bitboard.hpp"
#include"Tests.hpp"
#include<bitset>
#include<iostream>
#include <sstream>      // std::stringstream
#include <ctime>

/*Copy line below to run in terminal (at least on mac you have to do this...)
g++ main.cpp Bitboard.cpp Game\_GenerateBlockerMoves.cpp Game\_MagicNumberGeneration.cpp Game\_KingKnightMoves.cpp Game\_GeneratePseudoMoves.cpp Game\_InitializeGame.cpp Game\_HelperFunctions.cpp Game\_MakeLegalMove.cpp Game\_MakeAllMoves.cpp Game\_GenerateAttackSets.cpp Game\_Minimax.cpp Game\_EvaluatePosition.cpp Game\_IsOver.cpp -std=c++17
or "g++ *.cpp" should also work
*/

int main() {
    Game* g = new Game();
    g->SetupGame("rnbqkbnr/2pppppp/8/8/p7/p7/PPPPPPPP/1RBQKBNR w Kkq - 0 1");
    std::cout << g->SumOfAllMoves(3, false);
}
#include"Game.hpp"
#include"Bitboard.hpp"
#include"Tests.hpp"
#include<bitset>
#include<iostream>
#include <sstream>      // std::stringstream
#include <ctime>
#include<thread>

/*Copy line below to run in terminal (at least on mac you have to do this...)
g++ main.cpp Bitboard.cpp Game\_GenerateBlockerMoves.cpp Game\_MagicNumberGeneration.cpp Game\_KingKnightMoves.cpp Game\_GeneratePseudoMoves.cpp Game\_InitializeGame.cpp Game\_HelperFunctions.cpp Game\_MakeLegalMove.cpp Game\_MakeAllMoves.cpp Game\_GenerateAttackSets.cpp Game\_Minimax.cpp Game\_EvaluatePosition.cpp Game\_IsOver.cpp -std=c++17
or "g++ *.cpp" should also work
*/


using namespace std;
int main() {
    Game* g = new Game;
    for(int i = 0; i < 10; i++){
    cout << g->SquareToAlgebraic(i) << endl;
}
}
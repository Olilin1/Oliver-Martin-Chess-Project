#include"Game.hpp"
#include<time.h>

using namespace std;
int main() {
    Game g;
    g.SetupGame("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

    clock_t tStart = clock();
    cout << g.SumOfAllMoves(3)<<endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
   

    
}
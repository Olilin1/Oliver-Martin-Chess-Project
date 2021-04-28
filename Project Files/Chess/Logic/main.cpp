#include"Game.hpp"
#include<time.h>

using namespace std;
int main() {
    Game g;
    g.SetupGame("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
    for(int i = 1; i <= 10; i++){
    clock_t tStart = clock();
    cout << g.SumOfAllMoves(i)<<endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    }
    
}
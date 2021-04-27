#include"Game.hpp"

using namespace std;
int main() {
    Game g;
    g.SetupGame("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

    for(int i = 1; i<10; i++){
    cout << g.SumOfAllMoves(i)<<endl;
    }
    
}
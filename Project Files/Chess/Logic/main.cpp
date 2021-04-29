#include<iostream>
#include<time.h>
#include"Game.hpp"
#include"Tests.hpp"

using namespace std;

void runTests(int depth){

    for(test t : tests){
        
        clock_t tStart = clock();
        Game g;
        g.SetupGame(t.fen);
        cout << "Running test: " << t.testName << endl;
        for(int i = 0; i <= depth; i++){
            int ans = g.SumOfAllMoves(i);
            if(ans == t.expected[i]){
                cout << t.testName << " depth " << i << " PASS"<<endl;
                //printf("Time taken: %.2fm\n", ((double)(clock() - tStart) / CLOCKS_PER_SEC)/60);
            }
            else{
                cout << t.testName << " depth " << i << " FAIL"<< "expected " << t.expected[i] << " but got "<<ans <<endl;
                //printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
            }
        }
        cout << endl;
    }
}

int main() {
    runTests(4);
}
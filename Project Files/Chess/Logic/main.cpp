#include<iostream>
#include"Game.hpp"
#include"Tests.hpp"

using namespace std;

void runTests(int depth){

    for(test t : tests){
        Game g;
        g.SetupGame(t.fen);
        cout << "Running test: " << t.testName << endl;
        for(int i = 0; i <= depth; i++){
            int ans = g.SumOfAllMoves(i);
            if(ans == t.expected[i]){
                cout << t.testName << " depth " << i << " PASS"<<endl; 
            }
            else{
                cout << t.testName << " depth " << i << " FAIL"<< "expected " << t.expected[i] << " but got "<<ans <<endl; 
            }
        }
        cout << endl;
    }
}

int main() {
    runTests(4);
}
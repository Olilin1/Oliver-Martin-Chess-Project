#include"Game.hpp"


int main() {
    Game g;
    std::string s;
    int x1, x2, x3, x4;
    g.PrintBoard();
    while(true){
        
        std::cin >> x1 >> x2 >> x3 >> x4;
        if(g.MakeMove({x1,x2},{x3,x4})){
            g.PrintBoard();
        }
        else{
            std::cout << "ILLEGAL MOVE!\n";
            for(auto a : g.LegalMoves({x1,x2})){
                std::cout << a.first << ' ' << a.second << '\n';
            }
        }
    }
}
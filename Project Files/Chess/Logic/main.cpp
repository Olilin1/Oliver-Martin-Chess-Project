#include"Game.hpp"


int main() {
    Game g;
    std::string s;
    
    while(true){
        std::getline(std::cin, s);
        g.SetupGame(s);
        g.PrintBoard();
    }
}
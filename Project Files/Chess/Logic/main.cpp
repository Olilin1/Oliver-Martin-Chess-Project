#include"Game.hpp"
#include"Bitboard.hpp"
#include"Tests.hpp"
#include<bitset>
#include<iostream>
#include <sstream>      // std::stringstream
#include <ctime>


template<typename T>
static std::string toBinaryString(const T& x)
{
    std::stringstream ss;
    ss << std::bitset<sizeof(T) * 8>(x);
    return ss.str();
}

int main() {
    Game game;
    Tests test;
    std::clock_t start = std::clock();
    int sum = game.SumOfAllMoves(5, true);
    std::cout<<std::endl<<"Nodes searched: "<<sum<<std::endl;
    float time = ((std::clock()-start)/(double)CLOCKS_PER_SEC);
    std::cout<<time<<" seconds elapsed"<<std::endl;
    std::cout<<"Nodes/seconds: "<<sum/time<<std::endl;
    return 0;
}
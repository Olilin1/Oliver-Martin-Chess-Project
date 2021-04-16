#ifndef CONSTANTS
#define CONSTANTS

#include<utility>
const std::vector<std::pair<int,int>> rookMoves = {{1,0},{-1,0},{0,-1},{0,1}};
const std::vector<std::pair<int,int>> bishopMoves = {{1,1},{1,-1},{-1,1},{-1,-1}};
const std::vector<std::pair<int,int>> queenMoves = {{1,1},{1,-1},{-1,1},{-1,-1},{1,0},{-1,0},{0,-1},{0,1}};

#endif
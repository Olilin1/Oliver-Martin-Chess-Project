#pragma once

#include<utility>
#include<vector>
#include "Enums.hpp"
const std::vector<std::pair<int,int>> rookMoves = {{1,0},{-1,0},{0,-1},{0,1}};
const std::vector<std::pair<int,int>> bishopMoves = {{1,1},{1,-1},{-1,1},{-1,-1}};
const std::vector<std::pair<int,int>> queenMoves = {{1,1},{1,-1},{-1,1},{-1,-1},{1,0},{-1,0},{0,-1},{0,1}};
const std::vector<Piece> blackPromotions = {BlackBishop,BlackKnight,BlackQueen,BlackRook};
const std::vector<Piece> whitePromotions = {WhiteBishop,WhiteKnight,WhiteQueen,WhiteRook};
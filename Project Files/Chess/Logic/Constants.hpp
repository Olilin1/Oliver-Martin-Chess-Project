#pragma once

#include<utility>
#include<vector>
#include "Enums.hpp"
#include"Typedefs.hpp"
const std::vector<std::pair<int,int>> rookMoves = {{1,0},{-1,0},{0,-1},{0,1}};
const std::vector<std::pair<int,int>> bishopMoves = {{1,1},{1,-1},{-1,1},{-1,-1}};
const std::vector<std::pair<int,int>> queenMoves = {{1,1},{1,-1},{-1,1},{-1,-1},{1,0},{-1,0},{0,-1},{0,1}};
const std::vector<Piece> blackPromotions = {BlackBishop,BlackKnight,BlackQueen,BlackRook};
const std::vector<Piece> whitePromotions = {WhiteBishop,WhiteKnight,WhiteQueen,WhiteRook};

const std::vector<Piece> neutralPromotions = {Queen,Knight,Rook,Bishop}; //ORDER IS IMPORTANT!!! DO NOT CHANGE WIHTOUT VERY GOOD REASON
const square nullSquare = {-1,-1};
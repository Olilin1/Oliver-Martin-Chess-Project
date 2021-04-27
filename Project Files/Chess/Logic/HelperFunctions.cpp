#include"HelperFunctions.hpp"

//Checks if a square is on the board
bool OnBoard(square pos){
    if(pos.first < 8 && pos.first >= 0 && pos.second < 8 && pos.second >= 0) {
            return true;
        }
     return false;
}

//Converts a piece to Unicode
std::string ConvertToUnicode(Piece i)
{
    switch (i)
    {
    case -1:
        return "\u2659";
    case -2:
        return "\u2656";
    case -3:
        return "\u2658";
    case -4:
        return "\u2657";
    case -5:
        return "\u2655";
    case -6:
        return "\u2654";
    case 1:
        return "\u265F";
    case 2:
        return "\u265C";
    case 3:
        return "\u265E";
    case 4:
        return "\u265D";
    case 5:
        return "\u265B";
    case 6:
        return "\u265A";
    default:
        return " ";
    }
}

//Gives the neutral piece type
Piece pieceType(Piece p){
    if(p >6) return p;
    return Piece(std::abs(p)+6);
}

//Returns the color of the opposite of p
Player oppositePlayer(Player p){
    if(p==White) return Black;
    if(p==Black) return White;
    return None;
}

//Checks if a piece is black
bool isBlackPiece(Piece p)
{
    return p < 0;
}

//Checks if a piece is white
bool isWhitePiece(Piece p)
{
    return (p > 0 && p < 7);
}

//Returns the color of a pice
Player pieceColor(Piece p){
    if (isBlackPiece(p)) return Black;
    else if (isWhitePiece(p)) return White;
    else return None;
}

//Takes a square in algebraic notation and gives it as a square
square AlgebraicToSquare(std::string s)
{
    int row, col;
    row = s[1] - '0';
    col = s[0] - 'a';
    return {row, col};
}

std::string SquareToAlgebraic(square s){
    char row = s.first + '1';
    char col = s.second + 'a';
    std::string ans = "  ";
    ans[0] = col;
    ans[1] = row;
    return ans;
}
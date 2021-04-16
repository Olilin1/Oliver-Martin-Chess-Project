#include "Game.hpp"

square Game::AlgebraicToSquare(std::string s)
{
    int row, col;
    row = s[1] - '0';
    col = s[0] - 'a';
    return {row, col};
}

bool Game::isBlackPiece(Piece p)
{
    return p < 0;
}

bool Game::isWhitePiece(Piece p)
{
    return p > 0;
}

std::string Game::ConvertToUnicode(Piece i)
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

void Game::PrintBoard()
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != Empty)
            {
                std::cout << ConvertToUnicode(board[i][j]);
            }
            else{
                std::cout << (((i+j)%2) ? "\u25A1" : "\u25A0");
            }
        }
        std::cout << std::endl;
    }
}

bool Game::OnBoard(square pos){
    if(pos.first <= 8 && pos.first >= 1 && pos.second <= 8 && pos.second >= 1) {
            return true;
        }
     return false;
}

bool Game::SameSidePieces(Piece a, Piece b){
    return !(a > 0 ^ b > 0);
}

bool Game::IsEmpty(square pos){
    return board[pos.first][pos.second] == Empty;
}

void Game::PlacePiece(square pos, Piece p){
    board[pos.first][pos.second] = p;
    if(isBlackPiece(p)) blackPieces[pos] = p;
    else if(isWhitePiece(p)) whitePieces[pos]=p;
}

void Game::RemovePiece(square pos){
    board[pos.first][pos.second] = Empty;
    blackPieces.erase(pos);
    whitePieces.erase(pos);
}
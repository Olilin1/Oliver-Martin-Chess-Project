#include "Game.hpp"

//Takes a square in algebraic notation and gives it as a square
square Game::AlgebraicToSquare(std::string s)
{
    int row, col;
    row = s[1] - '0';
    col = s[0] - 'a';
    return {row, col};
}

//Gets the square of the current players king
square Game::CurrPlayerKingPostion(){
    if(gameState.currentPlayer == Black) return gameState.blackKingPos;
    else if(gameState.currentPlayer == White) return gameState.whiteKingPos;
    else return {-1,-1};
}

bool Game::canMove(square pos){
    if(OnBoard(pos) && 
    (pieceColor(board[pos]) != gameState.currentPlayer)) 
    return true;
    else return false;
}

//Checks if a piece is black
bool Game::isBlackPiece(Piece p)
{
    return p < 0;
}

//Checks if a piece is white
bool Game::isWhitePiece(Piece p)
{
    return (p > 0 && p < 7);
}

//Returns the color of a pice
Player Game::pieceColor(Piece p){
    if (isBlackPiece(p)) return Black;
    else if (isWhitePiece(p)) return White;
    else return None;
}

//Returns the color of the opposite of p
Player Game::oppositePlayer(Player p){
    if(p==White) return Black;
    if(p==Black) return White;
    return None;
}

//Gives the neutral piece type
Piece Game::pieceType(Piece p){
    return Piece(std::abs(p)+6);
}

//Converts a piece to Unicode
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

//Prints the board to console, using unicode charachters
void Game::PrintBoard()
{
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[{i,j}] != Empty)
            {
                std::cout << ConvertToUnicode(board[{i,j}]);
            }
            else{
                std::cout << (((i+j)%2) ? "\u25A1" : "\u25A0");
            }
        }
        std::cout << std::endl;
    }
}

//Checks if a square is on the board
bool Game::OnBoard(square pos){
    if(pos.first < 8 && pos.first > 0 && pos.second < 8 && pos.second > 0) {
            return true;
        }
     return false;
}

//Checks if a square is empty
bool Game::IsEmpty(square pos){
    return board[pos] == Empty;
}

//Places a piece onto the board and adds it to the piece map
void Game::PlacePiece(square pos, Piece p){
    board[pos] = p;
    if(isBlackPiece(p)) blackPieces[pos] = p;
    else if(isWhitePiece(p)) whitePieces[pos]=p;
}

//Removes a piece from the board and removes it from the piece maps
void Game::RemovePiece(square pos){
    board[pos] = Empty;
    blackPieces.erase(pos);
    whitePieces.erase(pos);
}

bool Game::isLegal(square origin, square destination){
    if(!canMove(destination)) return false;
    Board newBoard = board;
    newBoard.MakeMove(origin, destination);
    return !(newBoard.IsAttacked(CurrPlayerKingPostion(), oppositePlayer(gameState.currentPlayer)));
}

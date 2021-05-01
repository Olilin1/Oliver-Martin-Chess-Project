#include "Game.hpp"



//Gets the square of the current players king
square Game::CurrPlayerKingPostion(){
    if(gameState.currentPlayer == Black) return gameState.blackKingPos;
    else if(gameState.currentPlayer == White) return gameState.whiteKingPos;
    else return {-1,-1};
}

//Makes sure that you can move to a square (i.e. it's not blocked by one of your own pieces)
bool Game::canMove(square pos){
    if(OnBoard(pos) && 
    (pieceColor(board[pos]) != gameState.currentPlayer)) 
    return true;
    else return false;
}

//Prints the board to console, using unicode charachters
void Game::PrintBoard()
{
    board.PrintBoard();
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

//Checks that a move doesn't leave you in check
bool Game::isLegal(square origin, square destination){
    if(!canMove(destination)) return false;
    Board newBoard = board;
    newBoard.MakeMove(origin, destination);
    return !newBoard.IsAttacked(CurrPlayerKingPostion(), oppositePlayer(gameState.currentPlayer));
}

//Returns wheter or not the game is waiting for a promotion to occur
bool Game::awaitingPromotion(){
    return gameState.awaitingPromotion;
}

//Converts a piece to equivalent piece of currentplayer color
Piece Game::toCurrPlayer(Piece p){
    p = pieceType(p);
    if(gameState.currentPlayer == White){
        p = Piece(p-6);
    }
    else{
        p = Piece(-(p-6));
    }
    return p;
}

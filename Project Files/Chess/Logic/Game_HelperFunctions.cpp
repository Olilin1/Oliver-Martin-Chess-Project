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

 //Checks that a move doesn't leave you in check
 bool Game::isLegal(square origin, square destination){
     if(!canMove(destination)) return false;
     board.MakeMove(origin, destination);
     bool isLegal =  !board.IsAttacked(CurrPlayerKingPostion(), oppositePlayer(gameState.currentPlayer));
     board.UnmakeMove();
     return isLegal;
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

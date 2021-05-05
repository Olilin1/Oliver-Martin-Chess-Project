 #include "Game.hpp"

 //Makes ref contain all legal moves from a square
 Bitboard Game::LegalMoves(int pos){
     Bitboard ref;
     if(gameState.awaitingPromotion) return ref;
     switch (pieceType(board[{pos/8, pos%8}]))
     {
     case Knight: {
         LegalKnightMoves(pos, ref);
         return ref;
     }
     case Queen: {
         Bitboard newBitboard;
         LegalRookMoves(pos, newBitboard);
         LegalBishopMoves(pos, ref);
         ref.bitBoard |= newBitboard.bitBoard;      //The queen moves is the intersection of the rook and bishop moves (intersection = OR operator)
         return ref;
     }
     case Rook: {
         LegalRookMoves(pos, ref);
         return ref;
     }

     case Bishop: {
         LegalBishopMoves(pos, ref);
         return ref;
     };
     case King: {
         LegalKingMoves(pos, ref);
         return ref;
     }

     case Pawn: {
         LegalPawnMoves(pos, ref);
         return ref;
     }
     default:
         return ref;
         break;
     }
 }

 void Game::LegalRookMoves(int pos, Bitboard& bitBoard){

 }

 void Game::LegalBishopMoves(int pos, Bitboard& bitBoard){

 }

 void Game::LegalKnightMoves(int pos, Bitboard& bitBoard){

 }

 void Game::LegalKingMoves(int pos, Bitboard& bitBoard){

 }

 void Game::LegalPawnMoves(int pos, Bitboard& bitBoard){

 }

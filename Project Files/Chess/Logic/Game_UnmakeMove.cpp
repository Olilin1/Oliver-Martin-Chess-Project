#include"Game.hpp"

//Unmakes the latest move made
void Game::UnmakeMove(){
    Move currentMove = moveStack.front();
    Piece movedPiece = board[currentMove.destination];

    gameState = currentMove.previousGameState;

    if(currentMove.Promotion) {
        board[currentMove.origin] = (movedPiece < 0) ? BlackPawn : WhitePawn;
        RemovePiece(gameState.promotion);
        return;
    }

    board[currentMove.destination] = currentMove.capturedPiece;
    MakeMove(currentMove.destination, currentMove.origin);
    if(currentMove.castledKingSide) {
        square RookPosition = {currentMove.destination.first, 5};
        square NewPosition = {currentMove.destination.first, 7};
        board.MakeMove(RookPosition, NewPosition);
    }
    else if(currentMove.castledQueenSide) {
        square RookPosition = {currentMove.destination.first, 3};
        square NewPosition = {currentMove.destination.first, 0};
        board.MakeMove(RookPosition, NewPosition);
    }
    else if(currentMove.enPassantMove) {
        square enPassantPosition = (movedPiece < 0) ? std::make_pair(currentMove.destination.first + 1, currentMove.destination.second) : std::make_pair(currentMove.destination.first - 1, currentMove.destination.second);
        board[enPassantPosition] = (movedPiece < 0) ? WhitePawn : BlackPawn;
    }
}

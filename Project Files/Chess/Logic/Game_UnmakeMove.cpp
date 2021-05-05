//#include"Game.hpp"

////Unmakes the latest move made
//void Game::UnmakeMove(){
//    if(moveStack.empty()) return;
//    Move currentMove = moveStack.top();
//    Piece movedPiece = board[currentMove.destination];

//    Player currentPlayer = (movedPiece < 0) ? Black : White;

//    gameState = currentMove.moveGameState;

//    if(currentMove.Promotion) {
//        board[currentMove.origin] = (currentPlayer == Black) ? BlackPawn : WhitePawn;
//        RemovePiece(gameState.promotion);
//        moveStack.pop();
//        return;
//    }

//    board.MakeMove(currentMove.destination, currentMove.origin);
//    board[currentMove.destination] = currentMove.capturedPiece;
//    if(currentMove.castledKingSide) {
//        square RookPosition = {currentMove.destination.first, 5};
//        square NewPosition = {currentMove.destination.first, 7};
//        board.MakeMove(RookPosition, NewPosition);
//    }
//    else if(currentMove.castledQueenSide) {
//        square RookPosition = {currentMove.destination.first, 3};
//        square NewPosition = {currentMove.destination.first, 0};
//        board.MakeMove(RookPosition, NewPosition);
//    }
//    else if(currentMove.enPassantMove) {
//        square enPassantPosition = gameState.enPassant;
//        board[enPassantPosition] = (currentPlayer == Black) ? WhitePawn : BlackPawn;
//    }
//    moveStack.pop();
//}

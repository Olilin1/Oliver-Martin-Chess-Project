#include "Game.hpp"

////Makes a move if it is legal and then returns true, if the move was illegal nothing happens and false is returned
//bool Game::MakeMove(square origin, square destination, Piece promotion){
//    Move currentMove;
//    currentMove.origin = origin;
//    currentMove.destination = destination;
//    currentMove.moveGameState = gameState;
//    currentMove.capturedPiece = board[destination];

//    if(gameState.awaitingPromotion){
//        if(promotion == Empty) return false;
//        gameState.currentPlayer = oppositePlayer(gameState.currentPlayer);
//        promotion = toCurrPlayer(promotion);
//        board[gameState.promotion] = promotion;
//        gameState.awaitingPromotion = false;
//        gameState.currentPlayer = oppositePlayer(gameState.currentPlayer);
//        currentMove.Promotion = true;
//        moveStack.push(currentMove);
//        return true;
//    }

//    gameState.awaitingPromotion = false;
//    bool enPassant = false;
//    if(board[destination] != Empty) gameState.halfMoveClock = 0;
//    switch (pieceType(board[origin]))
//    {
//    case Knight:
//        board.MakeMove(origin, destination);
//        break;
//    case Bishop:
//        board.MakeMove(origin, destination);
//    break;
//    case Queen:
//        board.MakeMove(origin, destination);
//    break;
//    case Rook:
//        board.MakeMove(origin, destination);
//    break;
//    case King:
    
//        if(origin.second - destination.second == 2){
//            currentMove.castledKingSide = true;
//            board.MakeMove(origin, destination);
//            board.MakeMove({origin.first, 0}, {origin.first, origin.second-1});
//        }
//        else if(origin.second - destination.second == -2){
//            currentMove.castledQueenSide = true;
//            board.MakeMove(origin, destination);
//            board.MakeMove({origin.first, 7}, {origin.first, origin.second+1});
//        }
//        else{
//            board.MakeMove(origin, destination);
//        }

//        if(gameState.currentPlayer ==White){
//            gameState.whiteCanCastleKingSide = false;
//            gameState.whiteCanCastleQueenSide = false;
//            gameState.whiteKingPos = destination;
//        }
//        else{
//            gameState.blackCanCastleKingSide = false;
//            gameState.blackCanCastleQueenSide = false;
//            gameState.blackKingPos = destination;
//        }
            
        
//    break;
//    case Pawn:
        

//        gameState.halfMoveClock = 0;
//        board.MakeMove(origin, destination);
//        if(abs(destination.first-origin.first) == 2){
//            enPassant = true;
//            gameState.enPassant = destination;
//        }
//        else if(gameState.canEnPassant){
//            int direction = (gameState.currentPlayer == White ? 1:-1);
//            if(gameState.enPassant == std::make_pair(destination.first-direction, destination.second)){
//                board.RemovePiece(gameState.enPassant);
//                currentMove.enPassantMove = true;
//            }
//        }
//        if(destination.first == 0 || destination.first == 7){
//            gameState.promotion = destination;
//            gameState.awaitingPromotion = true;
//        }
        
//    break;
//    default:
//        break;
//    }
  
//    gameState.halfMoveClock++;
//    if(gameState.currentPlayer == Black) gameState.fullMoveClock++;
//    gameState.currentPlayer = oppositePlayer(gameState.currentPlayer);
//    gameState.canEnPassant = enPassant;
//    if(destination == std::make_pair(0,0) || origin == std::make_pair(0,0)) gameState.whiteCanCastleQueenSide = false;
//    if(destination == std::make_pair(0,7) || origin == std::make_pair(0,7)) gameState.whiteCanCastleKingSide = false;
//    if(destination == std::make_pair(7,0) || origin == std::make_pair(7,0)) gameState.blackCanCastleQueenSide = false;
//    if(destination == std::make_pair(7,7) || origin == std::make_pair(7,7)) gameState.blackCanCastleKingSide = false;
//    moveStack.push(currentMove);
//    return true;
    
//}

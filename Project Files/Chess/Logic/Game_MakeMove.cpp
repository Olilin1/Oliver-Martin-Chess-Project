#include "Game.hpp"

bool Game::MakeMove(square origin, square destination, Piece promotion){
    bool wasLegal = false;
    bool enPassant = false;
    switch (pieceType(board[origin]))
    {
    case Knight:
        if(LegalKnightMoves(origin).count(destination)){
            if(board[destination] != Empty) gameState.halfMoveClock = 0;
            board.MakeMove(origin, destination);
            wasLegal = true;
        }
        break;
    case Bishop:
        if(LegalBishopMoves(origin).count(destination)){
            if(board[destination] != Empty) gameState.halfMoveClock = 0;
            board.MakeMove(origin, destination);
            wasLegal = true;
        }
    break;
    case Queen:
        if(LegalQueenMoves(origin).count(destination)){
            if(board[destination] != Empty) gameState.halfMoveClock = 0;
            board.MakeMove(origin, destination);
            wasLegal = true;
        }
    break;
    case Rook:
        if(LegalRookMoves(origin).count(destination)){
            if(board[destination] != Empty) gameState.halfMoveClock = 0;
            board.MakeMove(origin, destination);
            wasLegal = true;
        }
    break;
    case King:
        if(LegalKingMoves(origin).count(destination)){
            wasLegal = true;
            if(board[destination] != Empty)
            {
            gameState.halfMoveClock = 0;
            board.MakeMove(origin, destination);
            }
            else if(origin.second - destination.second == 2){
                board.MakeMove(origin, destination);
                board.MakeMove({origin.first, 0}, {origin.first, origin.second-1});
            }
            else if(origin.second - destination.second == -2){
                board.MakeMove(origin, destination);
                board.MakeMove({origin.first, 7}, {origin.first, origin.second+1});
            }

            if(pieceColor(board[origin]) ==White){
                gameState.whiteCanCastleKingSide = false;
                gameState.whiteCanCastleQueenSide = false;
            } 
            else{
                gameState.blackCanCastleKingSide = false;
                gameState.blackCanCastleQueenSide = false;
            }
        }
    break;
    case Pawn:
        if(LegalPawnMoves(origin).count(destination)){
            wasLegal = true;
            gameState.halfMoveClock = 0;
            board.MakeMove(origin, destination);
            if(abs(destination.second-origin.second) == 2){
                enPassant = true;
                gameState.enPassant = destination;
            }
            else if(gameState.canEnPassant){
                int direction = (gameState.currentPlayer == White ? 1:-1);
                if(gameState.enPassant == std::make_pair(destination.first-direction, destination.second)){
                    board.RemovePiece(gameState.enPassant);
                }
            }
        }
    break;
    default:
        break;
    }
    if(wasLegal){
        gameState.halfMoveClock++;
        if(gameState.currentPlayer == Black) gameState.fullMoveClock++;
        gameState.currentPlayer = oppositePlayer(gameState.currentPlayer);
        gameState.canEnPassant = enPassant;
        return true;
    }
    else{
        return false;
    }
}
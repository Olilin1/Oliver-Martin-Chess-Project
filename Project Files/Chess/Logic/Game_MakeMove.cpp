#include "Game.hpp"

bool Game::MakeMove(square origin, square destination, Piece promotion){

    bool enPassant = false;
    if(!LegalMoves(origin).count(destination)) return false;
    if(board[destination] != Empty) gameState.halfMoveClock = 0;
    switch (pieceType(board[origin]))
    {
    case Knight:
        board.MakeMove(origin, destination);
        break;
    case Bishop:
        board.MakeMove(origin, destination);     
    break;
    case Queen:
        board.MakeMove(origin, destination);
    break;
    case Rook:      
        board.MakeMove(origin, destination);
    break;
    case King:
    
        if(board[destination] != Empty)
        {
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
        else{
            board.MakeMove(origin, destination);
        }

        if(gameState.currentPlayer ==White){
            gameState.whiteCanCastleKingSide = false;
            gameState.whiteCanCastleQueenSide = false;
            gameState.whiteKingPos = destination;
        } 
        else{
            gameState.blackCanCastleKingSide = false;
            gameState.blackCanCastleQueenSide = false;
            gameState.blackKingPos = destination;
        }
            
        
    break;
    case Pawn:
        

        gameState.halfMoveClock = 0;
        board.MakeMove(origin, destination);
        if(abs(destination.first-origin.first) == 2){
            enPassant = true;
            gameState.enPassant = destination;
        }
        else if(gameState.canEnPassant){
            int direction = (gameState.currentPlayer == White ? 1:-1);
            if(gameState.enPassant == std::make_pair(destination.first-direction, destination.second)){
                board.RemovePiece(gameState.enPassant);
            }
        }
        
    break;
    default:
        break;
    }

    gameState.halfMoveClock++;
    if(gameState.currentPlayer == Black) gameState.fullMoveClock++;
    gameState.currentPlayer = oppositePlayer(gameState.currentPlayer);
    gameState.canEnPassant = enPassant;
    if(destination == std::make_pair(0,0) || origin == std::make_pair(0,0)) gameState.whiteCanCastleQueenSide = false;
    if(destination == std::make_pair(0,7) || origin == std::make_pair(0,7)) gameState.whiteCanCastleKingSide = false;
    if(destination == std::make_pair(7,0) || origin == std::make_pair(7,0)) gameState.blackCanCastleQueenSide = false;
    if(destination == std::make_pair(7,7) || origin == std::make_pair(7,7)) gameState.blackCanCastleKingSide = false;
    return true;
    
}
#include "game.hpp"

//Checks if a square is under attack by attacker
bool Game::IsAttacked(square pos, Player attacker){
    return 
    IsAttackedByRookQueen(pos, attacker) ||
    IsAttackedByBishopQueen(pos, attacker) ||
    IsAttackedByKnight(pos, attacker) ||
    IsAttackedByPawn(pos, attacker) ||
    IsAttackedByKing(pos, attacker);

}

//Should Probably refactor this further
bool Game::IsAttackedByRookQueen(square pos, Player attacker){
    for(int i = 0; i > -8; i--){    
        square newPos = {pos.first+i, pos.second};
        if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Rook)) return true;
        if (board[newPos] != Empty) break;
    }

    for(int i = 0; i < 8; i++){
        square newPos = {pos.first+i, pos.second};
                if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Rook)) return true;
        if (board[newPos] != Empty) break;
    }

    for(int i = 0; i > -8; i--){
        square newPos = {pos.first, pos.second+i};
                if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Rook)) return true;
        if (board[newPos] != Empty) break;
    }

    for(int i = 0; i < 8; i++){
        square newPos = {pos.first, pos.second+i};
                if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Rook)) return true;
        if (board[newPos] != Empty) break;
    }
    return false;
}

//Should probably be refactored further too
bool Game::IsAttackedByBishopQueen(square pos, Player attacker){
    for(int i = 0; i < 8; i++){
        
        square newPos = {pos.first+i, pos.second+i};
        if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Bishop)) return true;
        if (board[newPos] != Empty) break;
    }
        for(int i = 0; i < 8; i++){
        
        square newPos = {pos.first+i, pos.second-i};
        if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Bishop)) return true;
        if (board[newPos] != Empty) break;
    }
        for(int i = 0; i < 8; i++){
        
        square newPos = {pos.first-i, pos.second+i};
        if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Bishop)) return true;
        if (board[newPos] != Empty) break;
    }
        for(int i = 0; i < 8; i++){
        
        square newPos = {pos.first-i, pos.second-i};
        if(!OnBoard(newPos)) break;
        if(pieceColor(board[newPos]) == attacker && 
        ( pieceType(board[newPos]) == Queen || pieceType(board[newPos]) == Bishop)) return true;
        if (board[newPos] != Empty) break;
    }
    return false;
}

//Okay this entire file needs to be refactored again. This is a mess.
bool Game::IsAttackedByKnight(square pos, Player attacker){

    for(int i : {-2, -1, 1, 2}){
        for(int j : {-2, -1, 1, 2}){
            if(abs(i) == abs(j)) continue;
            square newPos = {pos.first+i, pos.second+j};
            if(!OnBoard(newPos))continue;
            Piece p = board[newPos];
            if(pieceColor(p) == attacker && pieceType(p) == Knight) return true;
        }
    }
    return false;
}

bool Game::IsAttackedByPawn(square pos, Player attacker){
    square newPos = {pos.first+(attacker == Black ? 1 : -1),pos.second+1};
    if(OnBoard(newPos)){
        Piece p = board[newPos];
        if(pieceColor(p) == attacker && pieceType(p) == Pawn) return true;
    }
    newPos = {pos.first+(attacker == Black ? 1 : -1),pos.second-1};
    if(OnBoard(newPos)){
        Piece p = board[newPos];
        if(pieceColor(p) == attacker && pieceType(p) == Pawn) return true;
    }
    return false;
}

bool Game::IsAttackedByKing(square pos, Player attacker){

    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            square newPos = {pos.first+i, pos.second+j};
            if(!OnBoard(newPos)) continue;
            Piece p = board[newPos];
            if(pieceColor(p) == attacker && pieceType(p) == King) return true;
        }
    }
    return false;
    
}


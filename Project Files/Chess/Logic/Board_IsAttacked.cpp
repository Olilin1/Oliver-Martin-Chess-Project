#include "Board.hpp"

//Calculates the squares that could potentially be attacked bya sliding piece
std::set<square> Board::CalculateSlidingMoves(square pos, std::vector<std::pair<int, int>> directions)
{
    std::set<square> moves;
    for (std::pair<int, int> p : directions)
    {
        for (int i = 1; i < 8; i++)
        {
            square newPos = {pos.first + p.first * i, pos.second + p.second * i};
            if(!OnBoard(newPos)) break;

            if(!IsEmpty(newPos)){
                moves.insert(newPos);
                break;
            }    
        }
    }
    return moves;
}

bool Board::IsAttacked(square pos, Player attacker){
    return 
    IsAttackedByRook(pos, attacker) ||
    IsAttackedByBishop(pos, attacker) ||
    IsAttackedByKnight(pos, attacker) ||
    IsAttackedByPawn(pos, attacker) ||
    IsAttackedByKing(pos, attacker);

}

bool Board::IsAttackedByRook(square pos, Player attacker){
    for(square a : CalculateSlidingMoves(pos, rookMoves)){
        if((pieceType(board[a.first][a.second]) == Rook || pieceType(board[a.first][a.second]) == Queen) && pieceColor( board[a.first][a.second]) == attacker) return true;
    }
    return false;
}

bool Board::IsAttackedByBishop(square pos, Player attacker){
    for(square a : CalculateSlidingMoves(pos, bishopMoves)){
        if((pieceType(board[a.first][a.second]) == Bishop || pieceType(board[a.first][a.second]) == Queen)&& pieceColor( board[a.first][a.second]) == attacker) return true;
    }
    return false;
}

//Checks if the square is attacked by a queen, this function is not used for now due to it being faster checking in other functions
bool Board::IsAttackedByQueen(square pos, Player attacker){
    for(square a : CalculateSlidingMoves(pos, queenMoves)){
        if(pieceType(board[a.first][a.second]) == Queen && pieceColor( board[a.first][a.second]) == attacker) return true;
    }
    return false;
}

bool Board::IsAttackedByKnight(square pos, Player attacker){
    for(int i : {-2, -1, 1, 2}){
        for(int j : {-2, -1, 1, 2}){
            if(abs(i) == abs(j)) continue;
            square newPos = {pos.first+i, pos.second+j};
            if(!OnBoard(newPos))continue;
            Piece p = board[newPos.first][newPos.second];
            if(pieceType(p) == Knight && pieceColor(p) == attacker) return true;
        }
    }
    return false;
}

bool Board::IsAttackedByPawn(square pos, Player attacker){
    square newPos = {pos.first+(attacker == Black ? 1 : -1),pos.second+1};
    if(OnBoard(newPos)){
        Piece p = board[newPos.first][newPos.second];
        if(pieceColor(p) == attacker && pieceType(p) == Pawn) return true;
    }
    newPos = {pos.first+(attacker == Black ? 1 : -1),pos.second-1};
    if(OnBoard(newPos)){
        Piece p = board[newPos.first][newPos.second];
        if(pieceColor(p) == attacker && pieceType(p) == Pawn) return true;
    }
    return false;
}

bool Board::IsAttackedByKing(square pos, Player attacker){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            square newPos = {pos.first+i, pos.second+j};
            if(!OnBoard(newPos)) continue;
            Piece p = board[newPos.first][newPos.second];
            if(pieceColor(p) == attacker && pieceType(p) == King) return true;
        }
    }
    return false;
}


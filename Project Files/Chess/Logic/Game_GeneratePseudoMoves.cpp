#include"Game.hpp"

Bitboard Game::MakeBishopMove(int originSquare){
    Bitboard attackBoard = GetAttackBishopBoardFromMagic(originSquare);
    attackBoard.bitBoard &= (gameState.currentPlayer == White ? ~whitePiecesBB.bitBoard : ~blackPiecesBB.bitBoard);
    return attackBoard;
}

Bitboard Game::MakeRookMove(int originSquare){
    Bitboard attackBoard = GetAttackRookBoardFromMagic(originSquare);
    attackBoard.bitBoard &= (gameState.currentPlayer == White ? ~whitePiecesBB.bitBoard : ~blackPiecesBB.bitBoard);
    return attackBoard;
}

Bitboard Game::MakeQueenMove(int originSquare){
    Bitboard attackBoard;
    //The set of queen moves is the union of bishop and rook moves
    attackBoard.bitBoard = MakeBishopMove(originSquare).bitBoard | MakeRookMove(originSquare).bitBoard;
    return attackBoard;
}

Bitboard Game::MakeKingMove(int originSquare){
    Bitboard attackBoard = KingAttacks[originSquare];
    attackBoard.bitBoard &= (gameState.currentPlayer == White ? ~whitePiecesBB.bitBoard : ~blackPiecesBB.bitBoard);
    
    //Add castling moves (it will be checked if king is in check after castling in the MakeMove function, remember these are all pseudo moves)
    if(gameState.currentPlayer == White){
        if(gameState.whiteCanCastleQueenSide && Board[1] == Empty && Board[2] == Empty && Board[3] == Empty && !IsAttacked(3) && !IsAttacked(4)) 
            attackBoard.Set(2);
        if(gameState.whiteCanCastleKingSide && Board[5] == Empty && Board[6] == Empty && !IsAttacked(4) && !IsAttacked(5)){
            attackBoard.Set(6);
        }
    }
    else{
        if(gameState.blackCanCastleQueenSide && Board[57] == Empty && Board[58] == Empty && Board[59] == Empty && !IsAttacked(59) && !IsAttacked(60)) 
            attackBoard.Set(58);
        if(gameState.blackCanCastleKingSide && Board[61] == Empty && Board[62] == Empty && !IsAttacked(60) && !IsAttacked(61))
            attackBoard.Set(62); 
    }
    return attackBoard;
}

Bitboard Game::MakeKingMoveNoCastling(int originSquare){        //Used to check if a square is attacked by a king
    Bitboard attackBoard = KingAttacks[originSquare];
    attackBoard.bitBoard &= (gameState.currentPlayer == White ? ~whitePiecesBB.bitBoard : ~blackPiecesBB.bitBoard);
    return attackBoard;
}

Bitboard Game::MakeKnightMove(int originSquare){
    Bitboard attackBoard = KnightAttacks[originSquare];
    attackBoard.bitBoard &= (gameState.currentPlayer == White ? ~whitePiecesBB.bitBoard : ~blackPiecesBB.bitBoard);
    return attackBoard;
}

Bitboard Game::GetAttackBishopBoardFromMagic(int originSquare){
    uint64_t blockerMask = BishopBlockerMasks[originSquare].bitBoard;
    uint64_t blockerBoard = blockerMask & ~(whitePiecesBB.bitBoard | blackPiecesBB.bitBoard);
    blockerBoard *= BishopMagicNumbers[originSquare];
    blockerBoard >>= 55;
    return BishopAttacks[originSquare][blockerBoard];
}

Bitboard Game::GetAttackBishopBoardFromMagic(int originSquare, Bitboard occupancy){
    uint64_t blockerMask = BishopBlockerMasks[originSquare].bitBoard;
    uint64_t blockerBoard = blockerMask & ~(occupancy.bitBoard);
    blockerBoard *= BishopMagicNumbers[originSquare];
    blockerBoard >>= 55;
    return BishopAttacks[originSquare][blockerBoard];
}

Bitboard Game::GetAttackRookBoardFromMagic(int originSquare){
    uint64_t blockerMask = RookBlockerMasks[originSquare].bitBoard;
    uint64_t blockerBoard = blockerMask & ~(whitePiecesBB.bitBoard | blackPiecesBB.bitBoard);
    blockerBoard *= RookMagicNumbers[originSquare];
    blockerBoard >>= 52;
    return RookAttacks[originSquare][blockerBoard]; 
}

Bitboard Game::GetAttackRookBoardFromMagic(int originSquare, Bitboard occupancy){
    uint64_t blockerMask = RookBlockerMasks[originSquare].bitBoard;
    uint64_t blockerBoard = blockerMask & ~(occupancy.bitBoard);
    blockerBoard *= RookMagicNumbers[originSquare];
    blockerBoard >>= 52;
    return RookAttacks[originSquare][blockerBoard];
}

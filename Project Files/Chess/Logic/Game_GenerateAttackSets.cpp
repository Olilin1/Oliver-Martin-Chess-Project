#include"Game.hpp"

void Game::GeneratePawnAttackSet(std::set<std::pair<int, int>>& moveList){
    Bitboard attackBoard;
    Bitboard copiedBoard;
    if(gameState.currentPlayer == White){
        uint64_t pawnBitboard = pieceBitboards[WhitePawn].bitBoard;
        //Single step
        attackBoard.bitBoard |= (pawnBitboard << 8) & ~whitePiecesBB.bitBoard & ~blackPiecesBB.bitBoard;  //Left-shifting by 8 corresponds to moving each pawn 1 step forward
        copiedBoard.bitBoard = attackBoard.bitBoard & ranksAndFiles.rankThree;

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move - 8, move});
        }

        attackBoard.bitBoard = copiedBoard.bitBoard;        //The copiedBoard stored the moves to the third rank, which we are interested in to calculate the possible double steps

        //Double step
        attackBoard.bitBoard |= (attackBoard.bitBoard << 8) & ~whitePiecesBB.bitBoard & ~blackPiecesBB.bitBoard;     //First the attackboard bitboard has an attack board of pawns that have moved one step, with blocking pieces considered. Take all pawns that moved one step from rank 2 to rank 3, and shift these positions by 8 again to get them to move one more step forward

        attackBoard.bitBoard &= ranksAndFiles.rankFour;

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move - 16, move});
        }

        //En passant
        if(gameState.canEnPassant == true){
            //en passant left
            uint64_t enPassantBoard = 1ULL << gameState.enPassant;
            if((((enPassantBoard & ~ranksAndFiles.fileOne) >> 9) & pawnBitboard) != 0){
                moveList.insert({gameState.enPassant - 9, gameState.enPassant});
            }

            //en passant right
            if((((enPassantBoard & ~ranksAndFiles.fileEight) >> 7) & pawnBitboard) != 0){
                moveList.insert({gameState.enPassant - 7, gameState.enPassant});
            }
        }

        //Capture
        //Left capture
        attackBoard.bitBoard |= (((pawnBitboard & ~ranksAndFiles.fileOne) << 7) & blackPiecesBB.bitBoard) & ~whitePiecesBB.bitBoard;     //Remove pawns on file one and then left-shift the rest of the pawns 7 steps, corresponding to them moving north-west. Then take the intersection of these move squares with the opponent's pieces' positions

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move - 7, move});
        }

        //Right capture
        attackBoard.bitBoard |= (((pawnBitboard & ~ranksAndFiles.fileEight) << 9) & blackPiecesBB.bitBoard) & ~whitePiecesBB.bitBoard;

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move - 9, move});
        }
    }
    else {
        uint64_t pawnBitboard = pieceBitboards[BlackPawn].bitBoard;
        //Single step
        attackBoard.bitBoard |= (pawnBitboard >> 8) & ~whitePiecesBB.bitBoard & ~blackPiecesBB.bitBoard;  //Right-shifting by 8 corresponds to moving each black pawn 1 step forward
        copiedBoard.bitBoard = attackBoard.bitBoard & ranksAndFiles.rankSix;

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move + 8, move});
        }

        attackBoard.bitBoard = copiedBoard.bitBoard;

        //Double step
        attackBoard.bitBoard |= (attackBoard.bitBoard >> 8) & ~whitePiecesBB.bitBoard & ~blackPiecesBB.bitBoard;

        attackBoard.bitBoard &= ranksAndFiles.rankFive;

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move + 16, move});
        }

        //En passant
        if(gameState.canEnPassant == true){
            //en passant right
            uint64_t enPassantBoard = 1ULL << gameState.enPassant;
            if((((enPassantBoard & ~ranksAndFiles.fileOne) << 7) & pawnBitboard) != 0){
                moveList.insert({gameState.enPassant + 7, gameState.enPassant});
            }

            //en passant left
            if((((enPassantBoard & ~ranksAndFiles.fileEight) << 9) & pawnBitboard) != 0){
                moveList.insert({gameState.enPassant + 9, gameState.enPassant});
            }
        }

        //Capture
        //Right capture
        attackBoard.bitBoard |= (((pawnBitboard & ~ranksAndFiles.fileEight) >> 7) & whitePiecesBB.bitBoard) & ~blackPiecesBB.bitBoard;     //Remove pawns on file one and then left-shift the rest of the pawns 7 steps, corresponding to them moving north-west. Then take the intersection of these move squares with the opponent's pieces' positions

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move + 7, move});
        }

        //Left capture
        attackBoard.bitBoard |= (((pawnBitboard & ~ranksAndFiles.fileOne) >> 9) & whitePiecesBB.bitBoard) & ~blackPiecesBB.bitBoard;

        while(attackBoard.bitBoard){
            int move = attackBoard.popLSB();
            moveList.insert({move + 9, move});
        }
    }
}

void Game::GenerateKingAttackSet(std::set<std::pair<int, int>>& moveSet){
    int kingPos = gameState.currentPlayer == White ? pieceBitboards[WhiteKing].LSBIndex() : pieceBitboards[BlackKing].LSBIndex();
    Bitboard attackBoard = MakeKingMove(kingPos);
    while(attackBoard.bitBoard){
        int toSquare = attackBoard.popLSB();
        moveSet.insert({kingPos, toSquare});
    }
}

void Game::GenerateKnightAttackSet(std::set<std::pair<int, int>>& moveSet){
    Bitboard knightPositions = gameState.currentPlayer == White ? pieceBitboards[WhiteKnight] : pieceBitboards[BlackKnight];
    int positions[11] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int i = 0;
    while(knightPositions.bitBoard){
        positions[i++] = knightPositions.popLSB();
    }
    i = 0;
    while(positions[i] != -1){
        Bitboard attackBoard = MakeKnightMove(positions[i]);
        while(attackBoard.bitBoard){
            int toSquare = attackBoard.popLSB();
            moveSet.insert({positions[i], toSquare});
        }
        i++;
    }
}

void Game::GenerateRookAttackSet(std::set<std::pair<int, int>>& moveSet){
    Bitboard rookPositions = gameState.currentPlayer == White ? pieceBitboards[WhiteRook] : pieceBitboards[BlackRook];
    int positions[11] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int i = 0;
    while(rookPositions.bitBoard){
        positions[i++] = rookPositions.popLSB();
    }
    i = 0;
    while(positions[i] != -1){
        Bitboard attackBoard = MakeRookMove(positions[i]);
        while(attackBoard.bitBoard){
            int toSquare = attackBoard.popLSB();
            moveSet.insert({positions[i], toSquare});
        }
        i++;
    }
}

void Game::GenerateBishopAttackSet(std::set<std::pair<int, int>>& moveSet){
    Bitboard bishopPositions = gameState.currentPlayer == White ? pieceBitboards[WhiteBishop] : pieceBitboards[BlackBishop];
    int positions[11] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int i = 0;
    while(bishopPositions.bitBoard){
        positions[i++] = bishopPositions.popLSB();
    }
    i = 0;
    while(positions[i] != -1){
        Bitboard attackBoard = MakeBishopMove(positions[i]);
        while(attackBoard.bitBoard){
            int toSquare = attackBoard.popLSB();
            moveSet.insert({positions[i], toSquare});
        }
        i++;
    }
}

void Game::GenerateQueenAttackSet(std::set<std::pair<int, int>>& moveSet){
    Bitboard queenPositions = gameState.currentPlayer == White ? pieceBitboards[WhiteQueen] : pieceBitboards[BlackQueen];
    int positions[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int i = 0;
    while(queenPositions.bitBoard){
        positions[i++] = queenPositions.popLSB();
    }
    i = 0;
    while(positions[i] != -1){
        Bitboard attackBoard = MakeQueenMove(positions[i]);
        while(attackBoard.bitBoard){
            int toSquare = attackBoard.popLSB();
            moveSet.insert({positions[i], toSquare});
        }
        i++;
    }
}

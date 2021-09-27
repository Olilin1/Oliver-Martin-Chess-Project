#include "Game.hpp"

#include "Game.hpp"

Move Game::AiMove(search_parameters params){
    int depth = 4;
    int maxEval = (depth+1) * inf + 1;
    int beta = maxEval;
    int alpha = -maxEval;
    int eval;

    Move bestMove;

    std::set<std::pair<int, int>> allMoves;
    MakeAllPseudoMoves(allMoves);
    for(auto move : allMoves){
        if(MakeGameMove(move.first,move.second)){
            if(gameState.awaitingPromotion){
                for(auto p : {Queen,Knight,Rook,Bishop}){
                    Piece promotionPiece = ConvertToOppositeColoredPiece(p);
                    MakeBoardMove(-1, -1, promotionPiece);
                    eval = -miniMax(depth,-beta,-alpha);
                    if(eval > alpha){
                        alpha = eval;
                        bestMove.origin = move.first;
                        bestMove.destination = move.second;
                        bestMove.promotion = true;
                        bestMove.promotionPiece = promotionPiece;
                    }
                    gameState.awaitingPromotion = true;
                }
                gameState.awaitingPromotion = false;
            }
            else{
                eval = -miniMax(depth-1,-beta,-alpha);
                if(eval > alpha){
                    alpha = eval;
                    bestMove.origin = move.first;
                    bestMove.destination = move.second;
                }
            }
            UnmakeMove();
        }
    }

    MakeGameMove(bestMove.origin,bestMove.destination);
    if(gameState.awaitingPromotion){
        MakeBoardMove(-1, -1, bestMove.promotionPiece);
    }
    return bestMove;
}

int Game::miniMax(int depth, int alpha, int beta){
    int eval;
    if(depth == 0) return Quiescent(alpha, beta);

    bool madeMove = false;
    std::set<std::pair<int,int>> allMoves;
    MakeAllPseudoMoves(allMoves);
    for(auto move : allMoves){
        if(MakeGameMove(move.first,move.second)){
            madeMove = true;

            if(gameState.awaitingPromotion){
                for(auto p : {Queen,Knight,Rook,Bishop}){
                    MakeBoardMove(-1, -1, ConvertToOppositeColoredPiece(p));
                    eval = -miniMax(depth,-beta,-alpha);
                    if (eval >= beta){
                        UnmakeMove();
                        return eval;
                    }
                    if(eval > alpha) alpha = eval;
                    gameState.awaitingPromotion = true;
                }
                gameState.awaitingPromotion = false;
            }
            else{
                eval = -miniMax(depth-1,-beta,-alpha);
                if (eval >= beta){
                    UnmakeMove();
                    return beta;
                }
                if(eval > alpha) alpha = eval;
            }
            UnmakeMove();
        }
    }
    if(madeMove){
        return alpha;
    }
    else {
        return evaluatePosition()*(depth+1) * gameState.currentPlayer;
    }
}

int Game::Quiescent(int alpha, int beta){
    int eval = evaluatePosition() * gameState.currentPlayer;
    if(eval >= beta) return beta;
    if(alpha < eval) alpha = eval;          //This ensures that non-capture score will be returned if capture is bad (i.e. all captures yield scores less than alpha)

    std::set<std::pair<int, int>> captureMoves;
    MakeAllCaptureMoves(captureMoves);

    for(auto move : captureMoves){
        int see = SEE(move.first, move.second);
        if(see <= 0){
            continue;      //If the static exchange evaluation is not beneficial for current player then no need to check that capture
        }

        if(MakeGameMove(move.first, move.second)){
            int score = eval + see;
            UnmakeMove();

            if(score >= beta){
                return beta;
            }

            if(score > alpha){
                alpha = score;
            }
        }
    }
    return alpha;
}

//This function tells me it would be nice to have bitwise operator overloading for Bitboard class... may add later
Bitboard Game::attackAndDefend(Bitboard occupancy, int originSquare){
    Bitboard attackAndDefend;
    attackAndDefend.bitBoard |= (((1ULL << (originSquare + 9)) & (1ULL << (originSquare + 7)) & (1ULL << (originSquare - 9)) & (1ULL << (originSquare - 7))) & (pieceBitboards[WhitePawn].bitBoard | pieceBitboards[BlackPawn].bitBoard));
    attackAndDefend.bitBoard |= KnightAttacks[originSquare].bitBoard & (pieceBitboards[WhiteKnight].bitBoard | pieceBitboards[BlackKnight].bitBoard);
    attackAndDefend.bitBoard |= GetAttackBishopBoardFromMagic(originSquare, occupancy).bitBoard & (pieceBitboards[WhiteBishop].bitBoard | pieceBitboards[BlackBishop].bitBoard | pieceBitboards[WhiteQueen].bitBoard | pieceBitboards[BlackQueen].bitBoard);
    attackAndDefend.bitBoard |= GetAttackRookBoardFromMagic(originSquare, occupancy).bitBoard & (pieceBitboards[WhiteRook].bitBoard | pieceBitboards[BlackRook].bitBoard | pieceBitboards[WhiteQueen].bitBoard | pieceBitboards[BlackQueen].bitBoard);
    attackAndDefend.bitBoard |= KingAttacks[originSquare].bitBoard & (pieceBitboards[WhiteKing].bitBoard | pieceBitboards[BlackKing].bitBoard);

    attackAndDefend.bitBoard &= occupancy.bitBoard;
    return attackAndDefend;
}

//SEE stands for static exchange evaluation and evaluates the best score for current player after several trades on a single square has been made
int Game::SEE(int originSquare, int destinationSquare){

    int currentPiece = Board[originSquare];
    int sideToMove = currentPiece % 2 == 1 ? 0 : 1;
    Bitboard pieceBitboard (1ULL << originSquare);

    Bitboard occupancy (whitePiecesBB.bitBoard | blackPiecesBB.bitBoard);   //All the pieces
    Bitboard attAndDef = attackAndDefend(occupancy, destinationSquare);
    int iteration = 0;

    int scoreGains[32] = {0};         //This array keeps track of the score gains for players after all trades
    scoreGains[0] = PieceValue(Board[destinationSquare]);       //The first score gain is capturing the piece at destinationSquare

    //Then check all pieces that attack the current square, using the same method used before to check if king is in check
    while(pieceBitboard.bitBoard) {
        iteration++;
        scoreGains[iteration] = PieceValue(currentPiece) - scoreGains[iteration - 1];           //The score gain for the current player is the potential capture subtracted by the score gain the opposite player has gotten so far
        if (std::max(-scoreGains[iteration-1], scoreGains[iteration]) < 0) break;
        occupancy.bitBoard ^= pieceBitboard.bitBoard;          //Remove the attacking piece to allow for x-rays

        if(currentPiece != BlackKing && currentPiece != WhiteKing && currentPiece != BlackKnight && currentPiece != WhiteKnight){     //If the attacking piece was R,B,P or Q then it may have allowed x-ray
            //Update x-rays
            attAndDef.bitBoard |= GetAttackBishopBoardFromMagic(destinationSquare, occupancy).bitBoard & (pieceBitboards[WhiteBishop].bitBoard | pieceBitboards[BlackBishop].bitBoard | pieceBitboards[WhiteQueen].bitBoard | pieceBitboards[BlackQueen].bitBoard);
            attAndDef.bitBoard |= GetAttackRookBoardFromMagic(destinationSquare, occupancy).bitBoard & (pieceBitboards[WhiteRook].bitBoard | pieceBitboards[BlackRook].bitBoard | pieceBitboards[WhiteQueen].bitBoard | pieceBitboards[BlackQueen].bitBoard);     //Update possible x-rays
        }

        attAndDef.bitBoard &= occupancy.bitBoard;

        sideToMove = !sideToMove;
        pieceBitboard.bitBoard = 0;
        for(currentPiece = WhitePawn + sideToMove; currentPiece <= BlackKing; currentPiece+=2){
            uint64_t tempBitboard = pieceBitboards[currentPiece].bitBoard & attAndDef.bitBoard;
            if(tempBitboard){           //True if one of the pieces is among the attacking pieces
                pieceBitboard.bitBoard = tempBitboard & -tempBitboard;     //Get the LSB
                break;
            }
        }
    }
    //Each entry in scoreGains denotes the score gain for a player: scoreGains[0] is gain for currentPlayer, scoreGains[1] is gain for opposite player, scoreGains[2] is gain for currentPlayer and so on
    //-scoreGains[iteration-1] is the score if currentPlayer chooses not to capture at that point, while scoreGains[iteration] is the score if the currentPlayer does choose to capture at that point
    //The currentPlayer will of course choose the option that maximizes their score, and we add a sign in front of the expression because the gain for one player is the loss for the other player
    while(--iteration) {
        scoreGains[iteration-1] = -std::max(-scoreGains[iteration-1], scoreGains[iteration]);
    }
    return scoreGains[0];
}

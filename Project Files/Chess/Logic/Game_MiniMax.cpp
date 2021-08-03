#include "Game.hpp"

std::pair<int,int> Game::AiMove(){
    int depth = 4;
    float maxEval = inf + 2;
    float beta = maxEval;
    float alpha = -maxEval;
    float eval;
    
    std::pair<int,int> bestMove;
    Piece promotion;

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
                        bestMove = move;
                        promotion = promotionPiece;
                    }
                    gameState.awaitingPromotion = true;
                }
                gameState.awaitingPromotion = false;
            }
            else{
                eval = -miniMax(depth-1,-beta,-alpha);
                if(eval > alpha){
                    alpha = eval;
                    bestMove = move;
                }
            }
            UnmakeMove();
        }
    }

    MakeGameMove(bestMove.first,bestMove.second);
    if(gameState.awaitingPromotion){
        MakeBoardMove(-1, -1, promotion);
    }
    return bestMove;
}

int Game::miniMax(int depth, float alpha, float beta){
    float eval;
    if(depth == 0) {
        //return gameState.currentPlayer*evaluatePosition();
        return Quiescent(alpha, beta);
    }

    std::set<std::pair<int,int>> allMoves;
    MakeAllPseudoMoves(allMoves);
    for(auto move : allMoves){
        if(MakeGameMove(move.first,move.second)){
            if(gameState.awaitingPromotion){
                for(auto p : {Queen,Knight,Rook,Bishop}){
                    MakeBoardMove(-1, -1, ConvertToOppositeColoredPiece(p));        //{-1,-1} because squares don't matter when promotion is happening
                    eval = -miniMax(depth,-beta,-alpha);
                    UnmakeMove();
                    if (eval >= beta){
                        return beta;
                    }
                    if(eval > alpha) alpha = eval;
                    gameState.awaitingPromotion = true;
                }
                gameState.awaitingPromotion = false;
            }
            else{
                eval = -miniMax(depth-1,-beta,-alpha);
                UnmakeMove();
                if (eval >= beta){              //The score exceeded the upper bound
                    return beta;
                }
                if(eval > alpha) alpha = eval;      //We have a new lower bound
            }
        }
    }
    return alpha;
}

//Not working TODO fix
int Game::Quiescent(float alpha, float beta){
    std::set<std::pair<int, int>> captureMoves;
    MakeAllCaptureMoves(captureMoves);
    float eval = evaluatePosition()*gameState.currentPlayer;

    if(eval >= beta) return beta;
    if(eval > alpha) alpha = eval;

    Bitboard checkedSquares;        //This bitboard stores all squares that have been checked with see

    for(auto move : captureMoves){
        if(MakeGameMove(move.first, move.second)){
            UnmakeMove();
            if(checkedSquares[move.second]) continue;

            int seeScore = SEE(move.first, move.second);

            if(seeScore <= 0) continue;      //Only check moves with static exchange evaluation > 0

            checkedSquares.Set(move.second);

            int score = eval + seeScore;

            if(score >= beta){
                return beta;
            }

            if(score > alpha){
                alpha = eval + seeScore;
            }
        }
    }
    return alpha;
}

//This function tells me it would be nice to have bitwise operator overloading for Bitboard class... may add later
Bitboard Game::attackAndDefend(Bitboard occupancy, int originSquare){
    Bitboard attackAndDefend;
    //Add attacking and defending pawns (no en passant for now maybe add later)
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
    Bitboard pieceBitboard = (1ULL << originSquare);
    uint64_t potentialXRAY = pieceBitboards[WhiteQueen].bitBoard | pieceBitboards[BlackQueen].bitBoard | pieceBitboards[WhiteRook].bitBoard | pieceBitboards[BlackRook].bitBoard | pieceBitboards[WhiteBishop].bitBoard | pieceBitboards[BlackBishop].bitBoard;

    Bitboard occupancy (whitePiecesBB.bitBoard | blackPiecesBB.bitBoard);   //All the pieces
    occupancy.bitBoard ^= pieceBitboard.bitBoard;   //Remove originSquare to allow for x-rays later
    Bitboard attAndDef = attackAndDefend(occupancy, originSquare);
    int iteration = 0;

    int scoreGains[32] = {0};         //This array keeps track of the score gains for players after all trades
    scoreGains[0] = PieceValue(Board[destinationSquare]);       //The first score gain is capturing the piece at destinationSquare

    //Then check all pieces that attack the current square, using the same method used before to check if king is in check
    do {
        iteration++;
        scoreGains[iteration] = PieceValue(currentPiece) - scoreGains[iteration - 1];           //The score gain for the current player is the potential capture subtracted by the score gain the opposite player has gotten so far
        if (std::max(-scoreGains[iteration-1], scoreGains[iteration]) < 0) break;
        occupancy.bitBoard ^= pieceBitboard.bitBoard;          //Remove the attacking piece to allow for x-rays
        if(pieceBitboard.bitBoard & potentialXRAY){
            attAndDef.bitBoard |= GetAttackBishopBoardFromMagic(originSquare, occupancy).bitBoard & (pieceBitboards[WhiteBishop].bitBoard | pieceBitboards[BlackBishop].bitBoard | pieceBitboards[WhiteQueen].bitBoard | pieceBitboards[BlackQueen].bitBoard);
            attAndDef.bitBoard |= GetAttackRookBoardFromMagic(originSquare, occupancy).bitBoard & (pieceBitboards[WhiteRook].bitBoard | pieceBitboards[BlackRook].bitBoard | pieceBitboards[WhiteQueen].bitBoard | pieceBitboards[BlackQueen].bitBoard);     //Update possible x-rays
            attAndDef.bitBoard &= occupancy.bitBoard;
        }
        else{
            attAndDef.bitBoard ^= pieceBitboard.bitBoard;     //otherwise just remove the originSquare
        }

        sideToMove = ~sideToMove;
        for(currentPiece = WhitePawn + sideToMove; currentPiece <= BlackKing; currentPiece+=2){
            uint64_t tempBitboard = pieceBitboards[currentPiece].bitBoard & attAndDef.bitBoard;
            if(tempBitboard){           //True if one of the pieces is among the attacking pieces
                pieceBitboard = tempBitboard & -tempBitboard;     //Get the LSB
                break;
            }
        }
    }
    while(currentPiece <= BlackKing); //As long as the bitboard of attacking pieces is not 0, keep looping

    //Each entry in scoreGains denotes the score gain for a player: scoreGains[0] is gain for currentPlayer, scoreGains[1] is gain for opposite player, scoreGains[2] is gain for currentPlayer and so on
    while(--iteration) {
        scoreGains[iteration] = -std::min(-scoreGains[iteration], scoreGains[iteration + 1]);
    }
    return scoreGains[0];
}

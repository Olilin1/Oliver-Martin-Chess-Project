#include"Game.hpp"

//TODO: Something is wrong with whiteKingPos, it updates incorrectly. Check what this is. Maybe it has to with the move generation for kings

bool Game::MakeGameMove(int originSquare, int destinationSquare){         //Returns true if a move from originSquare to destinationSquare is legal, false otherwise
    if((Board[originSquare] % 2 == 0 && gameState.currentPlayer == White) || (Board[originSquare] % 2 == 1 && gameState.currentPlayer == Black) || Board[originSquare] == Empty) return false;
    MakeBoardMove(originSquare, destinationSquare);
    //If the move isn't legal, return false
    if(gameState.currentPlayer == White){       //note that the currentPlayer was switched when the move was made
        if(IsAttacked(pieceBitboards[WhiteKing].LSBIndex())){
            UnmakeMove();
            return false;
        }
    }
    else{
        if(IsAttacked(pieceBitboards[BlackKing].LSBIndex())){
            UnmakeMove();
            return false;
        } 
    }
    gameState.currentPlayer = gameState.currentPlayer == White ? Black : White;
    return true;
}

void Game::MakeBoardMove(int originSquare, int destinationSquare, Piece promotion){
    if(gameState.awaitingPromotion){
        if(promotion == Empty) return;
        pieceBitboards[Board[gameState.promotion]].Unset(gameState.promotion);
        Board[gameState.promotion] = promotion;
        gameState.awaitingPromotion = false;
        pieceBitboards[promotion].Set(gameState.promotion);
        return;
    }

    Move currentMove;
    currentMove.moveGameState = gameState;
    currentMove.origin = originSquare;
    currentMove.destination = destinationSquare;
    if(Board[destinationSquare] != Empty) gameState.halfMoveClock = 0;
    currentMove.capturedPiece = (Piece)Board[destinationSquare];

    bool canEnPassant = false;
    switch(Board[originSquare]){
        case BlackPawn: {
            //If this is an en passant move then we have to explicitly remove the en passant piece
            if(gameState.canEnPassant && destinationSquare == gameState.enPassant){
                Board[gameState.enPassant + 8] = Empty;
                whitePiecesBB.Unset(gameState.enPassant + 8);
                pieceBitboards[WhitePawn].Unset(gameState.enPassant + 8);
                currentMove.enPassantMove = true;
            }
            else if(originSquare - destinationSquare == 16){
                gameState.enPassant = originSquare - 8;
                canEnPassant = true;
            }
            else if(destinationSquare <= 7){
                gameState.promotion = destinationSquare;
                gameState.awaitingPromotion = true; 
                currentMove.promotion = true;
            }
            gameState.halfMoveClock = 0;
            break;
        }
        case BlackKing: {
            //If this is a castling we have to change the position of the rook as well
            if(destinationSquare - originSquare == 2){      //Castle king side
                MakeAnyMove(63, 61);
                currentMove.castledKingSide = true;
            }
            else if(destinationSquare - originSquare == -2){        //Castle queen side
                MakeAnyMove(56, 59);
                currentMove.castledQueenSide = true;
            }
            gameState.blackCanCastleKingSide = false;
            gameState.blackCanCastleQueenSide = false;
            gameState.blackKingPos = destinationSquare;
            break;
        }
        case WhitePawn: {
            //If this is an en passant move then we have to explicitly remove the en passant piece
            if(gameState.canEnPassant &&  destinationSquare == gameState.enPassant){
                Board[gameState.enPassant - 8] = Empty;
                blackPiecesBB.Unset(gameState.enPassant - 8);
                pieceBitboards[BlackPawn].Unset(gameState.enPassant - 8);
                currentMove.enPassantMove = true;
            }
            else if(destinationSquare - originSquare == 16){
                gameState.enPassant = originSquare + 8;
                canEnPassant = true;
            }
            else if(destinationSquare >= 56){
                gameState.promotion = destinationSquare;
                gameState.awaitingPromotion = true;
                currentMove.promotion = true;
            }
            gameState.halfMoveClock = 0;
            break;
        }
        case WhiteKing: {
            //If this is a castling we have to change the position of the rook as well
            if(destinationSquare - originSquare == 2){      //Castle king side
                MakeAnyMove(7, 5);
                currentMove.castledKingSide = true;
            }
            else if(destinationSquare - originSquare == -2){        //Castle queen side
                MakeAnyMove(0, 3);
                currentMove.castledQueenSide = true;
            }
            gameState.whiteCanCastleKingSide = false;
            gameState.whiteCanCastleQueenSide = false;
            gameState.whiteKingPos = destinationSquare;
            break;
        }
    }

    gameState.halfMoveClock++;
    if(gameState.currentPlayer == Black) gameState.fullMoveClock++;

    if(destinationSquare == 0 || originSquare == 0) gameState.whiteCanCastleQueenSide = false;
    if(destinationSquare == 7 || originSquare == 7) gameState.whiteCanCastleKingSide = false;
    if(destinationSquare == 56 || originSquare == 56) gameState.blackCanCastleQueenSide = false;
    if(destinationSquare == 63 || originSquare == 63) gameState.blackCanCastleKingSide = false;

    gameState.canEnPassant = canEnPassant;
    
    MakeAnyMove(originSquare, destinationSquare);
    moveStack.push(currentMove);
}

void Game::MakeAnyMove(int originSquare, int destinationSquare){
    int pieceType = Board[originSquare];
    if(pieceType % 2 == 0){     //It's a black piece
        blackPiecesBB.Unset(originSquare);
        blackPiecesBB.Set(destinationSquare);
    }
    else{
        whitePiecesBB.Unset(originSquare);
        whitePiecesBB.Set(destinationSquare);
    }
    pieceBitboards[pieceType].Unset(originSquare);
    pieceBitboards[pieceType].Set(destinationSquare);
    int capturedPiece = Board[destinationSquare];
    if(capturedPiece != Empty){
        pieceBitboards[capturedPiece].Unset(destinationSquare);
        if(capturedPiece % 2 == 0) blackPiecesBB.Unset(destinationSquare);
        else whitePiecesBB.Unset(destinationSquare);
    }
    Board[destinationSquare] = pieceType;
    Board[originSquare] = Empty;
}

//Create a "super piece" that can move in all directions that every piece can. For each specific move variant, check if it intersects with an opponent piece with that move variant If it does, then that square is under attack
bool Game::IsAttacked(int square){ 
    if(gameState.currentPlayer == White){
        //Attack by pawn
        if(square < 56 && square % 8 > 0 && Board[square + 7] == BlackPawn) return true;
        if(square < 56 && square % 8 < 7 && Board[square + 9] == BlackPawn) return true;

        //Attack by king
        if((MakeKingMoveNoCastling(square).bitBoard & pieceBitboards[BlackKing].bitBoard) != 0) return true;

        //Attack by knight
        if((MakeKnightMove(square).bitBoard & pieceBitboards[BlackKnight].bitBoard) != 0) return true;

        //Attack by bishop
        uint64_t attackBoard = MakeBishopMove(square).bitBoard; 
        if((attackBoard & pieceBitboards[BlackBishop].bitBoard) != 0 || (attackBoard & pieceBitboards[BlackQueen].bitBoard) != 0) return true;

        //Attack by rook
        attackBoard = MakeRookMove(square).bitBoard;
        if((attackBoard & pieceBitboards[BlackRook].bitBoard) != 0 || (attackBoard & pieceBitboards[BlackQueen].bitBoard) != 0) return true;
    }
    else {
        //Attack by pawn
        if(square > 7 && square % 8 < 7 && Board[square - 7] == WhitePawn) return true;
        if(square > 7 && square % 8 > 0 && Board[square - 9] == WhitePawn) return true;

        //Attack by king
        if((MakeKingMoveNoCastling(square).bitBoard & pieceBitboards[WhiteKing].bitBoard) != 0) return true;

        //Attack by knight
        if((MakeKnightMove(square).bitBoard & pieceBitboards[WhiteKnight].bitBoard) != 0) return true;

        //Attack by bishop
        uint64_t attackBoard = MakeBishopMove(square).bitBoard; 
        if((attackBoard & pieceBitboards[WhiteBishop].bitBoard) != 0 || (attackBoard & pieceBitboards[WhiteQueen].bitBoard) != 0) return true;

        //Attack by rook
        attackBoard = MakeRookMove(square).bitBoard;
        if((attackBoard & pieceBitboards[WhiteRook].bitBoard) != 0 || (attackBoard & pieceBitboards[WhiteQueen].bitBoard) != 0) return true;
    }
    return false;
}

void Game::UnmakeMove(){          //Unmakes the latest move that was made
    if(moveStack.empty()) return;
    Move currentMove = moveStack.top();
    
    int movedPiece = Board[currentMove.destination];

    Player currentPlayer = (movedPiece % 2 == 0) ? Black : White;

    gameState = currentMove.moveGameState;

    if(currentMove.castledKingSide) {
        if(currentPlayer == White){     //Put the rook back in its right place
            MakeAnyMove(5, 7);
        }
        else{
            MakeAnyMove(61, 63);
        }
    }
    else if(currentMove.castledQueenSide) {
        if(currentPlayer == White){
            MakeAnyMove(3, 0);
        }
        else{
            MakeAnyMove(59, 56);
        }
    }
    else if(currentMove.enPassantMove) {
        if(currentPlayer == White){
            blackPiecesBB.Set(gameState.enPassant - 8);
            pieceBitboards[BlackPawn].Set(gameState.enPassant - 8);
            Board[gameState.enPassant - 8] = BlackPawn;
        }
        else{
            whitePiecesBB.Set(gameState.enPassant + 8);
            pieceBitboards[WhitePawn].Set(gameState.enPassant + 8);
            Board[gameState.enPassant + 8] = WhitePawn;
        }
    }
    else if(currentMove.promotion){
        pieceBitboards[Board[currentMove.destination]].Unset(currentMove.destination);
        Board[currentMove.destination] = currentPlayer == White ? WhitePawn : BlackPawn;    //If a promotion was made, change the destination square to a pawn. This pawn will then be moved when MakeAnyMove is called
    }

    MakeAnyMove(currentMove.destination, currentMove.origin);

    if(currentMove.capturedPiece != Empty){
        Board[currentMove.destination] = currentMove.capturedPiece;
        pieceBitboards[currentMove.capturedPiece].Set(currentMove.destination);
        if(currentMove.capturedPiece % 2 == 0) blackPiecesBB.Set(currentMove.destination);
        else whitePiecesBB.Set(currentMove.destination);
    }
    moveStack.pop();
}

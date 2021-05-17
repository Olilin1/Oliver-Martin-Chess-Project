#include"Game.hpp"

//Takes a string in Forsyth–Edwards Notation and uses it to setup the game.
void Game::SetupGame(std::string fen)
{
    for(int i = 0; i < 64; i++){
        Board[i] = 0;
    }

    gameState.awaitingPromotion = false;
    gameState.winner = None;

    std::stringstream ss(fen);
    std::string placement, color, castling, enPassant, halfMove, fullMove;
    ss >> placement >> color >> castling >> enPassant >> halfMove >> fullMove;

    int currentSquare = 56; //Fenwick notation starts placing pieces from the 8th row

    //Placement of pieces
    //TODO: Maybe refactor?
    for (char c : placement)
    {
        switch (c)
        {
        case 'p':
            Board[currentSquare] = BlackPawn;
            pieceBitboards[BlackPawn].Set(currentSquare);
            blackPiecesBB.Set(currentSquare);
            currentSquare++;
            break;
        case 'r':
            Board[currentSquare] = BlackRook;
            pieceBitboards[BlackRook].Set(currentSquare);
            blackPiecesBB.Set(currentSquare);
            currentSquare++;
            break;
        case 'k':
            Board[currentSquare] = BlackKing;
            pieceBitboards[BlackKing].Set(currentSquare);
            blackPiecesBB.Set(currentSquare);
            gameState.blackKingPos = currentSquare;
            currentSquare++;
            break;
        case 'q':
            pieceBitboards[BlackQueen].Set(currentSquare);
            blackPiecesBB.Set(currentSquare);
            Board[currentSquare] = BlackQueen;
            currentSquare++;
            break;
        case 'b':
            pieceBitboards[BlackBishop].Set(currentSquare);
            blackPiecesBB.Set(currentSquare);
            Board[currentSquare] = BlackBishop;
            currentSquare++;
            break;
        case 'n':
            pieceBitboards[BlackKnight].Set(currentSquare);
            blackPiecesBB.Set(currentSquare);
            Board[currentSquare] = BlackKnight;
            currentSquare++;
            break;
        case 'P':
            pieceBitboards[WhitePawn].Set(currentSquare);
            whitePiecesBB.Set(currentSquare);
            Board[currentSquare] = WhitePawn;
            currentSquare++;
            break;
        case 'R':
            pieceBitboards[WhiteRook].Set(currentSquare);
            whitePiecesBB.Set(currentSquare);
            Board[currentSquare] = WhiteRook;
            currentSquare++;
            break;
        case 'K':
            pieceBitboards[WhiteKing].Set(currentSquare);
            whitePiecesBB.Set(currentSquare);
            Board[currentSquare] = WhiteKing;
            gameState.whiteKingPos = currentSquare;
            currentSquare++;
            break;
        case 'Q':
            pieceBitboards[WhiteQueen].Set(currentSquare);
            whitePiecesBB.Set(currentSquare);
            Board[currentSquare] = WhiteQueen;
            currentSquare++;
            break;
        case 'B':
            pieceBitboards[WhiteBishop].Set(currentSquare);
            whitePiecesBB.Set(currentSquare);
            Board[currentSquare] = WhiteBishop;
            currentSquare++;
            break;
        case 'N':
            pieceBitboards[WhiteKnight].Set(currentSquare);
            whitePiecesBB.Set(currentSquare);
            Board[currentSquare] = WhiteKnight;
            currentSquare++;
            break;
        case '/':
            currentSquare = 8 * (currentSquare/8 - 2);
            break;
        default:
            currentSquare += c-'0';
            break;
        }
    }

    //Whose turn it is
    if(color == "w") gameState.currentPlayer = White;
    else gameState.currentPlayer = Black;

    //Setup castling availability
    std::set<char> availability(castling.begin(), castling.end());
    gameState.whiteCanCastleKingSide = availability.count('K');
    gameState.whiteCanCastleQueenSide = availability.count('Q');
    gameState.blackCanCastleKingSide = availability.count('k');
    gameState.blackCanCastleQueenSide = availability.count('q');

    //enPassant availability
    if(enPassant == "-"){
        gameState.canEnPassant = false;
    }
    else{
        gameState.canEnPassant = true;
        gameState.enPassant = AlgebraicToSquare(enPassant);
    }

    try{
    //Halfmove clock
    gameState.halfMoveClock = std::stoi(halfMove);
    }
    catch(...){
    gameState.halfMoveClock = 0; 
    }

    try{
    //Halfmove clock
    gameState.fullMoveClock = std::stoi(fullMove);
    }
    catch(...){
    gameState.fullMoveClock = 0; 
    }
    //FullMoveClock
    
}

//Takes a square in algebraic notation and gives it as a square
int Game::AlgebraicToSquare(std::string s)
{
    int row, col;
    row = s[1] - '0';
    col = s[0] - 'a';
    return (row-1) * 8 + (col);
}

//Converts a square to Algebraic notation
std::string Game::SquareToAlgebraic(int s){
    char row = s/8 + '1';
    char col = s%8 + 'a';
    std::string ans = "  ";
    ans[0] = col;
    ans[1] = row;
    return ans;
}

//Converts a piece to Unicode
std::string Game::ConvertToUnicode(int p)
{
    switch (p)
    {
    case 2:
        return "\u2659";
    case 4:
        return "\u2656";
    case 6:
        return "\u2658";
    case 8:
        return "\u2657";
    case 10:
        return "\u2655";
    case 12:
        return "\u2654";
    case 1:
        return "\u265F";
    case 3:
        return "\u265C";
    case 5:
        return "\u265E";
    case 7:
        return "\u265D";
    case 9:
        return "\u265B";
    case 11:
        return "\u265A";
    default:
        return " ";
    }
}

void Game::PrintBoard(){
    for(int i = 56; i >= 0; i++){
        std::cout<<ConvertToUnicode(Board[i])<<" ";
        if(i == 7) break;
        if(i % 8 == 7) {
            std::cout<<std::endl;
            i -= 16;
            continue;
        }
    }
    std::cout<<std::endl;
}

int* Game::GetBoard(){
    return Board;
}

int Game::CurrPlayerKingPostion(){
    if(gameState.currentPlayer == White) return pieceBitboards[WhiteKing].LSBIndex();
    else return pieceBitboards[BlackKing].LSBIndex();
}

Player Game::oppositePlayer(){
    if(gameState.currentPlayer == White) return Black;
    else return White;
}

Player Game::pieceColor(int piece){
    if(piece % 2 == 0) return Black;
    else return White;
}

bool Game::awaitingPromotion(){
    return gameState.awaitingPromotion;
}

Piece Game::ConvertToColoredPiece(UncoloredPiece p){
    if(gameState.currentPlayer == White) return (Piece)p;
    else return (Piece) (p + 1);
}

Piece Game::ConvertToOppositeColoredPiece(UncoloredPiece p){
    if(gameState.currentPlayer == White) return (Piece)(p+1);
    else return (Piece) p;
}

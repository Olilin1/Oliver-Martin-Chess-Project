#include "Game.hpp"

//Takes a string in Forsyth–Edwards Notation and uses it to setup the game.
void Game::SetupGame(std::string fen)
{
    for(int i = 0; i < 8; i++){
        for(int j = 0; j<8; j++){
            board[{i,j}] = Empty;
        }
    }

    gameState.awaitingPromotion = false;

    std::stringstream ss(fen);
    std::string placement, color, castling, enPassant, halfMove, fullMove;
    ss >> placement >> color >> castling >> enPassant >> halfMove >> fullMove;

    int row = 7, col = 0; //Fenwick notation starts placing pieces from the 8th row

    //Placement of pieces
    //TODO: Maybe refactor?
    for (char c : placement)
    {
        switch (c)
        {
        case 'p':
            board[{row,col}] = BlackPawn;
            col++;
            break;
        case 'r':
            board[{row,col}] = BlackRook;
            col++;
            break;
        case 'k':
            board[{row,col}] = BlackKing;
            gameState.blackKingPos = {row,col};
            col++;
            break;
        case 'q':
            board[{row,col}] = BlackQueen;
            col++;
            break;
        case 'b':
            board[{row,col}] = BlackBishop;
            col++;
            break;
        case 'n':
            board[{row,col}] = BlackKnight;
            col++;
            break;
        case 'P':
            board[{row,col}] = WhitePawn;
            col++;
            break;
        case 'R':
            board[{row,col}] = WhiteRook;
            col++;
            break;
        case 'K':
            board[{row,col}] = WhiteKing;
            gameState.whiteKingPos = {row,col};
            col++;
            break;
        case 'Q':
            board[{row,col}] = WhiteQueen;
            col++;
            break;
        case 'B':
            board[{row,col}] = WhiteBishop;
            col++;
            break;
        case 'N':
            board[{row,col}] = WhiteKnight;
            col++;
            break;
        case '/':
            col = 0;
            row--;
            break;
        default:
            col += c-'0';
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

    //Halfmove clock
    gameState.halfMoveClock = std::stoi(halfMove);

    //FullMoveClock
    gameState.fullMoveClock = std::stoi(fullMove);
}
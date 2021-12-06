#pragma once
#include<random>
#include"Bitboard.hpp"
#include"GameState.hpp"
#include"RanksFilesBitboards.hpp"
#include"SearchParams.hpp"
#include"Move.hpp"
#include<iostream>
#include<cmath>
#include<sstream>
#include<set>
#include<stack>
#include<utility>

/*A class that handles all the logic for the game,
Board represents the board as a 1d array, gameState keeps track of misc things like player, castling, and so on
There are bitboards representing the locations of all white pieces, all black pieces, as well as a separate bitboard for each colored piece type.
These bitboards come in very handy when doing move generation.
Function explanations can be found at their definitions. Your IDE/Editor should have functionality to jump around between files.

Here is a quick little summary of how this program works
If you go through all the functions from top to bottom you should get a fairly good idea how the program is structured.
First, magic numbers are generated, using the calculated blocker masks and attack boards for bishops/rooks.
For more info about magic bitboards, check out these pages: https://www.chessprogramming.org/Magic_Bitboards and https://www.chessprogramming.org/Looking_for_Magics. For this, we
have used "plain magic bitboards".

After magic numbers are generated, and the attack boards for knight and kings are calculated, we can start calculating moves. For rooks and bishops, this is done by obtaining
the magic number corresponding to the current board state and then using that magic number as an index into one of the arrays BishopAttacks[64][512] or RookAttacks[64][4096].
For kings and knights, each of the 64 squares has a unique set of possible moves, which are stored in KingAttacks[64] and KnightAttacks[64]. AFter we have our attack board
for the current piece, we take the intersection of that attackboard and the bitboard of all friendly pieces (whitePiecesBB or blackPiecesBB depending on current player).

For pawns, we calculate all possible moves for all pawns at the same time, by shifting the positions of the pawns in different ways. For example, left shifting the bitboards containing
all white pawns 8 steps corresponds to them moving 1 step forward. Then intersecting them with the inverse of all pieces removes the one step moves that are blocked.

Calculating if a square is attacked is very simple with bitboards. For each piece, you calculate the moves which that piece would be able to do from that square. Then you look
if those moves intersect with the bitboard corresponding to the enemy type of that piece. Then you do this for each piece.
*/

class Game{
private:
    #define inf 1000000

    EngineMode mode;
    bool debugMode;
    Bitboard pieceBitboards[13];
    Bitboard whitePiecesBB;
    Bitboard blackPiecesBB;
    int Board[64];
    GameState gameState;
    RanksFilesBitboards ranksAndFiles;
    std::stack<Move> moveStack;
public:
    //-------------------------------------------------Miscellanious helper functions----------------------------------------------------

    Game();
    void SetupGame(std::string fen);
    int AlgebraicToSquare(std::string algebraicString);
    int CurrPlayerKingPostion();
    Player oppositePlayer();
    Player pieceColor(int piece);
    Player getWinner();
    std::string SquareToAlgebraic(int s);
    std::string ConvertToUnicode(int p);
    Piece ConvertToColoredPiece(UncoloredPiece p);
    Piece ConvertToOppositeColoredPiece(UncoloredPiece p);
    bool awaitingPromotion();
    int* GetBoard();
    void PrintBoard();
    bool GameIsOver();
    std::pair<int,int> intToPair(int square);
    void setMode(EngineMode mode);
    std::string moveToLongNotation(Move move);
    std::string pieceToLongNotation(Piece p);
    void setDebugMode(bool on);

    //-------------------------------------------------Calculate board masks/attack boards/magic numbers----------------------------------------------------

    //Contains the possible attacks for kings and knights
    Bitboard KingAttacks[64];
    Bitboard KnightAttacks[64];
    void GenerateKingAttackBoards();
    void GenerateKnightAttackBoards();

    //The magic numbers that, when multiplied with a blocker board and then right shifted a certain amount, gives a unique index to the attack board for that blocker board
    uint64_t BishopMagicNumbers[64];
    uint64_t RookMagicNumbers[64];

    //Contains all possible bishop and rook attacks. These will be indexed into through a magic number
    Bitboard BishopAttacks[64][512];
    Bitboard RookAttacks[64][4096];

    //Blocker masks that are used to perform an AND operation with occupancy bitboards to obtain the relevant blocker board (which is then magic hashed into an attack board)
    Bitboard BishopBlockerMasks[64];
    Bitboard RookBlockerMasks[64];

    //Functions to generate the blocker boards for bishops and rooks
    void GenerateBishopBlockerMasks();
    void GenerateRookBlockerMasks();

    Bitboard GenerateBlockerBoard(Bitboard blockerMask, int index);

    void GenerateBlockerBoards(Bitboard rookBlockerBoards[64][4096], Bitboard bishopBlockerBoards[64][512]);

    void GenerateBishopAttackBoards(Bitboard bishopBlockerBoards[64][512], Bitboard bishopAttackBoards[64][512]);
    void GenerateRookAttackBoards(Bitboard rookBlockerBoards[64][4096], Bitboard rookAttackBoards[64][4096]);

    uint64_t GenerateBishopMagicNumbers(int square, Bitboard bishopBlockerBoards[512], Bitboard bishopAttackBoards[512]);
    uint64_t GenerateRookMagicNumbers(int square, Bitboard rookBlockerBoards[4096], Bitboard rookAttackBoards[4096]);

    void AssignMagicNumbers();

    //-----------------------------------------------Use the tables calculated in previous section to calculate moves very efficiently-----------------------------------------

    Bitboard GetAttackBishopBoardFromMagic(int originSquare);
    Bitboard GetAttackBishopBoardFromMagic(int originSquare, Bitboard occupancy);
    Bitboard GetAttackRookBoardFromMagic(int originSquare);
    Bitboard GetAttackRookBoardFromMagic(int originSquare, Bitboard occupancy);

    //All of these functions return a bitboard with all possible moves from originSquare
    Bitboard MakeBishopMove(int originSquare);

    Bitboard MakeRookMove(int originSquare);

    Bitboard MakeQueenMove(int originSquare);

    Bitboard MakeKingMove(int originSquare);
    Bitboard MakeKingMoveNoCastling(int originSquare);

    Bitboard MakeKnightMove(int originSquare);

    //-----------------------------------------------Use the attack bitboards calculated previously and convert them to a set of moves-----------------------------------------

    //Calculates all possible pawn moves and pawn attacks (note that these are pseudo moves and must be checked if they are legal later via MakeGameMove)
    //if(moveSet.count(selectedMove) && MakeGameMove(selectedMove) can be used to check if the player's move is legal
    void GeneratePawnAttackSet(std::set<std::pair<int, int>>& moveSet);

    void GenerateKingAttackSet(std::set<std::pair<int, int>>& moveSet);

    void GenerateKnightAttackSet(std::set<std::pair<int, int>>& moveSet);

    void GenerateRookAttackSet(std::set<std::pair<int, int>>& moveSet);

    void GenerateBishopAttackSet(std::set<std::pair<int, int>>& moveSet);

    void GenerateQueenAttackSet(std::set<std::pair<int, int>>& moveSet);

    //-----------------------------------------------Make an actual move and update the gamestate accordingly with the functions below----------------------------------------------

    bool MakeGameMove(int originSquare, int destinationSquare);         //MakeGameMove makes a legal move
    void MakeBoardMove(int originSquare, int destinationSquare, Piece promotion = Empty);        //MakeBoardMove makes a pseudo-legal move
    void MakeAnyMove(int originSquare, int destinationSquare);         //MakeAnyMove can make any move on board


    bool IsAttacked(int attackedSquare);      //Returns true if attackedSquare is attacked, false otherwise

    void UnmakeMove();          //Unmakes the latest game move that was made

    //-----------------------------------------------Using the legal moves calculated in the previous sections, calculate all possible moves----------------------------------------------

    void MakeAllPseudoMoves(std::set<std::pair<int, int>>& allMoves);     //Contains all pseudo moves

    void MakeAllLegalMoves(std::set<std::pair<int, int>>& allMoves);

    void MakeAllLegalMovesFromSquare(std::set<int>& allMoves, int square);

    void MakeAllCaptureMoves(std::set<std::pair<int, int>>& allMoves);

    uint64_t SumOfAllMoves(int depth, bool perftAnalysis);

    //-----------------------------------------------Using all the possible moves calculated, we can now use them to create an AI with a minimax algorithm----------------------------------------------

    int evaluatePosition();
    int PieceValue(int p);

    Move AiMove(search_parameters params = search_parameters());
    int miniMax(int depth, int alpha = 0, int beta = 0);

    int Quiescent(int alpha, int beta);
    int SEE(int originSquare, int destinationSquare);
    Bitboard attackAndDefend(Bitboard occupancy, int originSquare);

    //Arrays of 64, where each element in each array gives a value of how preferable it is that the specific piece is on that square.
    //These values are for white, for black simply take 63 - index to get the mirrored value.
    //The higher the value, the more preferable it is. The values in the tables are taken from https://www.chessprogramming.org/Simplified_Evaluation_Function
    int pawnPieceSquareTable[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        5, 10, 10, -20, -20, 10, 10, 5,
        5, -5, -10, 0, 0, -10, -5, 5,
        0, 0, 0, 20, 20, 0, 0, 0,
        5, 5, 10, 25, 25, 10, 5, 5,
        10, 10, 20, 30, 30, 20, 10, 10,
        50, 50, 50, 50, 50, 50, 50, 50,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    int knightPieceSquareTable[64] = {
        -50, -40, -30, -30, -30, -30, -40, -50,
        -40, -20, 0, 5, 5, 0, -20, -40,
        -30, 5, 10, 15, 15, 10, 5, -30,
        -30, 0, 15, 20, 20, 15, 0, -30,
        -30, 5, 15, 20, 20, 15, 5, -30,
        -30, 0, 10, 15, 15, 10, 0, -30,
        -40, -20, 0, 0, 0, 0, -20, -40,
        -50, -40, -30, -30, -30, -30, -40, -50
    };
    int bishopPieceSquareTable[64] = {
        -20, -10, -10, -10, -10, -10, -10, -20,
        -10, 5, 0, 0, 0, 0, 5, -10,
        -10, 10, 10, 10, 10, 10, 10, -10,
        -10, 0, 10, 10, 10, 10, 0, -10,
        -10, 5, 5, 10, 10, 5, 5, -10,
        -10, 0, 5, 10, 10, 5, 0, -10,
        -10, 0, 0, 0, 0, 0, 0, -10,
        -20, -10, -10, -10, -10, -10, -10, -20
    };
    int rookPieceSquareTable[64] = {
            0, 0, 0, 5, 5, 0, 0, 0,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            -5, 0, 0, 0, 0, 0, 0, -5,
            5, 10, 10, 10, 10, 10, 10, 5,
            0, 0, 0, 0, 0, 0, 0, 0
    };
    int queenPieceSquareTable[64] = {
        -20, -10, -10, -5, -5, -10, -10, -20,
        -10, 0, 0, 0, 0, 5, 0, -10,
        -10, 0, 5, 5, 5, 5, 5, -10,
        -5, 0, 5, 5, 5, 5, 0, 0,
        -5, 0, 5, 5, 5, 5, 0, -5,
        -10, 0, 5, 5, 5, 5, 0, -10,
        -10, 0, 0, 0, 0, 0, 0, -10,
        -20, -10, -10, -5, -5, -10, -10, -20
    };
    int kingPieceSquareTable[64] = {
        20, 30, 10, 0, 0, 10, 30, 20,
        20, 20, 0, 0, 0, 0, 20, 20,
        -10, -20, -20, -20, -20, -20, -20, -10,
        -20, -30, -30, -40, -40, -30, -30, -20,
        -30, -40, -40, -50, -50, -40, -40, -30,
        -30, -40, -40, -50, -50, -40, -40, -30,
        -30, -40, -40, -50, -50, -40, -40, -30,
        -30, -40, -40, -50, -50, -40, -40, -30
    };
};

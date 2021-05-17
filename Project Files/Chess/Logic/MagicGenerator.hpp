#include"Bitboard.hpp"

class MagicGenerator{
    //These represent all possible blocking piece combinations from each square on the board, for bishops and rooks respectively. This number will then be used to index into a table of
    Bitboard BishopBlockerBoards[64][512];
    Bitboard RookBlockerBoards[64][4096];

    //Functions to generate the blocker boards for bishops and rooks
    void GenerateBishopBlockerMasks();
    void GenerateRookBlockerMasks();

    Bitboard GenerateBlockerBoard(Bitboard blockerMask, int index);

    void GenerateBlockerBoards();

    Bitboard BishopAttackBoards[64][512];
    Bitboard RookAttackBoards[64][4096];
};
#include"Game.hpp"

void Game::GenerateBishopBlockerMasks(){
    for(int i = 0; i < 64; i++) {
        Bitboard currentBitboard;

        //Calculate all the possible bishop moves from the square with index i
        int j = i;
        while(j / 8 < 6 && j % 8 < 6) {
            currentBitboard.Set(j + 9);
            j += 9;
        }

        j = i;
        while(j / 8 < 6 && j % 8 > 1) {
            currentBitboard.Set(j + 7);
            j+=7;
        }

        j = i;
        while(j / 8 > 1 && j % 8 > 1) {
            currentBitboard.Set(j-9);
            j-=9;
        }

        j = i;
        while(j / 8 > 1 && j % 8 < 6) {
            currentBitboard.Set(j-7);
            j-=7;
        }

        BishopBlockerMasks[i] = currentBitboard;
    }
}

void Game::GenerateRookBlockerMasks(){
    for(int i = 0; i < 64; i++) {
        Bitboard currentBitboard;

        //Calculate all the possible rook moves from the square with index i
        int j = i;
        while(j / 8 < 6) {
            currentBitboard.Set(j + 8);
            j+=8;
        }

        j = i;
        while(j % 8 < 6) {
            currentBitboard.Set(j+1);
            j+=1;
        }

        j = i;
        while(j % 8 > 1) {
            currentBitboard.Set(j-1);
            j-=1;
        }

        j = i;
        while(j / 8 > 1) {
            currentBitboard.Set(j-8);
            j-=8;
        }

        RookBlockerMasks[i] = currentBitboard;
    }
}

Bitboard Game::GenerateBlockerBoard(Bitboard blockerMask, int index){
    int bitIndex = 0;       //bitIndex keeps track of the current bit in index. Index has the same length as the number of ones in the blockerMask, and the zeros in bitIndex determines what squares in blockerMask are blocked.
    for(int i = 0; i < 64; i++){
       if(blockerMask[i] == 1) {    //If the blocker mask has a 1-bit at index i, then this bit should be removed if it is 0 at bitindex in index. Otherwise, do nothing
            if((index & (1 << bitIndex)) == 0){
                blockerMask.Unset(i);
            }
            bitIndex++;
       }
    }
    return blockerMask;
}

void Game::GenerateBlockerBoards(Bitboard rookBlockerBoards[64][4096], Bitboard bishopBlockerBoards[64][512]){
    for(int i = 0; i < 64; i++) {
        //Generate rook blocker boards
        int numOfOnes = RookBlockerMasks[i].NumOfOnes();
        for(int j = 0; j < (1 << numOfOnes); j++) {
            rookBlockerBoards[i][j] = GenerateBlockerBoard(RookBlockerMasks[i], j);
        }

        //Generate bishop blocker boards
        numOfOnes = BishopBlockerMasks[i].NumOfOnes();
        for(int j = 0; j < (1 << numOfOnes); j++) {
            bishopBlockerBoards[i][j] = GenerateBlockerBoard(BishopBlockerMasks[i], j);
        }
    }
}
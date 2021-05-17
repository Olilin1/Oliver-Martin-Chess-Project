#include"Game.hpp"

void Game::GenerateBishopAttackBoards(Bitboard bishopBlockerBoards[64][512], Bitboard bishopAttackBoards[64][512]){
    for(int i = 0; i < 64; i++) {
        int numOfOnes = BishopBlockerMasks[i].NumOfOnes();

        for(int p = 0; p < (1 << numOfOnes); p++) {
            Bitboard currentBitboard;
            //Calculate all the possible bishop moves from the square with index i, when there are blocking pieces corresponding to index p
            int j = i;
            while(j / 8 < 7 && j % 8 < 7) {
                currentBitboard.Set(j + 9);
                j += 9;
                if(bishopBlockerBoards[i][p][j] == 0) break;        //If the blocker board corresponding to square i with index p, is zero at position j, then break
            }

            j = i;
            while(j / 8 < 7 && j % 8 > 0) {
                currentBitboard.Set(j + 7);
                j+=7;
                if(bishopBlockerBoards[i][p][j] == 0) break;
            }

            j = i;
            while(j / 8 > 0 && j % 8 > 0) {
                currentBitboard.Set(j-9);
                j-=9;
                if(bishopBlockerBoards[i][p][j] == 0) break;
            }

            j = i;
            while(j / 8 > 0 && j % 8 < 7) {
                currentBitboard.Set(j-7);
                j-=7;
                if(bishopBlockerBoards[i][p][j] == 0) break;
            }
            bishopAttackBoards[i][p] = currentBitboard;         //Set the bishop attack board from square i with blocking pieces corresponding to index p
        }
    }
}

void Game::GenerateRookAttackBoards(Bitboard rookBlockerBoards[64][4096], Bitboard rookAttackBoards[64][4096]){
    for(int i = 0; i < 64; i++){
        int numOfOnes = RookBlockerMasks[i].NumOfOnes();

        for(int p = 0; p < (1 << numOfOnes); p++){
            Bitboard currentBitboard;

            //Same principle as GenerateBishopAttackBoards but for rooks
            int j = i;
            while(j / 8 < 7) {
                currentBitboard.Set(j + 8);
                j+=8;
                if(rookBlockerBoards[i][p][j] == 0) break;
            }

            j = i;
            while(j % 8 < 7) {
                currentBitboard.Set(j+1);
                j+=1;
                if(rookBlockerBoards[i][p][j] == 0) break;
            }

            j = i;
            while(j % 8 > 0) {
                currentBitboard.Set(j-1);
                j-=1;
                if(rookBlockerBoards[i][p][j] == 0) break;
            }

            j = i;
            while(j / 8 > 0) {
                currentBitboard.Set(j-8);
                j-=8;
                if(rookBlockerBoards[i][p][j] == 0) break;
            }

            rookAttackBoards[i][p] = currentBitboard;
        }
    }
}

int count_1s(uint64_t b) {
  int r;
  for(r = 0; b; r++, b &= b - 1);
  return r;
}

uint64_t random_uint64() {
  uint64_t u1, u2, u3, u4;
  u1 = (uint64_t)(random()) & 0xFFFF; u2 = (uint64_t)(random()) & 0xFFFF;
  u3 = (uint64_t)(random()) & 0xFFFF; u4 = (uint64_t)(random()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

uint64_t random_uint64_fewbits() {
  return random_uint64() & random_uint64() & random_uint64();
}

/*This function generates a magic number for either bishops or rooks. 
The function works by looping through a bunch of random numbers, and for each random numbers, testing if it is a viable magic number
The thing that determines if it is a viable magic number is if it maps each separate blocker board to a unique index between 0 and numOfBits, 
where numOfBits is the number of bits contained in the blocker board's corresponding blocker mask
*/
uint64_t Game::GenerateBishopMagicNumbers(int square, Bitboard bishopBlockerBoards[512], Bitboard bishopAttackBoards[512]){
    Bitboard blockerMask = BishopBlockerMasks[square];

    int numOfOnes = blockerMask.NumOfOnes();

    uint64_t usedNumbers[512];

    for(int i = 0; i < 10000000;i++){
        uint64_t magicNumber = random_uint64_fewbits();
        if(count_1s((blockerMask.bitBoard * magicNumber) & 0xFF00000000000000ULL) < 6) continue;        //Mask out the last 8 bits
        for(int j = 0; j < 512; j++) usedNumbers[j] = 0;    //Reset the magic numbers before each new iteration
        int fail = 0;
        for(int j = 0; j < (1<<numOfOnes) && !fail; j++){
            uint64_t preShiftIndex = magicNumber * bishopBlockerBoards[j].bitBoard;
            int magicIndex = preShiftIndex>>55;        //Shift the preShiftIndex 55 steps to the right in order to get the actual index

            if(usedNumbers[magicIndex] == 0) {
                usedNumbers[magicIndex] = bishopAttackBoards[j].bitBoard;
            }
            else if(usedNumbers[magicIndex] != bishopAttackBoards[j].bitBoard) {
                fail = 1;
            }
        } 
        if(!fail) return magicNumber;       //A magic number was found
    }
    std::cout<<"Failed magic number generation"<<std::endl;
    return 0;
}

uint64_t Game::GenerateRookMagicNumbers(int square, Bitboard rookBlockerBoards[4096], Bitboard rookAttackBoards[4096]){
    Bitboard blockerMask = RookBlockerMasks[square];

    int numOfOnes = blockerMask.NumOfOnes();

    uint64_t usedNumbers[4096];

    for(int i = 0; i < 1000000;i++){
        uint64_t magicNumber = random_uint64_fewbits();
        if(count_1s((blockerMask.bitBoard * magicNumber) & 0xFFF0000000000000ULL) < 6) continue;
        for(int j = 0; j < 4096; j++) usedNumbers[j] = 0;
        int fail = 0;
        for(int j = 0; j < (1<<numOfOnes) && !fail; j++){
            uint64_t preShiftIndex = magicNumber * rookBlockerBoards[j].bitBoard;
            int magicIndex = preShiftIndex>>52; 

            if(usedNumbers[magicIndex] == 0) {
                usedNumbers[magicIndex] = rookAttackBoards[j].bitBoard;
            }
            else if(usedNumbers[magicIndex] != rookAttackBoards[j].bitBoard) {
                fail = 1;
            }
        } 
        if(!fail) return magicNumber;
    }
    std::cout<<"Failed magic number generation"<<std::endl;
    return 0;
}

void Game::AssignMagicNumbers(){
    Bitboard rookAttackBoards[64][4096];
    Bitboard bishopAttackBoards[64][512]; 
    Bitboard bishopBlockerBoards[64][512];
    Bitboard rookBlockerBoards[64][4096];
    
    GenerateRookBlockerMasks();
    GenerateBishopBlockerMasks();
    GenerateBlockerBoards(rookBlockerBoards, bishopBlockerBoards);
    GenerateRookAttackBoards(rookBlockerBoards, rookAttackBoards);
    GenerateBishopAttackBoards(bishopBlockerBoards, bishopAttackBoards);  

    for(int i = 0; i < 64; i++){
        BishopMagicNumbers[i] = GenerateBishopMagicNumbers(i, bishopBlockerBoards[i], bishopAttackBoards[i]); 
        int numOfOnes = BishopBlockerMasks[i].NumOfOnes();
        for(int j = 0; j  < (1<<numOfOnes); j++){
            uint64_t index;
            index = bishopBlockerBoards[i][j].bitBoard * BishopMagicNumbers[i];
            index >>= 55; 
            BishopAttacks[i][index] = bishopAttackBoards[i][j];
        }

        RookMagicNumbers[i] = GenerateRookMagicNumbers(i, rookBlockerBoards[i], rookAttackBoards[i]); 
        numOfOnes = RookBlockerMasks[i].NumOfOnes();
        for(int j = 0; j  < (1<<numOfOnes); j++){
            uint64_t index;
            index = rookBlockerBoards[i][j].bitBoard * RookMagicNumbers[i];
            index >>= 52; 
            RookAttacks[i][index] = rookAttackBoards[i][j];
        } 
    }
}
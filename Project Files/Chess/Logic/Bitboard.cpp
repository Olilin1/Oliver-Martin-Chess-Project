#include"Bitboard.hpp"
#include<iostream>
#include<bitset>
#include <sstream>

Bitboard::Bitboard() {
    bitBoard = 0;
}

Bitboard::Bitboard(uint64_t bb){
    bitBoard = bb;
}

void Bitboard::Set(int index){ 
    bitBoard |= ((uint64_t)1 << index);
}

void Bitboard::Unset(int index) {
    bitBoard &= ~((uint64_t)1 << index); 
}

const int lsb_64_table[64] =
{
   63, 30,  3, 32, 59, 14, 11, 33,
   60, 24, 50,  9, 55, 19, 21, 34,
   61, 29,  2, 53, 51, 23, 41, 18,
   56, 28,  1, 43, 46, 27,  0, 35,
   62, 31, 58,  4,  5, 49, 54,  6,
   15, 52, 12, 40,  7, 42, 45, 16,
   25, 57, 48, 13, 10, 39,  8, 44,
   20, 47, 38, 22, 17, 37, 36, 26
};

//A sort of hashing functions that map each possible LSB to its corresponding LSB index (thanks to https://www.chessprogramming.org/BitScan)
int Bitboard::LSBIndex(){
    unsigned int folded;
    uint64_t bb = bitBoard;
    bb ^= bb - 1;
    folded = (int) bb ^ (bb >> 32);
    return lsb_64_table[folded * 0x78291ACF >> 26];
}

int Bitboard::LSB(){
     //The two's complement of a number can be obtained through the one's complementing (the inverted number), added with 1
     //Because of this, the added one will be carried to the spot where the first one in the original number is(where the two's complement is zero), and this is the spot of the first 1 (the LSB)
    return (bitBoard & -bitBoard);     
}

int Bitboard::MSB(){
    return 0;
}

int Bitboard::NumOfOnes(){
    int count = 0;
    uint64_t bitBoardCopy = bitBoard;
    while(bitBoardCopy) {
        uint64_t LSB = bitBoardCopy & -bitBoardCopy;     
        bitBoardCopy ^= LSB;      //Set LSB to 0
        count++;
    }
    return count;
}

std::string Bitboard::ToString(){
    std::string parsedBitboard;
    for(int i = 7; i >= 0; i--) {
        for(int j = 0; j < 8; j++) {
            uint64_t currentBit = (uint64_t)1 << (8*i + j);
            if(currentBit & bitBoard){
                parsedBitboard.append("1 ");
            }
            else{
                parsedBitboard.append("0 ");
            }
        }
        parsedBitboard.append("\n"); 
    }
    return parsedBitboard;
}

int Bitboard::operator [](int i) const{
    if(bitBoard & ((uint64_t)1<<i)) return 1;
    return 0;
}

int Bitboard::popLSB(){
    int lsb = LSBIndex();
    bitBoard &= bitBoard-1;
    return lsb;
}
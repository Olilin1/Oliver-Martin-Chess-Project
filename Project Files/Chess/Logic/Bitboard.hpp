#include<stdint.h>
#include<string>

#pragma once

class Bitboard {
public:
    uint64_t bitBoard;      //The actual bitboard

    Bitboard();

    void Set(int index);    //Sets the bit at position index to 1
    int LSB();          //Returns position of least significant bit
    int MSB();          //Returns position of most significant bit
    int NumOfOnes();    //Returns number of ones in the bitboard
    std::string ToString();        //Returns a string that shows the bitboard
};

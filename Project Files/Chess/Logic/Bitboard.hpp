#pragma once
#include<stdint.h>
#include<string>

class Bitboard {
public:
    uint64_t bitBoard;      //The actual bitboard

    Bitboard();
    Bitboard(uint64_t bb);

    void Set(int index);    //Sets the bit at position index to 1
    void Unset(int index);  //Sets the bit at position index to 0
    void Clear();
    int LSB();          //Returns position of least significant bit
    int LSBIndex();     //Returns the index of the least significant bit
    int popLSB();       //Removes the LSB and returns it
    int MSB();          //Returns position of most significant bit
    int NumOfOnes();    //Returns number of ones in the bitboard
    std::string ToString();        //Returns a string that shows the bitboard

    int operator [](int i) const;
};
#include"Bitboard.hpp"

Bitboard::Bitboard() {
    bitBoard = 0;
}

void Bitboard::Set(int index){
    uint64_t tempBitBoard = 1 << index;
    bitBoard |= tempBitBoard;
}

int Bitboard::LSB(){

}

int Bitboard::MSB(){

}

int Bitboard::NumOfOnes(){
    int count = 0;
    for(int i = 0; i < 64; i++) {       //At each iteration of the loop, left shift a temporary number i times, and then take the intersection of that number with the bitBoard. If they intersect, then the bitBoard is 1 at that position
        uint64_t index = 1 << i;
        if(index && bitBoard) {
            count++;
        }
    }
    return count;
}

std::string Bitboard::ToString(){
    std::string parsedBitboard;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int currentBit = 1 << (8*i + j);
            if(currentBit && bitBoard){
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

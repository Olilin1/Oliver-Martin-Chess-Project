#include"Game.hpp"

void Game::GenerateBishopBlockerBoards(){
    for(int i = 0; i < 64; i++) {
        Bitboard currentBitboard;

        //Calculate all the possible bishop moves from the square with index i
        int j = i;
        while((j + 9) / 8 < 7 && (j + 9) % 8 < 7) {
            currentBitboard.Set(j + 9);
        }

        j = i;
        while((j + 7) / 8 < 7 && (j + 7) % 8 > 0) {
            currentBitboard.Set(j + 7);
        }

        j = i;
        while((j - 9) / 8 > 0 && (j - 9) % 8 > 0) {
            currentBitboard.Set(j-9);
        }

        j = i;
        while((j - 7) / 8 > 0 && (j - 7) % 8 < 7) {
            currentBitboard.Set(j-7);
        }

        BishopBlockerBoards[i] = currentBitboard;
    }
}

void Game::GenerateRookBlockerBoards(){
    for(int i = 0; i < 64; i++) {
        Bitboard currentBitboard;

        //Calculate all the possible rook moves from the square with index i
        int j = i;
        while((j + 8) / 8 < 7) {
            currentBitboard.Set(j + 8);
        }

        j = i;
        while((j + 1) % 8 < 7) {
            currentBitboard.Set(j+1);
        }

        j = i;
        while((j - 1) % 8 > 0) {
            currentBitboard.Set(j-1);
        }

        j = i;
        while((j - 8) / 8 > 0) {
            currentBitboard.Set(j-8);
        }

        BishopBlockerBoards[i] = currentBitboard;
    }
}

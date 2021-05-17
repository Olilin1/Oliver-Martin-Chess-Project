#include"Game.hpp"

void Game::GenerateKingAttackBoards(){
    for(int originSquare = 0; originSquare < 64; originSquare++){
        Bitboard availableMoves;
        if(originSquare % 8 < 7){   //1 right
            availableMoves.Set(originSquare + 1);
        }
        if(originSquare % 8 > 0){   //1 left
            availableMoves.Set(originSquare - 1);
        }
        if(originSquare / 8 < 7){   //1 up
            if(originSquare % 8 < 7){   //1 right
                availableMoves.Set(originSquare + 9);
            }
            if(originSquare % 8 > 0){   //1 left
                availableMoves.Set(originSquare + 7);
            }
            availableMoves.Set(originSquare + 8);
        }
        if(originSquare / 8 > 0){   //1 down
            if(originSquare % 8 < 7){   //1 right
                availableMoves.Set(originSquare - 7);
            }   
            if(originSquare % 8 > 0){   //1 left
                availableMoves.Set(originSquare - 9);
            }
            availableMoves.Set(originSquare - 8);
        }
        KingAttacks[originSquare] = availableMoves;
    }
}

void Game::GenerateKnightAttackBoards(){
    for(int originSquare = 0; originSquare < 64; originSquare++){
        Bitboard availableMoves;
        if(originSquare % 8 < 7 && originSquare / 8 < 6){   //2 up, 1 right
            availableMoves.Set(originSquare + 17);
        }
        if(originSquare % 8 < 6 && originSquare / 8 < 7){   //1 up, 2 right
            availableMoves.Set(originSquare + 10);
        }
        if(originSquare % 8 < 6 && originSquare / 8 > 0){   //1 down, 2 right
            availableMoves.Set(originSquare - 6);
        }   
        if(originSquare % 8 < 7 && originSquare / 8 > 1){   //2 down, 1 right
            availableMoves.Set(originSquare - 15);
        }
        if(originSquare % 8 > 0 && originSquare / 8 > 1){   //2 down, 1 left
            availableMoves.Set(originSquare - 17);
        }
        if(originSquare % 8 > 1 && originSquare / 8 > 0){   //1 down, 2 left
            availableMoves.Set(originSquare - 10);
        }
        if(originSquare % 8 > 1 && originSquare / 8 < 7){   //1 up, 2 left
            availableMoves.Set(originSquare + 6);
        }
        if(originSquare % 8 > 0 && originSquare / 8 < 6){   //2 up, 1 left
            availableMoves.Set(originSquare + 15);
        }
        KnightAttacks[originSquare] = availableMoves;
    } 
}
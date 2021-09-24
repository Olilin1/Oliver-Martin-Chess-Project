#include"Game.hpp"

Game::Game(){
    AssignMagicNumbers();
    GenerateKingAttackBoards();
    GenerateKnightAttackBoards();
    mode = NORMAL;
}

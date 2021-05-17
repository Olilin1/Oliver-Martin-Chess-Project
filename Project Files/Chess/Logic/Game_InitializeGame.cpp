#include"Game.hpp"

Game::Game(){
    AssignMagicNumbers();
    GenerateKingAttackBoards();
    GenerateKnightAttackBoards();
    SetupGame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    PrintBoard();
}

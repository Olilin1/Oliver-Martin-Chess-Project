#include"Game.hpp"

const std::string Game::name = "GM Gullefjun";
const std::string Game::author = "Oliver Lindgren & Martin Orrje";

Game::Game(){
    AssignMagicNumbers();
    GenerateKingAttackBoards();
    GenerateKnightAttackBoards();
    mode = NORMAL;
    debugMode = false;
}

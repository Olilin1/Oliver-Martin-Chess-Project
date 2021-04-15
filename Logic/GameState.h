#ifndef GAMESTATE
#define GAMESTATE

struct GameState {
    int blackKingPos;
    int whiteKingPos;
    int blackEnPassant;
    int whiteEnPassant;
    bool blackCanEnPassant;
    bool whiteCanEnPassant;
    bool whiteCanCastle;
    bool blackCanCastle;
};

#endif
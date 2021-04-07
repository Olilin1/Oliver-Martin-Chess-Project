struct GameState {
    int blackKingPos;
    int whiteKingPos;
    int blackEnPassant;     //If black can do en passant, then the first element of this pair tells whether black has en passant, and the second coordinate is the square that black can capture with en passant
    int whiteEnPassant;
    bool blackCanEnPassant;
    bool whiteCanEnPassant;
    bool whiteCanCastle;
    bool blackCanCastle;
};
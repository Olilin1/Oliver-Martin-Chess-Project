#pragma once

    #include"Typedefs.hpp"
    #include"Enums.hpp"
    #include<string>
    
    square AlgebraicToSquare(std::string);
    std::string SquareToAlgebraic(square);
    Player pieceColor(Piece);
    Piece pieceType(Piece);
    bool isBlackPiece(Piece);
    bool isWhitePiece(Piece);
    bool OnBoard(square);
    std::string ConvertToUnicode(Piece i);
    Player oppositePlayer(Player);

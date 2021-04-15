#pragma once
#include<array>
#include<iostream>
#include<unordered_map>
#include"GameState.h"
#include"Enums.hpp"
#include<assert.h>



class Board {
private:
    std::array<Piece, 64> boardArray;     //The actual chess board
    std::unordered_map<int, Piece> whitePositions;    //Maps each board position to a white piece. This makes it so we don't have to iterate over the whole board when calculating all possible moves
    std::unordered_map<int, Piece> blackPositions;  
public:  
    GameState gameState;
    Board() {
        //Populate board with starting positions
        gameState.currentPlayer = White;
        gameState.blackCanCastle = true;
        gameState.whiteCanCastle = true;
        gameState.blackCanEnPassant = false;
        gameState.whiteCanEnPassant = false;
        gameState.blackKingPos = 60;
        gameState.whiteKingPos = 4;
        boardArray.fill(Empty);
        PopulateBoard(boardArray);
        for(int i = 0; i < 16; i++) {
            whitePositions.emplace(i, boardArray[i]);
        } 
        for(int j = 48; j < 64; j++) {
            blackPositions.emplace(j, boardArray[j]);
        }
 
    }

    void PrintBoard() {
        for(int i = 7; i >= 0; i--){
            for(int j = 0; j < 8; j++) {
                if(boardArray[i*8 + j]) {
                    std::cout<<ConvertToUnicode(boardArray[i*8 + j]);
                }
                else if(!((i + j) % 2)) {
                    std::cout<<"#";
                }
                else {
                    std::cout<<" ";
                }
                std::cout<<" ";
            }
            std::cout<<std::endl;
        }
    }

    void PopulateBoard(std::array<Piece, 64>& boardArray) {
        PopulatePawns(boardArray);
        PopulateRowOne(boardArray);
        PopulateRowEight(boardArray);
    }

    //Populates the pawns on each side of the board
    void PopulatePawns(std::array<Piece, 64>& boardArray) {
        for(int i = 1; i < 8; i+=5) {
            for(int j = 0; j < 8; j++) {
                if(i==1) {
                    boardArray[i*8 + j] = WhitePawn;
                    whitePositions[i*8+j] = WhitePawn;
                }
                else if(i == 6) {
                    boardArray[i*8 + j] = BlackPawn;
                }
                else boardArray[i*8 + j] = BlackPawn;
            }
        } 
    }

    //Populate the pieces that are not pawns on each side
    void PopulateRowOne(std::array<Piece, 64>& boardArray) {
        boardArray[0] = boardArray[7] = WhiteRook;     
        boardArray[1] = boardArray[6] = WhiteKnight;    
        boardArray[2] = boardArray[5] = WhiteBishop;     
        boardArray[3] = WhiteQueen;    
        boardArray[4] = WhiteKing;      
    }

    void PopulateRowEight(std::array<Piece, 64>& boardArray) {
        boardArray[(7) * 8] = boardArray[(7)*8 + 7] = BlackRook;     
        boardArray[(7)*8 + 1] = boardArray[(7)*8 + 6] = BlackKnight;    
        boardArray[(7)*8+2] = boardArray[(7)*8 + 5] = BlackBishop;     
        boardArray[(7)*8+3] = BlackQueen;    
        boardArray[(7)*8+4] = BlackKing;    
    }

        //Update and retrieve a copy of the board. Used to see if a move puts the king in check
    Board UpdateBoardCopy(std::pair<int, int> firstPos, std::pair<int, int> secondPos, Board boardCopy) {
        Piece pieceType = boardCopy.GetPieceType(firstPos.first, firstPos.second);
        boardCopy.UpdateBoard(firstPos, secondPos, pieceType);
        return boardCopy;
    }

    //Update the board's positions
    void UpdateBoard(std::pair<int, int> firstPos, std::pair<int, int> secondPos, Piece pieceType) {
        IfEnPassant(pieceType, firstPos, secondPos);
        boardArray[ConvertToSingle(firstPos.first, firstPos.second)] = Empty;
        boardArray[ConvertToSingle(secondPos.first, secondPos.second)] = pieceType;
        UpdateEnPassant(pieceType, firstPos, secondPos);
        UpdatePieceMap(firstPos, secondPos, pieceType);
        UpdateKingPosAfterMove(firstPos, secondPos, pieceType);
        if(pieceType == BlackRook || pieceType == BlackKing) gameState.blackCanCastle = false;           //If the player moves his rook or king, he can no longer castle
        else if(pieceType == WhiteRook || pieceType == WhiteKing) gameState.whiteCanCastle = false;
    }

    //This function checks if the current player made en passant, and if so, it deletes the piece that was captured from the en passant
    void IfEnPassant(Piece pieceType, std::pair<int, int> firstPos, std::pair<int, int> secondPos) {
        if(pieceType == BlackPawn && secondPos.second != firstPos.second) {
            if(GetPieceType(secondPos.first, secondPos.second) == Empty) {
                SetPiece(secondPos.first + 1, secondPos.second, Empty);
                whitePositions.erase(ConvertToSingle(secondPos.first + 1, secondPos.second));   
            }
        }
        else if(pieceType == WhitePawn && secondPos.second != firstPos.second) {
            if(GetPieceType(secondPos.first, secondPos.second) == Empty) {
                SetPiece(secondPos.first - 1, secondPos.second, Empty);
                blackPositions.erase(ConvertToSingle(secondPos.first - 1, secondPos.second));
            }
        }
    }

    //If any player moved two steps forward with their pawn, then the opposing player will have en passant next round
    void UpdateEnPassant(Piece pieceType, std::pair<int, int> firstPos, std::pair<int, int> secondPos) {
        if(pieceType ==  BlackPawn) {     //The move was by black
            if(secondPos.first == firstPos.first - 2) {
                gameState.whiteCanEnPassant = true;
                gameState.whiteEnPassant = ConvertToSingle(secondPos.first + 1, secondPos.second);      //Set whiteEnPassant to the square that white can move to if they decide to en passant next turn
            }
        }
        else if(pieceType == WhitePawn){
            if(secondPos.first == firstPos.first + 2) {
                gameState.blackCanEnPassant = true;
                gameState.blackEnPassant = ConvertToSingle(secondPos.first - 1, secondPos.second);
            }
        }
    }

    void UpdatePieceMap(std::pair<int, int> firstPos, std::pair<int, int> secondPos, Piece pieceType) {
        if(pieceType < 0) {    //it's black
            blackPositions.erase(ConvertToSingle(firstPos.first, firstPos.second)); 
            blackPositions[ConvertToSingle(secondPos.first, secondPos.second)] = pieceType;
        }
        else if(pieceType > 0) {
            whitePositions.erase(ConvertToSingle(firstPos.first, firstPos.second)); 
            whitePositions[ConvertToSingle(secondPos.first, secondPos.second)] = pieceType;
        }
    }

    void UpdateKingPosAfterMove(std::pair<int, int> firstPos, std::pair<int, int> secondPos, Piece pieceType) {
        if(pieceType == BlackKing) {
            if(abs(secondPos.second - firstPos.second) > 1) {     //This applies only if current move is a castling
                if(secondPos.second == 3) {
                    SetPiece(8, 1, Empty);
                    SetPiece(8, 4, BlackRook);
                    blackPositions.erase(ConvertToSingle(8, 1));
                    blackPositions[ConvertToSingle(8, 4)] = BlackRook;
                }
                else if(secondPos.second == 7) {
                    SetPiece(8, 8, Empty);
                    SetPiece(8, 6, BlackRook);
                    blackPositions.erase(ConvertToSingle(8, 8));
                    blackPositions[ConvertToSingle(8, 6)] = BlackRook;
                }
            } 
            gameState.blackKingPos = ConvertToSingle(secondPos.first, secondPos.second);     //Update the position of the black king if it was moved
        } 
        else if(pieceType == WhiteKing) {
           if(abs(secondPos.second - firstPos.second) > 1) {     //This applies only if current move is a castling
                if(secondPos.second == 3) {
                    SetPiece(1, 1, Empty);
                    SetPiece(1, 4, WhiteRook);
                    whitePositions.erase(ConvertToSingle(1, 1));
                    whitePositions[ConvertToSingle(1, 4)] = WhiteRook;
                }
                else if(secondPos.second == 7) {
                    SetPiece(1, 8, Empty);
                    SetPiece(1, 6, WhiteRook);
                    whitePositions.erase(ConvertToSingle(1, 8));
                    whitePositions[ConvertToSingle(1, 6)] = WhiteRook;
                }
            } 
            gameState.whiteKingPos = ConvertToSingle(secondPos.first, secondPos.second);     //Update the position of the white king if it was moved
        }
    }

    void NewTurn () {
        if(gameState.currentPlayer == White) {
            gameState.whiteCanEnPassant = false;
            gameState.currentPlayer = Black;
        }
        else if(gameState.currentPlayer == Black) {
            gameState.blackCanEnPassant = false;
            gameState.currentPlayer = White;
        }
    }

    //Retrieves the piece at the given coordinate
    Piece GetPieceType(int x, int y) {
        assert(x >= 1 && x <= 8 && y >= 1 && y <= 8);
        return boardArray[(x-1)*8 + y - 1];
    }

    void SetPiece(int x, int y, Piece pieceType) {
        assert(x >= 1 && x <= 8 && y >= 1 && y <= 8); 
        boardArray[(x - 1)*8 + (y - 1)] = pieceType;
    }

    int ConvertToSingle(int x, int y) {
        return (x-1)*8 + (y-1);
    }

    std::pair<std::unordered_map<int, Piece>::iterator, std::unordered_map<int, Piece>::iterator> getWhitePositions() {
        return {whitePositions.begin(), whitePositions.end()};
    }

    std::pair<std::unordered_map<int, Piece>::iterator, std::unordered_map<int, Piece>::iterator> getBlackPositions() {
        return {blackPositions.begin(), blackPositions.end()};
    }

    std::string ConvertToUnicode(int i) {
        switch(i) {
            case -1:
                return "\u2659";
            case -2:
                return "\u2656";
            case -3:
                return "\u2658";
            case -4:
                return "\u2657";
            case -5:
                return "\u2655";
            case -6:
                return "\u2654";
            case 1:
                return "\u265F";
            case 2:
                return "\u265C";
            case 3:
                return "\u265E";
            case 4:
                return "\u265D";
            case 5:
                return "\u265B";
            case 6:
                return "\u265A";
            default:
                return " ";
        }
    }
};
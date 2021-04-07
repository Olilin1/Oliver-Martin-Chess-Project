// #pragma once
// #include"Board.h"
// #include<memory>

// class BoardUpdater {
// private:
//     Board& chessBoard;
//     std::unique_ptr<GameState> gameState;
// public:
//     BoardUpdater(Board& board) : chessBoard(board) {
//         gameState = std::make_unique<GameState>(board.gameState);
//     }

//     void UpdateKingPosAfterMove(std::pair<int, int> firstPos, std::pair<int, int> secondPos, Piece pieceType) {
//         if(pieceType == BlackKing) {
//             if(abs(secondPos.second - firstPos.second) > 1) {     //This applies only if a castle occured last turn
//                 if(secondPos.second < 4) {
//                     chessBoard.SetPiece(8, 1, Empty);
//                     chessBoard.SetPiece(8, 3, BlackRook);
//                     gameState->blackPositions.erase(ConvertToSingle(8, 1));
//                     gameState->blackPositions[ConvertToSingle(8, 3)] = BlackRook;
//                 }
//                 else if(secondPos.second > 4) {
//                     chessBoard.SetPiece(8, 8, Empty);
//                     chessBoard.SetPiece(8, 6, BlackRook);
//                     gameState->blackPositions.erase(ConvertToSingle(8, 8));
//                     gameState->blackPositions[ConvertToSingle(8, 6)] = BlackRook;
//                 }
//             } 
//             gameState->blackKingPos = ConvertToSingle(secondPos.first, secondPos.second);     //Update the position of the black king if it was moved
//         } 
//         else if(pieceType == WhiteKing) {
//            if(abs(secondPos.second - firstPos.second) > 1) {     //This applies only if a castling occured last turn
//                 if(secondPos.second < 4) {
//                     chessBoard.SetPiece(1, 1, Empty);
//                     chessBoard.SetPiece(1, 3, WhiteRook);
//                     gameState->whitePositions.erase(ConvertToSingle(1, 1));
//                     gameState->whitePositions[ConvertToSingle(1, 3)] = WhiteRook;
//                 }
//                 else if(secondPos.second > 4) {
//                     chessBoard.SetPiece(1, 8, Empty);
//                     chessBoard.SetPiece(1, 6, WhiteRook);
//                     gameState->whitePositions.erase(ConvertToSingle(1, 8));
//                     gameState->whitePositions[ConvertToSingle(1, 6)] = WhiteRook;
//                 }
//             } 
//             gameState->whiteKingPos = ConvertToSingle(secondPos.first, secondPos.second);     //Update the position of the black king if it was moved
//         }
//     }

//     void IfEnPassant(Piece pieceType, std::pair<int, int> firstPos, std::pair<int, int> secondPos) {
//         if(pieceType == BlackPawn && secondPos.second != firstPos.second) {
//             if(chessBoard.GetPieceType(secondPos.first, secondPos.second) == Empty) {
//                 chessBoard.SetPiece(secondPos.first + 1, secondPos.second, Empty);
//                 gameState->whitePositions.erase(ConvertToSingle(secondPos.first + 1, secondPos.second));   
//             }
//         }
//         else if(pieceType == WhitePawn && secondPos.second != firstPos.second) {
//             if(chessBoard.GetPieceType(secondPos.first, secondPos.second) == Empty) {
//                 chessBoard.SetPiece(secondPos.first - 1, secondPos.second, Empty);
//                 gameState->blackPositions.erase(ConvertToSingle(secondPos.first - 1, secondPos.second));
//             }
//         }
//     }

//     //If any player moved two steps forward with their pawn, then the opposing player will have en passant next round
//     void UpdateEnPassant(Piece pieceType, std::pair<int, int> firstPos, std::pair<int, int> secondPos) {
//         if(pieceType ==  BlackPawn) {     //The move was by black
//             if(secondPos.first == firstPos.first - 2) {
//                 gameState->whiteCanEnPassant = true;
//                 gameState->whiteEnPassant = (secondPos.first)*8 + (secondPos.second-1);
//             }
//         }
//         else if(pieceType == WhitePawn){
//             if(secondPos.first == firstPos.first + 2) {
//                 gameState->blackCanEnPassant = true;
//                 gameState->blackEnPassant = (secondPos.first - 2)*8 + (secondPos.second - 1);
//             }
//         }
//     }

//     void UpdatePieceMap(std::pair<int, int> firstPos, std::pair<int, int> secondPos, Piece pieceType) {
//         if(pieceType < 0) {    //it's black
//             gameState->blackPositions.erase((firstPos.first-1)*8 + (firstPos.second-1)); 
//             gameState->blackPositions[ConvertToSingle(secondPos.first, secondPos.second)] = pieceType;
//         }
//         else if(pieceType > 0) {
//             gameState->whitePositions.erase((firstPos.first-1)*8 + (firstPos.second-1)); 
//             gameState->whitePositions[ConvertToSingle(secondPos.first, secondPos.second)] = pieceType;
//         }
//     }

//     int ConvertToSingle(int x, int y) {
//         return (x-1)*8 + (y-1);
//     }
// };
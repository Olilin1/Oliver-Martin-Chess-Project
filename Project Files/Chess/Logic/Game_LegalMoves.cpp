#include "game.hpp"

void Game::LegalMoves(square pos, std::set<square>& ref){
    if(gameState.awaitingPromotion) return; 
 switch (pieceType(board[pos]))
    {
    case Knight:
        LegalKnightMoves(pos, ref);
        break;
    case Bishop:
        LegalSlidingMoves(pos, bishopMoves, ref);
    break;
    case Queen:
        LegalSlidingMoves(pos, queenMoves, ref);
    break;
    case Rook:
        LegalSlidingMoves(pos, rookMoves, ref);
    break;
    case King:
        LegalKingMoves(pos, ref);
    break;
    case Pawn:
        LegalPawnMoves(pos, ref);
    break;
    default:
        break;
    }
}

void Game::LegalSlidingMoves(square pos, std::vector<std::pair<int, int>> directions, std::set<square>& moves)
{

    if (pieceColor(board[pos]) != gameState.currentPlayer)
        return;

    for (std::pair<int, int> p : directions)
    {
        for (int i = 1; i < 8; i++)
        {
            square newPos = {pos.first + p.first * i, pos.second + p.second * i};
            
            if (isLegal(pos, newPos))
                moves.insert(newPos);
            if(!IsEmpty(newPos)) break;
        }
    }
    return;
}

void Game::LegalKnightMoves(square pos, std::set<square>& moves)
{
    if (pieceType(board[pos]) != Knight)
       return;
    if (pieceColor(board[pos]) != gameState.currentPlayer)
        return;


    for (int i : {-2, -1, 1, 2})
    {
        for (int j : {-2, -1, 1, 2})
        {
            if (abs(i) == abs(j))
                continue;
            square newPos = {pos.first + i, pos.second + j};
            if (isLegal(pos, newPos))
                moves.insert(newPos);
        }
    }

   return;
}


void Game::LegalKingMoves(square pos, std::set<square>& moves)
{
    if (pieceColor(board[pos]) != gameState.currentPlayer)
        return;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            square newPos = {pos.first+i, pos.second+j};
            if(!canMove(newPos)) continue;
            Board newBoard = board;
            newBoard.MakeMove(pos, newPos);
            if(!newBoard.IsAttacked(newPos, oppositePlayer(gameState.currentPlayer))){
                moves.insert(newPos);
            }
        }
    }

    if (gameState.currentPlayer == Black)
    {   
        
        if (gameState.blackCanCastleKingSide &&
            IsEmpty({7, 5}) &&
            IsEmpty({7, 6}) &&
            !board.IsAttacked({7, 4}, White) &&
            !board.IsAttacked({7, 5}, White) &&
            !board.IsAttacked({7, 6}, White))
        {
            moves.insert({7, 6});
        }
        if (gameState.blackCanCastleQueenSide &&
            IsEmpty({7, 3}) &&
            IsEmpty({7, 2}) &&
            IsEmpty({7, 1}) &&
            !board.IsAttacked({7, 4}, White) &&
            !board.IsAttacked({7, 3}, White) &&
            !board.IsAttacked({7, 2}, White))
        {
            moves.insert({7, 2});
        }
    }
    else
    {
        if (gameState.whiteCanCastleKingSide &&
            IsEmpty({0, 5}) &&
            IsEmpty({0, 6}) &&
            !board.IsAttacked({0, 4}, Black) &&
            !board.IsAttacked({0, 5}, Black) &&
            !board.IsAttacked({0, 6}, Black))
        {
            moves.insert({0, 6});
        }
        if (gameState.whiteCanCastleQueenSide &&
            IsEmpty({0, 3}) &&
            IsEmpty({0, 2}) &&
            IsEmpty({0, 1}) &&
            !board.IsAttacked({0, 4}, Black) &&
            !board.IsAttacked({0, 3}, Black) &&
            !board.IsAttacked({0, 2}, Black))
        {
            moves.insert({0, 2});
        }
    }
    return;
}

void Game::LegalPawnMoves(square pos, std::set<square>& moves)
{
    if (pieceColor(board[pos]) != gameState.currentPlayer)
        return;

    int direction;
    if (gameState.currentPlayer == White)
        direction = 1;
    else
        direction = -1;
    if (pieceColor(board[{pos.first + direction * 1, pos.second - 1}]) == oppositePlayer(gameState.currentPlayer) && 
    isLegal(pos, {pos.first + direction * 1, pos.second - 1}))
        moves.insert({pos.first + direction * 1, pos.second - 1});
    if (pieceColor(board[{pos.first + direction * 1, pos.second + 1}]) == oppositePlayer(gameState.currentPlayer) && 
    isLegal(pos, {pos.first + direction * 1, pos.second + 1}))
        moves.insert({pos.first + direction * 1, pos.second + 1});
    if (IsEmpty({pos.first + direction * 1, pos.second}) && isLegal(pos, {pos.first + direction * 1, pos.second}))
        moves.insert({pos.first + direction * 1, pos.second});
    if (IsEmpty({pos.first + direction * 1, pos.second}) && IsEmpty({pos.first + direction * 2, pos.second}) && (pos.first == (pieceColor(board[pos]) == White ? 1 : 6)) && isLegal(pos, {pos.first + direction * 2, pos.second}))
        moves.insert({pos.first + direction * 2, pos.second});
    if (gameState.canEnPassant)
    {
        if (gameState.enPassant == std::make_pair(pos.first, pos.second - 1))
        {
            Board newBoard = board;
            newBoard.RemovePiece({pos.first, pos.second - 1});
            newBoard.MakeMove(pos, {pos.first + direction * 1, pos.second - 1});
            if (!newBoard.IsAttacked(CurrPlayerKingPostion(), oppositePlayer(gameState.currentPlayer)))
                moves.insert({pos.first + direction * 1, pos.second - 1});
        }
        else if (gameState.enPassant == std::make_pair(pos.first, pos.second + 1))
        {
            Board newBoard = board;
            newBoard.RemovePiece({pos.first, pos.second + 1});
            newBoard.MakeMove(pos, {pos.first + direction * 1, pos.second + 1});
            if (!newBoard.IsAttacked(CurrPlayerKingPostion(), oppositePlayer(gameState.currentPlayer)))
                moves.insert({pos.first + direction * 1, pos.second + 1});
        }
    }
    return;
}

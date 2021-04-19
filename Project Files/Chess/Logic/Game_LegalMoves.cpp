#include "game.hpp"

std::set<square> Game::LegalMoves(square pos){
 switch (pieceType(board[pos]))
    {
    case Knight:
        return LegalKnightMoves(pos);
        break;
    case Bishop:
        return LegalBishopMoves(pos);
    break;
    case Queen:
        return LegalQueenMoves(pos);
    break;
    case Rook:
        return LegalRookMoves(pos);
    break;
    case King:
        return LegalKingMoves(pos);
    break;
    case Pawn:
        return LegalPawnMoves(pos);
    break;
    default:
        return {};
        break;
    }
}

std::set<square> Game::CalculateSlidingMoves(square pos, std::vector<std::pair<int, int>> directions)
{

    std::set<square> moves;
    for (std::pair<int, int> p : directions)
    {
        for (int i = 1; i < 8; i++)
        {
            square newPos = {pos.first + p.first * i, pos.second + p.second * i};
            if (canMove(newPos))
                moves.insert(newPos);
            else
                break;
            if(!IsEmpty(newPos)) break;
        }
    }
    return moves;
}

std::set<square> Game::LegalKnightMoves(square pos)
{
    if (pieceType(board[pos]) != Knight)
        return {};
    if (pieceColor(board[pos]) != gameState.currentPlayer)
        return {};

    std::set<square> moves;
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

    return moves;
}

std::set<square> Game::LegalBishopMoves(square pos)
{
    if (pieceColor(board[pos]) != gameState.currentPlayer)
        return {};
    std::set<square> moves = CalculateSlidingMoves(pos, bishopMoves);
    for (square s : moves)
    {
        if (!isLegal(pos, s))
            moves.erase(s);
    }
    return moves;
}

std::set<square> Game::LegalRookMoves(square pos)
{
    if (pieceColor(board[pos]) != gameState.currentPlayer)
        return {};
    std::set<square> moves = CalculateSlidingMoves(pos, rookMoves);
    for (square s : moves)
    {
        if (!isLegal(pos, s))
            moves.erase(s);
    }
    return moves;
}

std::set<square> Game::LegalQueenMoves(square pos)
{
        if (pieceColor(board[pos]) != gameState.currentPlayer)
        return {};
    std::set<square> moves = CalculateSlidingMoves(pos, queenMoves);
    for (square s : moves)
    {
        if (!isLegal(pos, s))
            moves.erase(s);
    }
    return moves;
}

std::set<square> Game::LegalKingMoves(square pos)
{
        if (pieceColor(board[pos]) != gameState.currentPlayer)
        return {};
    std::set<square> moves;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;
            if (isLegal(pos, {pos.first + i, pos.second + j}))
                moves.insert({pos.first + i, pos.second + j});
        }
    }

    if (gameState.currentPlayer == Black)
    {
        if (gameState.blackCanCastleKingSide &&
            canMove({7, 5}) &&
            canMove({7, 6}) &&
            !board.IsAttacked({7, 5}, White) &&
            !board.IsAttacked({7, 6}, White))
        {
            moves.insert({7, 6});
        }
        if (gameState.blackCanCastleQueenSide &&
            canMove({7, 3}) &&
            canMove({7, 2}) &&
            !board.IsAttacked({7, 3}, White) &&
            !board.IsAttacked({7, 2}, White))
        {
            moves.insert({7, 2});
        }
    }
    else
    {
        if (gameState.whiteCanCastleKingSide &&
            canMove({0, 5}) &&
            canMove({0, 6}) &&
            !board.IsAttacked({0, 5}, Black) &&
            !board.IsAttacked({0, 6}, Black))
        {
            moves.insert({0, 6});
        }
        if (gameState.whiteCanCastleQueenSide &&
            canMove({0, 3}) &&
            canMove({0, 2}) &&
            !board.IsAttacked({0, 3}, Black) &&
            !board.IsAttacked({0, 2}, Black))
        {
            moves.insert({0, 2});
        }
    }
    return moves;
}

std::set<square> Game::LegalPawnMoves(square pos)
{
        if (pieceColor(board[pos]) != gameState.currentPlayer)
        return {};
    std::set<square> moves;
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
            if (isLegal(pos, {pos.first + direction * 1, pos.second - 1}))
                moves.insert({pos.first, pos.second - 1});
        }
        else if (gameState.enPassant == std::make_pair(pos.first, pos.second + 1))
        {
            Board newBoard = board;
            newBoard.RemovePiece({pos.first, pos.second + 1});
            if (isLegal(pos, {pos.first + direction * 1, pos.second + 1}))
                moves.insert({pos.first, pos.second + 1});
        }
    }
    return moves;
}

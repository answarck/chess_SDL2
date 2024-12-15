#ifndef RULES_H
#define RULES_H
#include <stdlib.h>
#include <string.h>
#include "pieces.h"
#include "types.h"

int searchForObs(piece* board[8][8], vector oldPos, vector newPos) {
  piece piece_ = *(board[oldPos.y][oldPos.x]);
  if (piece_.name == 'p') {
    if (piece_.color == 'w') {
      if (board[oldPos.y - 1][oldPos.x] != NULL) {
        return -1;
      }
    }
    if (piece_.color == 'b') {
      if (board[oldPos.y + 1][oldPos.x] != NULL) {
        return -1;
      }
    }
  }
  if (piece_.name == 'r') {
    if (oldPos.x == newPos.x) {
      if (oldPos.y > newPos.y) for (int i = newPos.y; i < oldPos.y; i++) if (board[i][oldPos.x] != NULL) return -1;
      else for (int i = oldPos.y; i < newPos.y; i++) if (board[i][oldPos.x] != NULL) return -1;
    }
    else if (oldPos.y == newPos.y) {
      if (oldPos.x > newPos.x) for (int i = newPos.x; i < oldPos.x; i++) if (board[oldPos.y][i] != NULL) return -1;
      else for (int i = oldPos.x; i < newPos.x; i++) if (board[oldPos.y][i] != NULL) return -1;
    }
  }
  return 0;
}

int knight(piece* board[8][8], vector oldPos, vector newPos) {
  if (abs(oldPos.x - newPos.x) == 2) {
    if (abs(oldPos.y - newPos.y) == 1) return 0;
  }
  if (abs(oldPos.x - newPos.x) == 1) {
    if (abs(oldPos.y - newPos.y) == 2) return 0;
  }
  return -1;
}
int pawn(piece* board[8][8], vector oldPos, vector newPos) {
  piece pawn_ = *(board[oldPos.y][oldPos.x]);
  if (oldPos.x == newPos.x) {
    if (pawn_.color == 'b' && oldPos.y > newPos.y) return -1;
    if (pawn_.color == 'w' && oldPos.y < newPos.y) return -1;
    if (pawn_.first == 0) {
      board[oldPos.y][oldPos.x]->first = 1;
      if (abs(oldPos.y - newPos.y) == 1) return 0;
      if (abs(oldPos.y - newPos.y) == 2 && searchForObs(board, oldPos, newPos) == 0) return 0;
    }
    else if (pawn_.first != 0 && abs(oldPos.y - newPos.y) == 1)  return 0;
  }
  return -1;
}
int rook(piece* board[8][8], vector oldPos, vector newPos) {
  piece pawn_ = *(board[oldPos.y][oldPos.x]);
  if (oldPos.x != newPos.x && oldPos.y != newPos.y) return -1;
  else return searchForObs(board, oldPos, newPos);
}
int king(piece* board[8][8], vector oldPos, vector newPos) {
  if (abs(oldPos.y - newPos.y) == 1) {
    //if (abs(oldPos.x - newPos.x) == 1 || oldPos.x == newPos.x) return searchForObs(board, oldPos, newPos);
    if (abs(oldPos.x - newPos.x) == 1 || oldPos.x == newPos.x) return 0;
  }
  else return -1;
}
int isMovable(piece* board[8][8], vector oldPos, vector newPos) {
  char pieceName = board[oldPos.y][oldPos.x]->name;
  if (pieceName == 'p') return pawn(board, oldPos, newPos);
  if (pieceName == 'n') return knight(board, oldPos, newPos);
  if (pieceName == 'r') return rook(board, oldPos, newPos);
  if (pieceName == 'k') return king(board, oldPos, newPos);
}
#endif // !RULES_H

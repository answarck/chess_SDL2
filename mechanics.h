#ifndef MECHANICS_H
#define MECHANICS_H
#define PLAYER_WHITE 1
#define PLAYER_BLACK -1
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "pieces.h"
#include "types.h"

int isSelectable(piece* board[8][8], vector oldPos, int* turn) {
  if (board[oldPos.y][oldPos.x] == NULL) return -1;
  if (board[oldPos.y][oldPos.x]->color == 'w' && *turn == PLAYER_BLACK) return -1;
  if (board[oldPos.y][oldPos.x]->color == 'b' && *turn == PLAYER_WHITE) return -1;
  return 0;
}

void refreshBoard(SDL_Renderer* renderer, piece* board[8][8], vector oldPos, vector newPos) {
  vector pos;
  for (int i = 0; i < 2; i++) {
    pos = (i == 0) ? oldPos : newPos;
    setColor(renderer, (pos.x + pos.y) % 2);
    SDL_Rect square = {pos.x * LENGTH, pos.y * LENGTH, LENGTH, LENGTH};
    SDL_RenderFillRect(renderer, &square);
    if (board[pos.y][pos.x] != NULL) {
      SDL_RenderCopy(renderer, board[pos.y][pos.x]->image, NULL, &square);
    }
  }
  SDL_RenderPresent(renderer);
}
void movePiece(piece* board[8][8], SDL_Renderer *renderer, vector oldPos, vector newPos, int* turn) {
  if (board[oldPos.y][oldPos.x] == NULL || board[newPos.y][newPos.x] != NULL)  return;
  piece* pieceToMove = board[oldPos.y][oldPos.x];
  board[oldPos.y][oldPos.x] = NULL;
  board[newPos.y][newPos.x] = pieceToMove;
  SDL_Rect pos = {newPos.x * LENGTH, newPos.y * LENGTH, LENGTH, LENGTH};
  refreshBoard(renderer, board, oldPos, newPos);
  *turn *= -1;
}
#endif // !MECHANICS_H

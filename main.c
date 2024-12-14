#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pieces.h"
#include "boardInit.h"
#include "types.h"

int turn = 1;

void refreshBoard(SDL_Renderer* renderer, piece* board[8][8]) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_Rect pos = {0, 0, LENGTH, LENGTH};
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      setColor(renderer, (row + col) % 2);
      SDL_Rect square = {col * LENGTH, row * LENGTH, LENGTH, LENGTH};
      SDL_RenderFillRect(renderer, &square);
    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] != NULL) {
        pos.x = j * LENGTH;
        pos.y = i * LENGTH;
        SDL_RenderCopy(renderer, board[i][j]->image, NULL, &pos);
      }
    }
  }
  SDL_RenderPresent(renderer);
}

void movePiece(piece* board[8][8], SDL_Renderer *renderer, vector oldPos, vector newPos) {
  if (board[oldPos.y][oldPos.x] == NULL || board[newPos.y][newPos.x] != NULL)  return;
  if (board[oldPos.y][oldPos.x]->color == 'w' && turn == -1) return;
  if (board[oldPos.y][oldPos.x]->color == 'b' && turn == 1) return;
  piece* pieceToMove = board[oldPos.y][oldPos.x];
  board[oldPos.y][oldPos.x] = NULL;
  board[newPos.y][newPos.x] = pieceToMove;
  pieceToMove->position = newPos;
  SDL_Rect pos = {newPos.x * LENGTH, newPos.y * LENGTH, LENGTH, LENGTH};
  refreshBoard(renderer, board);
  system("clear");
  for (int i = 0; i < 8; i++) {
    printf("{ ");
    for (int j = 0; j < 8; j++) {
      if (board[i][j] != NULL) printf("%c%c ", board[i][j]->color, board[i][j]->name);
      else printf("ee ");
    }
    printf("}\n");
  }
  printf("%d\n", turn);
  turn *= -1;
}


int main() {
  piece* board[8][8];

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error: SDL is not initialised! %s\n", SDL_GetError());
    return 1;
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("ERROR: Can't initialise Image Loader. %s\n", IMG_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Error: can't create window %s\n", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!renderer) {
    printf("Error: can't initialise renderer %s\n", SDL_GetError());
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
    
  initialiseBoard(renderer, board);
  SDL_Event event;
  int running = 1, check = 0;
  vector oldPos, newPos;
  
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (check == 0 && veccmp(newPos, oldPos) != 0) {
          check = 1;
          SDL_GetMouseState(&oldPos.x, &oldPos.y);
          oldPos.x /= LENGTH;
          oldPos.y /= LENGTH;
          if (board[oldPos.y][oldPos.x] == NULL) {
            check = 0;
            continue;
          }
        }
        else if (check == 1) {
          check = 0;
          SDL_GetMouseState(&newPos.x, &newPos.y);
          newPos.x /= LENGTH;
          newPos.y /= LENGTH;
          movePiece(board, renderer, oldPos, newPos);
        }
      }
      if (event.type == SDL_QUIT) {
        running = 0;
      }
      else {
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_q) {
            running = 0;
          }
        }
      }
    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      free(board[i][j]);
    }
}
  return 0;
}

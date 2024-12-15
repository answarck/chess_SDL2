#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pieces.h"
#include "boardInit.h"
#include "types.h"
#include "mechanics.h"
#include "rules.h"

void getPos(vector* vec) {
  SDL_GetMouseState(&vec->x, &vec->y);
  vec->x /= LENGTH;
  vec->y /= LENGTH;
}

int main() {
  piece* board[8][8];
  int turn = 1;

  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error: SDL is not initialised! %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Error: can't create window %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!renderer) {
    printf("Error: can't initialise renderer %s\n", SDL_GetError());
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
        if (check == 0) {
          check = 1;
          getPos(&oldPos);
          printf("old-(%d, %d)\n", oldPos.x, oldPos.y);
          if (isSelectable(board, oldPos, &turn) == -1) {
            check = 0;
            continue;
          }
        }
        else if (check == 1) {
          check = 0;
          getPos(&newPos);
          printf("new-(%d, %d)\n", newPos.x, newPos.y);
          if (isMovable(board, oldPos, newPos) == 0) {
            movePiece(board, renderer, oldPos, newPos, &turn);
          }
          else continue;
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

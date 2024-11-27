#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include "pieces.h"
#include "boardInit.h"

char* grid[8][8] = {
    {"br", "bn", "bb", "bq", "bk", "bb", "bn", "br"},
    {"bp", "bp", "bp", "bp", "bp", "bp", "bp", "bp"},
    {"e", "e", "e", "e", "e", "e", "e", "e"},
    {"e", "e", "e", "e", "e", "e", "e", "e"},
    {"e", "e", "e", "e", "e", "e", "e", "e"},
    {"e", "e", "e", "e", "e", "e", "e", "e"},
    {"wp", "wp", "wp", "wp", "wp", "wp", "wp", "wp"},
    {"wr", "wn", "wb", "wq", "wk", "wb", "wn", "wr"},
};


piece bPieces[2][8]; 
piece wPieces[2][8]; 

vector rowColToPos(vector pos) {
  vector position;
  position.x = (pos.y - 1)* LENGTH;
  position.y = (pos.x - 1) * LENGTH;
  return position;
}

int main() {
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

  initialiseBoard(renderer, wPieces, bPieces);

  SDL_Event event;
  int running = 1, row, col, check = 0;
  vector clickedRowCol;
  while (running) {
    while (SDL_PollEvent(&event)) {
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
  return 0;
}

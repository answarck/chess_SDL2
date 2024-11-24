#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "pieces.h"

#define WIN_W 800
#define WIN_H 800
#if WIN_W == WIN_H
  #define LENGTH WIN_W / 8
#endif

pawn wp[8], bp[8];
king wk, bk;
queen wq, bq;
knight wn, bn;
rook wr, br;
bishop wb, bb;

void setColor(SDL_Renderer *renderer, int choice) {
  SDL_Color darkBlue = {0, 71, 171, 255};
  SDL_Color lightBlue = {173, 216, 230, 255};
  if (choice) { //light
    SDL_SetRenderDrawColor(renderer, darkBlue.r, darkBlue.g, darkBlue.b, darkBlue.a);
  }
  else { //dark
    SDL_SetRenderDrawColor(renderer, lightBlue.r, lightBlue.g, lightBlue.b, lightBlue.a);
  }
}

SDL_Texture* loadImage(SDL_Renderer *renderer, char* path) {
  SDL_Surface* imageSurface = IMG_Load(path);
  SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
  SDL_FreeSurface(imageSurface);
  return imageTexture;
}

void initialisePieces(SDL_Renderer *renderer) {
  piece bPieces[2][8]; 
  piece wPieces[2][8]; 
  char pieceOrder[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, path[16];
  for (int i = 0; i < 2; i++) {
    SDL_Rect wPos = {0 , WIN_H - 2 * LENGTH + i * LENGTH, LENGTH, LENGTH};
    SDL_Rect bPos = {0, LENGTH - i * LENGTH , LENGTH, LENGTH};
    for (int j = 0; j < 8; j++) {
      bPieces[i][j].color = 'b';
      wPieces[i][j].color = 'w';
      if (i != 1) {
        bPieces[i][j].name = 'p';
        wPieces[i][j].name = 'p';
        bPieces[i][j].image = loadImage(renderer, "./assets/bp.png");
        wPieces[i][j].image = loadImage(renderer, "./assets/wp.png");
      }
      else {
        snprintf(path, sizeof(path), "./assets/w%c.png", pieceOrder[j]);
        wPieces[i][j].image = loadImage(renderer, path);
        snprintf(path, sizeof(path), "./assets/b%c.png", pieceOrder[j]);
        bPieces[i][j].image = loadImage(renderer, path);
        bPieces[i][j].name = pieceOrder[j];
        wPieces[i][j].name = pieceOrder[j];
        wPieces[i][j].position = wPos;
        bPieces[i][j].position = bPos;
      }
      wPieces[i][j].position = wPos;
      bPieces[i][j].position = bPos;
      wPos.x += LENGTH;
      bPos.x += LENGTH;
      SDL_RenderCopy(renderer, wPieces[i][j].image, NULL, &wPieces[i][j].position);
      SDL_RenderCopy(renderer, bPieces[i][j].image, NULL, &bPieces[i][j].position);
    }
  }
  SDL_RenderPresent(renderer);
}
void initialiseBoard(SDL_Renderer *renderer) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      setColor(renderer, (row + col) % 2); 
      SDL_Rect square = {col * LENGTH, row * LENGTH, LENGTH, LENGTH};
      SDL_RenderFillRect(renderer, &square);  
    }
  }
  SDL_RenderPresent(renderer);  
  initialisePieces(renderer);
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

  initialiseBoard(renderer);

  SDL_Event event;
  int running = 1;
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

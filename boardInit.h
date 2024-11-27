#ifndef BOARDINIT
#define BOARDINIT

#define WIN_W 800
#define WIN_H 800

#if WIN_W == WIN_H
  #define LENGTH (WIN_W / 8)
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pieces.h"

void setColor(SDL_Renderer *renderer, int choice) {
  SDL_Color dark = {0, 71, 171, 255};
  SDL_Color light = {173, 216, 230, 255};
  if (choice) { //light
    SDL_SetRenderDrawColor(renderer, dark.r, dark.g, dark.b, dark.a);
  }
  else { //dark
    SDL_SetRenderDrawColor(renderer, light.r, light.g, light.b, light.a);
  }
}

SDL_Texture* loadImage(SDL_Renderer *renderer, char* path) {
  SDL_Surface* imageSurface = IMG_Load(path);
  SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
  SDL_FreeSurface(imageSurface);
  return imageTexture;
}

void initialisePieces(SDL_Renderer *renderer, piece wPieces[2][8], piece bPieces[2][8]) {
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
        wPieces[i][j].position = (vector ){(wPos.x / 100), (wPos.y / 100)};
        bPieces[i][j].position = (vector ){(bPos.x / 100), (bPos.y / 100)};
      }
      wPieces[i][j].position = (vector ){(wPos.x / 100), (wPos.y / 100)};
      bPieces[i][j].position = (vector ){(bPos.x / 100), (bPos.y / 100)};
      SDL_RenderCopy(renderer, wPieces[i][j].image, NULL, &wPos);
      SDL_RenderCopy(renderer, bPieces[i][j].image, NULL, &bPos);
      wPos.x += LENGTH;
      bPos.x += LENGTH;
    }
  }
  SDL_RenderPresent(renderer);
}


void initialiseBoard(SDL_Renderer *renderer, piece wPieces[2][8], piece bPieces[2][8]) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      setColor(renderer, (row + col) % 2); 
      SDL_Rect square = {col * LENGTH, row * LENGTH, LENGTH, LENGTH};
      SDL_RenderFillRect(renderer, &square);  
    }
  }
  SDL_RenderPresent(renderer);  
  initialisePieces(renderer, wPieces, bPieces);
}
#endif 


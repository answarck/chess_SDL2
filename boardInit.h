#ifndef BOARDINIT
#define BOARDINIT

#define WIN_W 800
#define WIN_H 800

#if WIN_W == WIN_H
  #define LENGTH (WIN_W / 8)
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "pieces.h"
#include "types.h"

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

void initialisePieces(SDL_Renderer *renderer, piece* board[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = malloc(sizeof(piece));
        }
    }

    char pieceOrder[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, path[16];
    SDL_Rect pos = {0, 0, LENGTH, LENGTH};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i < 2) {
                board[i][j]->color = 'b';
                if (i == 0) {
                    board[i][j]->name = pieceOrder[j];
                    snprintf(path, sizeof(path), "./assets/b%c.png", pieceOrder[j]);
                    board[i][j]->image = loadImage(renderer, path);
                } 
                else {
                    board[i][j]->name = 'p';
                    board[i][j]->image = loadImage(renderer, "./assets/bp.png");
                }
                board[i][j]->position.x = j;
                board[i][j]->position.y = i;
                SDL_RenderCopy(renderer, board[i][j]->image, NULL, &pos);
            } 
            else if (i > 5) {
                board[i][j]->color = 'w';
                if (i == 6) {
                    board[i][j]->name = 'p';
                    board[i][j]->image = loadImage(renderer, "./assets/wp.png");
                } 
                else {
                    board[i][j]->name = pieceOrder[j];
                    snprintf(path, sizeof(path), "./assets/w%c.png", pieceOrder[j]);
                    board[i][j]->image = loadImage(renderer, path);
                }
                board[i][j]->position.x = j;
                board[i][j]->position.y = i;
                SDL_RenderCopy(renderer, board[i][j]->image, NULL, &pos);
            }
            else {
              board[i][j] = NULL;
            }
            pos.x += LENGTH;
        }
        pos.x = 0;
        pos.y += LENGTH;
    }
    SDL_RenderPresent(renderer);
}

void initialiseBoard(SDL_Renderer *renderer, piece* board[8][8]) {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      setColor(renderer, (row + col) % 2); 
      SDL_Rect square = {col * LENGTH, row * LENGTH, LENGTH, LENGTH};
      SDL_RenderFillRect(renderer, &square);  
    }
  }
  SDL_RenderPresent(renderer);  
  initialisePieces(renderer, board);
}
#endif 

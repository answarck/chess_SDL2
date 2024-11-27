#ifndef PIECES_H
#define PIECES_H

#include <SDL2/SDL.h>

typedef struct {
   int x; 
   int y;
} vector;
typedef struct {
  char name;
  char color;
  vector position;
  SDL_Texture* image;
} piece;
#endif 

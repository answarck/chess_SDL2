#ifndef PIECES_H
#define PIECES_H

#include <SDL2/SDL.h>
#include "types.h"

typedef struct {
  char name;
  char color;
  int first;
  SDL_Texture* image;
} piece;
#endif 

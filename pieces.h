#ifndef PIECES_H
#define PIECES_H

#include <SDL2/SDL.h>
#include "types.h"

typedef struct {
  char name;
  char color;
  vector position;
  SDL_Texture* image;
} piece;
#endif 

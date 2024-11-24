#ifndef PIECES_H
#define PIECES_H
#endif 

#include <SDL2/SDL.h>

typedef struct piece piece;
typedef struct king king;
typedef struct queen queen;
typedef struct bishop bishop;
typedef struct rook rook;
typedef struct knight knight;
typedef struct pawn pawn;

struct king {
  SDL_Rect pos;
  SDL_Texture* image;
  char color;
};
struct queen {
  SDL_Rect pos;
  SDL_Texture* image;
  char color;
};
struct rook {
  SDL_Rect pos;
  SDL_Texture* image;
  char color;
};
struct bishop {
  SDL_Rect pos;
  SDL_Texture* image;
  char color;
};
struct knight {
  SDL_Rect pos;
  SDL_Texture* image;
  char color;
};
struct pawn {
  SDL_Rect pos;
  SDL_Texture* image;
  char color;
};
struct piece {
  char name;
  char color;
  SDL_Rect position;
  SDL_Texture* image;
};

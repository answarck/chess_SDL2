#ifndef TYPES_H
#define TYPES_H

typedef struct {
   int x; 
   int y;
} vector;

int veccmp(vector v1, vector v2);

int veccmp(vector v1, vector v2) {
  if (v1.x == v2.x && v1.y == v2.y) return 0;
  else return 1;
}


#endif

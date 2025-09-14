#ifndef RT_H // put around entire file or individual definitions?
#define RT_H
#define NUM_OBJS 2
#include <stdio.h>
#include "vp.h"

typedef struct {
  VP_T origin;
  VP_T dir;
}RAY_T;

typedef struct {
  VP_T origin;
  double radius;
}SPHERE_T;

typedef struct {
  VP_T normal; // orientation of plane
  double d; // distance from origin/placement of plane
}PLANE_T;

typedef struct {
  double R;
  double G;
  double B;
}COLOR_T;

typedef struct {
  VP_T loc;
}LIGHT_T;  

typedef struct OBJ {
  union {
    PLANE_T plane;
    SPHERE_T sphere;
  };
  char type;
  COLOR_T color;
  int checker;
  COLOR_T color2;
  int (*intersect) (RAY_T ray, struct OBJ_T *obj, double *t, VP_T *int_pt, VP_T *normal); // throws warning: struct obj only visible inside statement (implementation from video)
  struct OBJ *next;
}OBJ_T;

typedef struct {
  OBJ_T *objs;
  LIGHT_T light;
  double start_x; // beginning of stuff space ???
  double start_y;
  double pixel_size; // = 1/1000
}SCENE_T;

int objs_equal(OBJ_T obj1, OBJ_T obj2);

#endif

#ifndef VP_H
#define VP_H

typedef struct {
  double x;
  double y;
  double z;
}VP_T;

double dot(VP_T v1, VP_T v2); /* Function prototype. */

VP_T normalize (VP_T vector); /* Function prototype. */

double vec_len(VP_T vector);

VP_T vec_subtract(VP_T vector1, VP_T vector2);

#endif

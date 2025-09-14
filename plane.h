#ifndef PLANE_H
#define PLANE_H
#include "vp.h"
#include "rt.h"

int intersect_plane(RAY_T ray, OBJ_T *objs, double *t, VP_T *int_pt, VP_T *normal);

#endif

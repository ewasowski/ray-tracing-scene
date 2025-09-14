#ifndef LIGHT_H
#define LIGHT_H
#include "vp.h"
#include "rt.h"

COLOR_T illuminate (SCENE_T scene, RAY_T ray, VP_T int_pt, OBJ_T *obj, VP_T normal);

#endif

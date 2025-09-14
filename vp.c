#include <stdio.h>
#include <math.h>
#include "vp.h"
#include "rt.h"

double vec_len(VP_T vector)
{
  double length = sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
  return length;
}

VP_T normalize(VP_T vector)
{
  double length = vec_len(vector);
  VP_T norm;
  norm.x = vector.x / length;
  norm.y = vector.y / length;
  norm.z = vector.z / length;
  return norm;
}

double dot(VP_T v1, VP_T v2)
{
  double product = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
  return product;
}

VP_T vec_subtract(VP_T vector1, VP_T vector2)
{
  double x = vector1.x - vector2.x;
  double y = vector1.y - vector2.y;
  double z = vector1.z - vector2.z;
  
  VP_T new;
  new.x = x;
  new.y = y;
  new.z = z;
  
  return new;
}

#include "plane.h"
#include "rt.h"
#include "vp.h"

int intersect_plane(RAY_T ray, OBJ_T *objs, double *t, VP_T *int_pt, VP_T *normal){

  //printf("start intersect plane");
  PLANE_T plane = objs -> plane;
  normal -> x = plane.normal.x; // save normal
  normal -> y = plane.normal.y;
  normal -> z = plane.normal.z;

  double dp = dot(*normal, ray.dir); // HE JUST PUT * CIRCLE ON SLIDES IM SURE ITS DOT

  if (dp == 0) { // ray and plane are parallel, do not intersect
      return 0;
    }
  
  else {
    *t = -(dot(*normal, ray.origin) + plane.d) / dp; // distance to intersection
    if (*t < 0) { // intersects behind viewpoint
      return 0;
	}

    else {
      int_pt -> x = ray.origin.x + (*t * ray.dir.x); // calc intersection
      int_pt -> y = ray.origin.y + (*t * ray.dir.y);
      int_pt -> z = ray.origin.z + (*t * ray.dir.z);

      return 1;
    }
  }
      
}

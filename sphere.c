#include "sphere.h"
#include "rt.h"
#include "vp.h"
#include <math.h>

int intersect_sphere(RAY_T ray, OBJ_T *obj, double *t, VP_T *int_pt, VP_T *normal)
// Intersection test.
{
//printf("SPHERER INTERSECT RUNNING WAOAOAIAO\N");
  SPHERE_T sphere = obj -> sphere;
  double A = 1;
  
  double b = 2 * (ray.dir.x * (ray.origin.x - sphere.origin.x) +
  	       ray.dir.y * (ray.origin.y - sphere.origin.y) +
  	       ray.dir.z * (ray.origin.z - sphere.origin.z));
  	       
  double c = ((ray.origin.x - sphere.origin.x) * (ray.origin.x - sphere.origin.x) +
  	   (ray.origin.y - sphere.origin.y) * (ray.origin.y - sphere.origin.y) +
  	   (ray.origin.z - sphere.origin.z) * (ray.origin.z - sphere.origin.z)) - 
  	   (sphere.radius * sphere.radius);

  double discr = (b*b - 4*A*c); // discriminant of quadratic formula
  
  if (discr > 0) // if intersection found
    {
      discr = sqrt(discr);
      double t1 = (-b - discr) / 2*A;
      double t2 = (-b + discr) / 2*A;
      
      
      if (t1 > 0 && t2 > 0)  // if both intersection points are ahead of viewpoint
        {
          *t = fmin(t1, t2); // calculate distance from eyepoint to intersection
          
          int_pt -> x = ray.origin.x + (*t * ray.dir.x); // calculating intersection point
          int_pt -> y = ray.origin.y + (*t * ray.dir.y);
          int_pt -> z = ray.origin.z + (*t * ray.dir.z);
          
          
          normal -> x = (int_pt -> x) - sphere.origin.x; // calculating normal vector
          normal -> y = (int_pt -> y) - sphere.origin.y;
	  normal -> z = (int_pt -> z) - sphere.origin.z;
          *normal = normalize(*normal);
          }
      return 1;
    }
  
  else // no intersection found
    {
      return 0;
    }
}

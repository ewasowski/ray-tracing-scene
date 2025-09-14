#include "light.h"
#include <math.h>

static int shadow_test(SCENE_T scene, OBJ_T *obj, VP_T int_pt)
// objects cast shadows
{
// iterate through objs list to see if any objs exist between int_pt and light
   RAY_T shadow_ray; // ray from int_pt towards light source
   shadow_ray.origin = int_pt;
   shadow_ray.dir = vec_subtract(scene.light.loc, int_pt);
   shadow_ray.dir = normalize(shadow_ray.dir);
   
				   if (obj -> color.R == 0.8){ // checking red sphere with error
				   printf("intpt %f %f %f  light loc %f %f %f", shadow_ray.origin.x, shadow_ray.origin.y, shadow_ray.origin.z, scene.light.loc.x, scene.light.loc.y, scene.light.loc.z);
				   printf("normalized direction ???(redonly)?????? %f %f %f\n", shadow_ray.dir.x, shadow_ray.dir.y, shadow_ray.dir.z);
				   }

   OBJ_T *cur_obj; 
   cur_obj = scene.objs; // getting start pointer for objs list
   
   double t; // initializing vals for intersect
   VP_T int_pt2;
   VP_T normal;
   
   while (cur_obj != NULL) 
   {
   	// blocks checking self
     if (cur_obj == obj)
       //if (objs_equal(*cur_obj, obj))
      {
	//printf("address iter vs address obj %p %p\n", cur_obj, obj);
      //printf("worked! :D ");
      //printf("cur_obj %c r %f g %f \n", cur_obj -> type, cur_obj -> color.R, cur_obj -> color.G);
         cur_obj = cur_obj -> next;
         //printf("cur_obj %c r %f g %f  go to continue\n", cur_obj -> type, cur_obj -> color.R, cur_obj -> color.G);
         continue;
      }
         
         // actual intersect test. i think i am somehow interpreting this wrong OVERGENERATES SHADOW ON RED
      if (cur_obj -> intersect(shadow_ray, cur_obj, &t, &int_pt2, &normal))
      {
      		if (obj -> color.R == 0.8) { // checking red sphere with error
      		printf("intersection detected on red circle ");
      		printf("new int pt %f %f %f with object %c g val %f\n", int_pt2.x, int_pt2.y, int_pt2.z, cur_obj -> type, cur_obj -> color.G);
      		}
         return 1;
      }
         
      cur_obj = cur_obj -> next;
   }
   
   return 0;

}


COLOR_T illuminate(SCENE_T scene, RAY_T ray, VP_T int_pt, OBJ_T *obj, VP_T normal) 
// Lighting function.
{
  COLOR_T color; // initializing color to add to and return
  double dp, dp2;
  VP_T R;
  COLOR_T obj_color;
  double atten;
  double dL;
  
  VP_T light_loc; // setting scene attr light to existing var to avoid having to change names JUST USE ATTR WHEN TRANSFERRING
  light_loc = scene.light.loc;
  
  obj_color = obj -> color;
  
  if (obj -> checker && (((int)floor (int_pt.x) + (int)floor (int_pt.y) + (int)floor (int_pt.z)) & 1)) { // check for checker
    obj_color = obj -> color2;
    //printf("checker = true, color = %f starts dark ", obj_color.R);
     }
     else{ 
     //printf("checker = false, color = %f. should be light ", obj_color.R);
     }
  
  
  // ambient
  
  color.R = 0.1 * obj_color.R;
  color.G = 0.1 * obj_color.G;
  color.B = 0.1 * obj_color.B;
     
  //printf("after ambient: %f %f %f\n", color.R, color.G, color.B);
  
  // implement shadow test here
  if (1 || !shadow_test(scene, obj, int_pt)) // CURRENTLY MAKING RED SPHERE (supposed to have none) HAVE SHADOW ON IT, also creating all required shadows
  {
  
  // diffuse
  
  VP_T L;
  
  L.x = light_loc.x - int_pt.x; // distance from light source to intersection with object
  L.y = light_loc.y - int_pt.y;
  L.z = light_loc.z - int_pt.z;
  
  	// calculating light attenuation
  	dL = vec_len(L);
  	atten = 1/(.002 * (dL*dL) + .02 * dL + .2); // i dont understand why this is over 1 but we roll!! works :)
  					//printf("%f ", atten);
  					//atten = 1;
  L = normalize(L);
  
  
  dp = dot(L,normal);
  
  if (dp > 0) {
    color.R += dp * obj_color.R * atten; // if dot product positive, increase color value
    color.G += dp * obj_color.G * atten; 
    color.B += dp * obj_color.B * atten;
    //printf("after diffuse: %f %f %f\n", color.R, color.G, color.B);

    
  // specular
    
  R.x = L.x - normal.x * 2 * dp;
  R.y = L.y - normal.y * 2 * dp;
  R.z = L.z - normal.z * 2 * dp;
  
  R = normalize(R);
  
  dp2 = dot(R, ray.dir);

  if (dp2 > 0) { // if dot product positive, increase brightness
      color.R += pow(dp2, 200) * atten;
      color.G += pow(dp2, 200) * atten;
      color.B += pow(dp2, 200) * atten;
    }
    //printf("after specular: %f %f %f\n", color.R, color.G, color.B);
  }
  }

    
  // capping off colors
  if (color.R > 1) {
    color.R = 1;
  }
  if (color.G > 1) {
    color.G = 1;
  }
  if (color.B > 1) {
    color.B = 1;
    }
  	//printf("final color is: %f %f %f\n\n", color.R, color.G, color.B);
  return color;
}





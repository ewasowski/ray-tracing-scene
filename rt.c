#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rt.h"
#include "vp.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"

COLOR_T trace(RAY_T ray, SCENE_T scene) { // "just pass in ray and scene and not all the extraneous things"

  COLOR_T color; // declare color to return at end of function  
  
  double t; // initializing vals that used to be passed as blank addresses
  VP_T int_pt;
  VP_T normal;
  
  double closest_t = 10000; // storing closest info
  VP_T closest_int_pt;
  VP_T closest_normal;
  OBJ_T *closest_obj;

  OBJ_T *node;
  node = scene.objs;

  // setting background color
  color.R = 0.3;
  color.G = 0.3;
  color.B = 0.5;

  //for item in linked list, do next bit. (intersect_obj w fn pointers)
  while (node != NULL) {
    
      // DOUBLE CHECK THAT IF STATEMENT IS CORRECT, IT SHOULD ONLY CARE IF T IS CLOSER AT INDIVIDUAL POINTS, RIGHT? dont want to overwrite all points except closest screenwide, jsut for single pixel.
    if (node -> intersect(ray, node, &t, &int_pt, &normal)) // if ray intersects object, continue to calculate color
      {

      VP_T light_loc; // set light location (NOW BASED ON INPUT FILE/LIGHT OBJ)
      light_loc.x = scene.light.loc.x;
      light_loc.y = scene.light.loc.y;
      light_loc.z = scene.light.loc.z;
      
    // LIGHT LOC AND OBJ COLOR REPLACED WITH SCENE
    			// figure out how to put scene in everything while keeping obj separate? can always pass both
      color = illuminate(scene, ray, int_pt, node, normal); // calculate color + lighting

      if (t > 0 && t < closest_t) {
	closest_t = t;
	closest_int_pt = int_pt;
	closest_normal = normal;
	closest_obj = node;
        }
      }
    node = node -> next;
  }
  
  return color;
}

void init(SCENE_T *scene) // pass in ADDRESS // must also assign intersect_sphere fn to spheres and intersect_plane to planes, not sure how u do that (he says at 47:00 on mon 10/28 vid)
{
  OBJ_T *objs = NULL;
  //OBJ_T *node;

  scene -> pixel_size = 1/1000;
			 
  // READING FROM SCENE FILE
  FILE *fpr; // file pointer (read)
           
  printf("lalala"); // DEBUG PRINT STATEMENT
  fpr = fopen("scene1.txt", "r");

  char c;
	   
  printf("opened");                                  // DEBUG PRINT STATENET
  while((fscanf(fpr, "%c", &c) != EOF)) {
    printf("character %c,\n", c); // DEBUG PRINT STATEMNnt
    double num;
    switch(c){
	       
    case 's': {OBJ_T *node;

      SPHERE_T sphere; 
      
      node = (OBJ_T *)malloc(sizeof(OBJ_T));
      node -> next = scene -> objs;
      scene -> objs = node;

      // setting sphere attributes
       
      // origin
      fscanf(fpr, "%lf", &num);
      node -> sphere.origin.x = num;

      printf("sphere x is %lf<-", num); // DEBUG PRINT STATENEMT
       
      fscanf(fpr, "%lf", &num);
      node -> sphere.origin.y = num;

      fscanf(fpr, "%lf", &num);
      node -> sphere.origin.z = num;


      fscanf(fpr, "%lf", &num);
      node -> sphere.radius = num;

      printf("sphere radius is %lf<-", num); // DEBUG PRINT STATEMNET
	       
      // setting object attributes
      node -> type = 's';
       
	       
      fscanf(fpr, "%lf", &num); //color
      node -> color.R = num;
	       
      fscanf(fpr, "%lf", &num);
      node -> color.G = num;

      fscanf(fpr, "%lf", &num);
      node -> color.B = num;


      node -> checker = 0; // checker false

      node -> intersect = intersect_sphere;

    }
      // add to objects list (counter index????? or just. append its a linked list lmao. why did i do that??)
	       
      break;
	       
    case 'p': {OBJ_T *node_p; 
      node_p = (OBJ_T *)malloc(sizeof(OBJ_T));
      node_p -> next = scene -> objs;
      scene -> objs = node_p; 
      
      PLANE_T plane;
      // setting plane attributes
      fscanf(fpr, "%lf", &num); // normal
      plane.normal.x = num;

      fscanf(fpr, "%lf", &num);
      plane.normal.y = num;

      fscanf(fpr, "%lf", &num);
      plane.normal.z = num;


      fscanf(fpr, "%lf", &num); // d - distance from viewpoint
      plane.d = num;
      printf("plane d value %lf", plane.d); // DEBUG PRINT STATEMENT

      node_p -> plane = plane;

      // setting object attributes
      node_p -> type = 'p';

      fscanf(fpr, "%lf", &num); // color
      node_p -> color.R = num;

      fscanf(fpr, "%lf", &num);
      node_p -> color.G = num;

      fscanf(fpr, "%lf", &num);
      node_p -> color.B = num;

       
      fscanf(fpr, "%lf", &num); // color2
      node_p -> color2.R = num;
       
      fscanf(fpr, "%lf", &num);
      node_p -> color2.G = num;

      fscanf(fpr, "%lf", &num);
      node_p -> color2.B = num;


      if(node_p -> color.R != node_p -> color2.R || node_p -> color.G != node_p -> color2.G || node_p -> color.B != node_p -> color2.B) { // if color and color2 vals differ, checker true
	node_p -> checker = 1;
      }
      else {
	node_p -> checker = 0; // else checker false
	}

      node_p -> intersect = intersect_plane;
    }	       
      // put in lists
	       
      break; //**/
       
    case 'l': {LIGHT_T light;
	       
      fscanf(fpr, "%lf", &num); // set location
      light.loc.x = num;

      fscanf(fpr, "%lf", &num);
      light.loc.y = num;

      fscanf(fpr, "%lf", &num);
      light.loc.z = num;

      scene -> light = light;}
      break; 
		  
    }

  }
}


int objs_equal(OBJ_T obj1, OBJ_T obj2) // extremely evil nested ifs im sorry :sob:
{
   if (obj1.type == obj2.type) //&& obj1.color.R == obj2.color.R && obj1.color.G == obj2.color.G && obj1.color.B == obj2.color.B)
   { // checks that type & color are the same
         if (obj1.type == 'p')
         {
            if (obj1.plane.d == obj2.plane.d &&
               	obj1.plane.normal.x == obj2.plane.normal.x &&
               	obj1.plane.normal.y == obj2.plane.normal.y &&
               	obj1.plane.normal.z == obj2.plane.normal.z)
               	{
               	   return 1;
               	}
            else 
            return 0;
         }
         else if (obj1.sphere.origin.x == obj2.sphere.origin.x && 
         	obj1.sphere.origin.y == obj2.sphere.origin.y && 
         	obj1.sphere.origin.z == obj2.sphere.origin.z &&
         	obj1.sphere.radius == obj2.sphere.radius)
         	{
         	printf("same sphere");
         	   return 1;
         	}
         	else return 0; // makes shadows on circles appear.
   }
   else
   {
      return 0;
   }
}
    


void main(void)
	 {
	   //printf("Main GO");
	   int dimx = 1920; // set dimensions of image
	   int dimy = 1080; 
	   
	   RAY_T ray; // init ray, set origin
	   ray.origin.x = 0; 
	   ray.origin.y = 0; 
	   ray.origin.z = 0; 

	   SCENE_T scene;

	   init(&scene);
	   scene.start_x = -((double)dimx/(double)dimy)/2;
	   scene.start_y = 0.5;
	   scene.pixel_size = 1/(double)dimy;
	  
	   
	   // CREATING FILE
	   FILE *fpw; // file pointer (write)
	   fpw = fopen("img.ppm", "w+");
	   fprintf(fpw, "P6\n%i %i\n255\n", dimx, dimy); // ppm header

	   for (int y = 0; y < dimy; y++)
	     {
	       for (int  x = 0; x < dimx; x++)
		 {
      
		   ray.dir.x = scene.start_x + ((double)x)*scene.pixel_size; // set ray direction (per pixel)
		   ray.dir.y = scene.start_y - ((double)y)*scene.pixel_size;
		   ray.dir.z = 1;
		   ray.dir = normalize(ray.dir); // normalize dir vector & reassign
		   
      
		   COLOR_T pixel = trace(ray, scene); // calculate pixel RGB values
		   unsigned char r = (unsigned char) (pixel.R * 255);
		   unsigned char g = (unsigned char) (pixel.G * 255);
		   unsigned char b = (unsigned char) (pixel.B * 255);
               
		   fprintf(fpw, "%c%c%c", r, g, b); // print pixel RGB values for ppm file
		 }
	     }
	 }

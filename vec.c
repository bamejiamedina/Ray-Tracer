//Bryan Mejia-Medina
//CS304 - Assignment 5

#include <math.h>
#include "vec.h"

VEC_T normalize(VEC_T v) {
    // Computer and returns normalized vector v
   double val = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
   v.x = v.x / val;
   v.y = v.y / val;
   v.z = v.z / val;
   return v;
}

//double dot(VEC_T v1, VEC_T v2) {
//    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//}

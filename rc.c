//Bryan Mejia-Medina
//CS304 - Assignment 5
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rc.h"

int main() {
    //Calls read_objs
    //Initializes image file
    //Loops through pixels
    //Sets ray, calls cast, prints pixel, frees linked list

    OBJ_T *list = NULL;
    OBJ_T *curr;
    read_objs(&list);
    COLOR_T pix;
    RAY_T ray;
    int x, y;

    ray.origin.x = 0;
    ray.origin.y = 0;
    ray.origin.z = 0;

    ray.direction.z = 1;

    printf("P6\n1000 1000\n255\n");

    for (y = 0; y < 1000; y++) {
        for (x = 0; x < 1000; x++) {
            ray.direction.x = -0.5 + x / 1000.0;
            ray.direction.y = 0.5 - y / 1000.0;
            ray.direction = normalize(ray.direction);
            curr = list;
            pix = cast(ray, list);
            printf("%c%c%c", (unsigned char)(pix.r*255), (unsigned char)(pix.g*255), (unsigned char)(pix.b*255));
        }
    }
    while (list != NULL) {
        curr = list;
        list = list->next;
        free(curr);
    }
}

COLOR_T cast(RAY_T ray, OBJ_T *list) {
    //Iterates through linked list; finds closest intersection using intersect_sphere
    //Returns color of closest sphere

    OBJ_T *curr;
    double min_t = 1000;
    double t;
    COLOR_T color;

    color.r = 1.;
    color.g = 1.;
    color.b = 1.;
    for (curr = list; curr != NULL; curr = curr->next) {
        if (intersect_sphere(ray, curr->sphere, &t)) {
            if (t < min_t) {
                color = curr->color;
                min_t = t;
            }
        }
    }
    return color;
}

int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t) {
    //Computes intersection of ray and sphere
    //Returns 1 if intersection, 0 otherwise
    //t is set to distance from camera to sphere intersection

    double A, B, C;

    A = 1;

    B = 2 * ((ray.direction.x * (ray.origin.x - sphere.center.x)) +
             (ray.direction.y * (ray.origin.y - sphere.center.y)) +
             (ray.direction.z * (ray.origin.z - sphere.center.z)));

    C = pow(ray.origin.x - sphere.center.x, 2) +
        pow(ray.origin.y - sphere.center.y, 2) +
        pow(ray.origin.z - sphere.center.z, 2) -
        pow(sphere.radius, 2);

    double discriminant = pow(B, 2) - 4*A*C;

    if (discriminant < 0) {
        return 0;
    }

    float t0 = (-B + sqrt(discriminant)) / 2*A;
    float t1 = (-B - sqrt(discriminant)) / 2*A;

    if (t0 < 0 && t1 < 0) {
        return 0;
    }

    *t = t0 < t1 ? t0 : t1;

    return 1;
}

void read_objs(OBJ_T **list) {
    //Reads spheres from stdin
    //Creates linked list using dynamic memory

    double center_x, center_y, center_z;
    double radius;
    double r, g, b;

    OBJ_T *new;
    while (scanf("%lf %lf %lf %lf %lf %lf %lf", &center_x, &center_y, &center_z, &radius, &r, &g, &b) == 7) {
        new = (OBJ_T *)malloc(sizeof(OBJ_T));
        new -> sphere.center.x = center_x;
        new -> sphere.center.y = center_y;
        new -> sphere.center.z = center_z;
        new -> sphere.radius = radius;
        new -> color.r = r;
        new -> color.g = g;
        new -> color.b = b;
        new -> next = *list;

        *list = new;
    }
}

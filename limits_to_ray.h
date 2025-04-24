#include "line_drawing_alg.h"

double intersect_screen(struct Ray ray, int screenW, int screenH);
double intersect_circle(struct Ray ray, struct Circle circle);

void compute_ray_endpoint(struct Ray *ray, struct Circle barrier, int screenW, int screenH);
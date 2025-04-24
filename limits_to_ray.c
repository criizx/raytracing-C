#include "limits_to_ray.h"

#include <float.h>
#include <math.h>

double intersect_screen(struct Ray ray, int screenW, int screenH) {
	int x0 = ray.start_x;
	int y0 = ray.start_y;
	double dx = sin(ray.angle);
	double dy = cos(ray.angle);

	double t_min = INFINITY;

	if (dx != 0.0) {
		double t = (0 - x0) / dx;
		double y = y0 + t * dy;
		if (t > 0 && y >= 0 && y <= screenH) t_min = fmin(t_min, t);

		t = (screenW - x0) / dx;
		y = y0 + t * dy;
		if (t > 0 && y >= 0 && y <= screenH) t_min = fmin(t_min, t);
	}

	if (dy != 0.0) {
		double t = (0 - y0) / dy;
		double x = x0 + t * dx;
		if (t > 0 && x >= 0 && x <= screenW) t_min = fmin(t_min, t);

		t = (screenH - y0) / dy;
		x = x0 + t * dx;
		if (t > 0 && x >= 0 && x <= screenW) t_min = fmin(t_min, t);
	}

	return t_min;
}

double intersect_circle(struct Ray ray, struct Circle circle) {
	double dx = sin(ray.angle);
	double dy = cos(ray.angle);
	double cx = circle.x;
	double cy = circle.y;
	double x0 = ray.start_x;
	double y0 = ray.start_y;

	double fx = x0 - cx;
	double fy = y0 - cy;
	double A = dx * dx + dy * dy;
	double B = 2 * (fx * dx + fy * dy);
	double C = fx * fx + fy * fy - circle.radius * circle.radius;

	double discriminant = B * B - 4 * A * C;

	if (discriminant < 0) {
		return INFINITY;
	} else {
		discriminant = sqrt(discriminant);
		double t1 = (-B - discriminant) / (2 * A);
		double t2 = (-B + discriminant) / (2 * A);

		if (t1 > 0) return t1;
		if (t2 > 0) return t2;
		return INFINITY;
	}
}

void compute_ray_endpoint(struct Ray *ray, struct Circle barrier, int screenW, int screenH) {
	double t_screen = intersect_screen(*ray, screenW, screenH);
	double t_circle = intersect_circle(*ray, barrier);
	double t = fmin(t_screen, t_circle);

	double dx = sin(ray->angle);
	double dy = cos(ray->angle);

	ray->end_x = ray->start_x + (int)(dx * t);
	ray->end_y = ray->start_y + (int)(dy * t);
}
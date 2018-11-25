#include "stdio.h"
#include "math.h"

class point
{
public:
  point() {x = y = z = 0;}
  point(float a, float b, float c);
	point *sub(point *q);
	float dot(point *q);
	float norm();
public:
	float x; float y; float z;
};

class ray
{
public:
  ray(point *o, point *d);
	point *at(float t);
public:
	point *origin;
	point *dir;
};

point::point(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

point *normalize(point *p) {
  point *q = new point();
	float norm = 
    sqrtf(p->x * p->x + p->y * p->y + p->z * p->z);
	if (norm == 0) norm = 1.f;
	q->x = p->x / norm;
	q->y = p->y / norm;
	q->z = p->z / norm;
	return q;
}

point *point::sub(point *q) {
  return 
    new point(x - q->x, y - q->y, z - q->z);
}

float point::dot(point *q) {
  return x * q->x + y * q->y + z * q->z;
}

float point::norm() {
  return sqrtf(x * x + y * y + z * z);
}

void printpt(point *p) {
  printf("<%f, %f, %f>\n", p->x, p->y, p->z);
}

ray::ray(point *o, point *d) {
  origin = o;
	dir = normalize(d);
}

point *ray::at(float t) {
  return new point(origin->x + t * dir->x,
									 origin->y + t * dir->y,
									 origin->z + t * dir->z);
}

class obj {
public:
	virtual float intersect(ray *r) = 0;
	virtual point* normal(point *p) = 0;
};

class sphere : public obj {
public:
	sphere(point *center, float r);
	float intersect(ray *r);
	point* normal(point *p);
private:
	point *_center;
	float _r;
};

sphere::sphere(point *center, float r) {
	_center = center;
	_r = r;
};

float sphere::intersect(ray *r) {
	float ox = r->origin->x;
	float oy = r->origin->y;
	float oz = r->origin->z;
	float dx = r->dir->x;
	float dy = r->dir->y;
	float dz = r->dir->z;
	float cx = _center->x;
	float cy = _center->y;
	float cz = _center->z;

	//(ox + dx * t - cx)^2 + ... = r^2
	float ux = ox - cx;
	float uy = oy - cy;
	float uz = oz - cz;
	float a = dx * dx + dy * dy + dz * dz;
	float b = 2 * (ux * dx + uy * dy + uz * dz);
	float c = ux * ux + uy * uy + uz * uz - _r * _r;
	float disc = b * b - 4 * a * c;
	if (disc < 0) return -1;
	float delta = sqrtf(disc);
	float t1 = (-b - delta) / (2 * a);
	if (t1 > 0) return t1;
	float t2 = (-b + delta) / (2 * a);
	if (t2 > 0) return t2;

	return -1;
}

point* sphere::normal(point *p) {
	return normalize(_center->sub(p));
}

int main(int argc, char** argv) {
	sphere *sp = new sphere(new point(0, 0, 0), 1);
	ray *r = new ray(new point(2, 2, 2),
									 new point(-1, -1, -1));
  printf("%f\n", sp->intersect(r));
	return 0;
}

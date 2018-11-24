#include "stdio.h"
#include "math.h"

typedef struct {
	float x; float y; float z;
} point;

typedef struct {
	point *origin;
	point *dir;
} ray;

point *newpt(float x, float y, float z) {
  point *p = new point();
	p->x = x;
  p->y = y;
  p->z = z;
  return p;
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

point *subpt(point *p, point *q) {
  return newpt(p->x - q->x, p->y - q->y, p->z - q->z);
}

void printpt(point *p) {
  printf("<%f, %f, %f>\n", p->x, p->y, p->z);
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

	//(dx * t - cx)^2 + ... = r^2
	float a = dx * dx + dy * dy + dz * dz;
	float b = -2 * (cx * dx + cy * dy + cz * dz);
	float c = cx * cx + cy * cy + cz * cz - _r * _r;
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
	return normalize(subpt(_center, p));
}

int main(int argc, char** argv) {
  point *p = newpt(1, 2, 3);
	point *q = normalize(p);
	printpt(q);
	return 0;
}

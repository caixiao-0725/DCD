#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "aabb.h"

#define MAX(a,b)	((a) > (b) ? (a) : (b))
#define MIN(a,b)	((a) < (b) ? (a) : (b))

#define frand48()  (((float)rand()) / ((float) RAND_MAX))

void
vmin(vec3d &a, const vec3d &b)
{
	a[0] = MIN(a[0], b[0]);
	a[1] = MIN(a[1], b[1]);
	a[2] = MIN(a[2], b[2]);
}

void
vmax(vec3d &a, const vec3d &b)
{
	a[0] = MAX(a[0], b[0]);
	a[1] = MAX(a[1], b[1]);
	a[2] = MAX(a[2], b[2]);
}

void
aabb::empty()
{
	_max = vec3d(INT_MIN, INT_MIN, INT_MIN);
	_min = vec3d(INT_MAX, INT_MAX, INT_MAX);
}

aabb::aabb()
{
	empty();
	_color = vec3f(frand48(), frand48(), frand48());
}

aabb::aabb(const vec3d &v)
{
	_min = _max = v;
	_color = vec3f(frand48(), frand48(), frand48());
}

aabb &
aabb::operator += (const vec3d &p)
{
	_min[0] = MIN(_min[0], p.x);
	_min[1] = MIN(_min[1], p.y);
	_min[2] = MIN(_min[2], p.z);
	_max[0] = MAX(_max[0], p.x);
	_max[1] = MAX(_max[1], p.y);
	_max[2] = MAX(_max[2], p.z);
	return *this;
}


aabb &
aabb::operator += (const aabb &b)
{
	vmin(_min, b._min);
	vmax(_max, b._max);
	return *this;
}

bool
aabb::overlaps(const aabb& b) const
{
	if (_min[0] > b._max[0]) return false;
	if (_min[1] > b._max[1]) return false;
	if (_min[2] > b._max[2]) return false;

	if (_max[0] < b._min[0]) return false;
	if (_max[1] < b._min[1]) return false;
	if (_max[2] < b._min[2]) return false;

	return true;
}

bool
aabb::inside(const vec3d &p) const
{
	if (p[0] < _min[0] || p[0] > _max[0]) return false;
	if (p[1] < _min[1] || p[1] > _max[1]) return false;
	if (p[2] < _min[2] || p[2] > _max[2]) return false;

	return true;
}



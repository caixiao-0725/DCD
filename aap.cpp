#include "aap.h"
#include <assert.h>
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#define MIN(a,b)	((a) < (b) ? (a) : (b))

aap::aap(char xyz, double p)
{
	assert(xyz >= 0 && xyz <= 2);
	this->xyz = xyz;
	this->p = p;
}

aap::aap(aabb &total)
{
	vec3d center = total.center();
	char xyz = 2;

	if (total.width() >= total.height() && total.width() >= total.depth()) {
		xyz = 0;
	} else
	if (total.height() >= total.width() && total.height() >= total.depth()) {
		xyz = 1;
	}

	this->xyz = xyz;
	this->p = center[xyz];
}
/*
float middle_xyz(char xyz, const vec3f &p1, const vec3f &p2, const vec3f &p3)
{
	float t0, t1;

	t0 = MIN(p1[xyz], p2[xyz]);
	t0 = MIN(t0, p3[xyz]);
	t1 = MAX(p1[xyz], p2[xyz]);
	t1 = MAX(t1, p3[xyz]);
	return (t0+t1)*0.5;
}*/

double aap::middle_xyz(char xyz, vec3d& p1, vec3d& p2, vec3d& p3)
{
	double t0, t1;

	t0 = MIN(p1[xyz], p2[xyz]);
	t0 = MIN(t0, p3[xyz]);
	t1 = MAX(p1[xyz], p2[xyz]);
	t1 = MAX(t1, p3[xyz]);
	return (t0 + t1) * 0.5;
}

bool
aap::inside(const vec3f &mid) const
{
	return mid[xyz]>p;
}

bool
aap::inside(const vec3d& mid) const
{
	return mid[xyz] > p;
}



bool
aap::inside(vec3d &p1,vec3d &p2,vec3d &p3) const
{
	return middle_xyz(xyz, p1, p2, p3)>p;
}


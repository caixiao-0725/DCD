#pragma once
#include <origin.h>
#include "aabb.h"


class aap {
public:
	char xyz;
	double p;

	aap(char, double);
	aap(aabb &);
	bool inside(vec3d &, vec3d &, vec3d &) const;
	bool inside(const vec3f &mid) const;
	bool inside(const vec3d& mid) const;
	static double middle_xyz(char xyz, vec3d& p1, vec3d& p2, vec3d& p3);
};


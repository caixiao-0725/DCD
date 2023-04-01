#pragma once
#include"model.h"
#include"bvh.h"
#include<vector>
#include<origin.h>

class CollideDetection {
public:
	static void execute(Model*, Model*, std::vector<BVHIndexPair>*);
private:
	static double max(double a, double b, double c);
	static double min(double a, double b, double c);
	static int project6(vec3d& ax,
						vec3d& p1,
						vec3d& p2,
						vec3d& p3,
						vec3d& q1,
						vec3d& q2,
						vec3d& q3);
	static int tri_contact(vec3d& P1,
						   vec3d& P2,
						   vec3d& P3,
						   vec3d& Q1,
						   vec3d& Q2,
						   vec3d& Q3);
};
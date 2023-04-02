#include"collide.h"

double CollideDetection::max(double a, double b, double c)
{
	double t = a;
	if (b > t) t = b;
	if (c > t) t = c;
	return t;
}

double CollideDetection::min(double a, double b, double c)
{
	double t = a;
	if (b < t) t = b;
	if (c < t) t = c;
	return t;
}

int CollideDetection::project6(vec3d& ax,
							   vec3d& p1, 
							   vec3d& p2,
							   vec3d& p3,
							   vec3d& q1, 
							   vec3d& q2, 
							   vec3d& q3)
{
	double P1 = ax.dot(p1);
	double P2 = ax.dot(p2);
	double P3 = ax.dot(p3);
	double Q1 = ax.dot(q1);
	double Q2 = ax.dot(q2);
	double Q3 = ax.dot(q3);

	double mx1 = max(P1, P2, P3);
	double mn1 = min(P1, P2, P3);
	double mx2 = max(Q1, Q2, Q3);
	double mn2 = min(Q1, Q2, Q3);

	if (mn1 > mx2) return 0;
	if (mn2 > mx1) return 0;
	return 1;
}

int
CollideDetection::tri_contact(vec3d& P1, 
							  vec3d& P2, 
							  vec3d& P3,
							  vec3d& Q1, 
							  vec3d& Q2, 
							  vec3d& Q3)
{

	vec3d p1, p2, p3;
	vec3d q1, q2, q3;
	vec3d e1, e2, e3;
	vec3d f1, f2, f3;
	vec3d g1, g2, g3;
	vec3d h1, h2, h3;
	vec3d n1, m1;
	vec3d z;

	vec3d ef11, ef12, ef13;
	vec3d ef21, ef22, ef23;
	vec3d ef31, ef32, ef33;

	

	p1 = P1 - P1;
	p2 = P2 - P1;
	p3 = P3 - P1;

	q1 = Q1 - P1;
	q2 = Q2 - P1;
	q3 = Q3 - P1;

	e1 = p2 - p1;
	e2 = p3 - p2;
	e3 = p1 - p3;

	f1 = q2 - q1;
	f2 = q3 - q2;
	f3 = q1 - q3;

	n1 = e1 ^ e2;
	m1 = f1 ^ f2;

	g1 = e1 ^ n1;
	g2 = e2 ^ n1;
	g3 = e3 ^ n1;
	h1 = f1 ^ m1;
	h2 = f2 ^ m1;
	h3 = f3 ^ m1;

	ef11 = e1 ^ f1;
	ef12 = e1 ^ f2;
	ef13 = e1 ^ f3;
	ef21 = e2 ^ f1;
	ef22 = e2 ^ f2;
	ef23 = e2 ^ f3;
	ef31 = e3 ^ f1;
	ef32 = e3 ^ f2;
	ef33 = e3 ^ f3;

	// now begin the series of tests

	if (!project6(n1, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(m1, p1, p2, p3, q1, q2, q3)) return 0;

	if (!project6(ef11, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef12, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef13, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef21, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef22, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef23, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef31, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef32, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(ef33, p1, p2, p3, q1, q2, q3)) return 0;

	if (!project6(g1, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(g2, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(g3, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(h1, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(h2, p1, p2, p3, q1, q2, q3)) return 0;
	if (!project6(h3, p1, p2, p3, q1, q2, q3)) return 0;

	return 1;
}

void CollideDetection::execute(Model* model0, Model* model1, std::vector<BVHIndexPair>* f) {
	//»¹Ô­ÑÕÉ«
	for (int i = 0; i < model0->colors_.size(); i++) {
		model0->colors_[i] = vec3f(1.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i < model1->colors_.size(); i++) {
		model1->colors_[i] = vec3f(1.0f, 1.0f, 1.0f);
	}

	std::vector<BVHIndexPair> BoxCollide;

	bvh_tree tree0 = bvh_tree(model0);
	bvh_tree tree1 = bvh_tree(model1);
	tree0.collide(&tree1, &BoxCollide);
	printf("collide box num : %d\n", BoxCollide.size());


	unsigned int id0, id1;
	vec3d p0;
	vec3d p1;
	vec3d p2;
	vec3d q0;
	vec3d q1;
	vec3d q2;

	for (int i = 0; i < BoxCollide.size(); i++) {
		BoxCollide[i].getTriPair(&id0, &id1);
		/*
		model0->colors_[model0->faces_[id0].x] = vec3f(0.0f, 0.0f, 0.0f);
		model0->colors_[model0->faces_[id0].y] = vec3f(0.0f, 0.0f, 0.0f);
		model0->colors_[model0->faces_[id0].z] = vec3f(0.0f, 0.0f, 0.0f);
		model1->colors_[model1->faces_[id1].x] = vec3f(0.0f, 0.0f, 0.0f);
		model1->colors_[model1->faces_[id1].y] = vec3f(0.0f, 0.0f, 0.0f);
		model1->colors_[model1->faces_[id1].z] = vec3f(0.0f, 0.0f, 0.0f);
		*/
		//printf("%d,%d\n", id0, id1);
		getTriangle(model0, id0, p0, p1, p2);
		getTriangle(model1, id1, q0, q1, q2);
		if (tri_contact(p0, p1, p2, q0, q1, q2)) {
			//printf("%d,%d\n", id0, id1);
			f->push_back(BVHIndexPair(id0,id1));
			model0->colors_[model0->faces_[id0].x] = vec3f(0.0f, 0.0f, 0.0f);
			model0->colors_[model0->faces_[id0].y] = vec3f(0.0f, 0.0f, 0.0f);
			model0->colors_[model0->faces_[id0].z] = vec3f(0.0f, 0.0f, 0.0f);
			model1->colors_[model1->faces_[id1].x] = vec3f(0.0f, 0.0f, 0.0f);
			model1->colors_[model1->faces_[id1].y] = vec3f(0.0f, 0.0f, 0.0f);
			model1->colors_[model1->faces_[id1].z] = vec3f(0.0f, 0.0f, 0.0f);
		}
	}
}
#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "origin.h"
#include "aabb.h"
//模型类	
using namespace std;
class Model {
public:
	Model();
	Model(const char* filename);//根据.obj文件路径导入模型
	~Model();
	int nverts();//返回模型顶点数量
	int nfaces();//返回模型面片数量
	vec3d vert(int i);//返回第i个顶点
	vec3i face(int idx);//返回第idx个面片
	vector<vec3d> verts_;//顶点集，每个顶点都是三维向量
	vector<vec3i> faces_;//面片集
	vector<vec3f> colors_;
	void draw(unsigned int shader);
	unsigned int VAO;
	unsigned int EBO;
	unsigned int VBO;
	unsigned int COLOR_VBO;
	aabb* _tri_boxes;
	vec3d* _tri_centers;
	void update(double dt);
};

#endif //__MODEL_H__
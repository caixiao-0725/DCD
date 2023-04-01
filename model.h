#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "origin.h"
#include "aabb.h"
//ģ����	
using namespace std;
class Model {
public:
	Model();
	Model(const char* filename);//����.obj�ļ�·������ģ��
	~Model();
	int nverts();//����ģ�Ͷ�������
	int nfaces();//����ģ����Ƭ����
	vec3d vert(int i);//���ص�i������
	vec3i face(int idx);//���ص�idx����Ƭ
	vector<vec3d> verts_;//���㼯��ÿ�����㶼����ά����
	vector<vec3i> faces_;//��Ƭ��
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
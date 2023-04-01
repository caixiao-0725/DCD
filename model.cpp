#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Model.h"
#include <glad/glad.h>

Model::Model() {

}

//���캯�������������.obj�ļ�·��
Model::Model(const char* filename) : verts_(), faces_() {
    std::ifstream in;
    in.open(filename, std::ifstream::in);//��.obj�ļ�
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {//û�е��ļ�ĩβ�Ļ�
        std::getline(in, line);//����һ��
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {//�����һ�е�ǰ�����ַ��ǡ�v ���Ļ��������Ƕ�������
            iss >> trash;
            vec3d v;//���붥������
            for (int i = 0; i < 3; i++) iss >> v.raw[i];
            verts_.push_back(v);//���붥�㼯
        }
        else if (!line.compare(0, 2, "f ")) {//�����һ�е�ǰ�����ַ��ǡ�f ���Ļ�����������Ƭ����
            vec3i v;
            int iuv, idx;//idx�Ƕ���������itrash������������ʱ�ò�������������ͷ�������
            iss >> trash;
            int i = 0;
            while (iss >> idx) {//��ȡx/x/x��ʽ
                idx--; // all indices start at 1, not 0
                v.raw[i] = idx;;//�������Ƭ�Ķ��㼯
                i++;
            }
            faces_.push_back(v);//�Ѹ���Ƭ����ģ�͵���Ƭ��          
        }
    }

    std::cerr << "v# " << verts_.size() << "   f# " << faces_.size() << std::endl;//�����������Ƭ����
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &COLOR_VBO);
    glGenBuffers(1, &EBO);
    // 1. ��VAO
    glBindVertexArray(VAO);
    // 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3d) * verts_.size(), verts_.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);
    
    for (int i = 0; i < verts_.size(); i++) {
        colors_.push_back(vec3f(1.0f, 1.0f, 1.0f));
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, COLOR_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * verts_.size(), colors_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3i) * faces_.size(), faces_.data(), GL_STATIC_DRAW);
    // 3. ���ö�������ָ��
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}



Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

vec3i Model::face(int i) {
    return faces_[i];
}


vec3d Model::vert(int i) {
    return verts_[i];
}

void Model::draw(unsigned int shader) {
    glUseProgram(shader);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3d) * verts_.size(), verts_.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3 * sizeof(double), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, COLOR_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f) * verts_.size(), colors_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawElements(GL_TRIANGLES, faces_.size() * 3, GL_UNSIGNED_INT, 0);
}

void Model::update(double dt) {
    for (int i = 0; i < verts_.size(); i++) {
        verts_[i] += vec3d(0, 1.0, 0)*dt;
    }

}
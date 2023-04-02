#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Model.h"
#include <glad/glad.h>

Model::Model() {

}

//构造函数，输入参数是.obj文件路径
Model::Model(const char* filename) : verts_(), faces_() {
    std::ifstream in;
    in.open(filename, std::ifstream::in);//打开.obj文件
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {//没有到文件末尾的话
        std::getline(in, line);//读入一行
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {//如果这一行的前两个字符是“v ”的话，代表是顶点数据
            iss >> trash;
            vec3d v;//读入顶点坐标
            for (int i = 0; i < 3; i++) iss >> v.raw[i];
            verts_.push_back(v);//加入顶点集
        }
        else if (!line.compare(0, 2, "f ")) {//如果这一行的前两个字符是“f ”的话，代表是面片数据
            vec3i v;
            int iuv, idx;//idx是顶点索引，itrash用来读我们暂时用不到的纹理坐标和法线向量
            iss >> trash;
            int i = 0;
            while (iss >> idx) {//读取x x x格式
                idx--; // all indices start at 1, not 0
                v.raw[i] = idx;;//加入该面片的顶点集
                i++;
            }
            faces_.push_back(v);//把该面片加入模型的面片集          
        }
    }

    std::cerr << "v# " << verts_.size() << "   f# " << faces_.size() << std::endl;//输出顶点与面片数量
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &COLOR_VBO);
    glGenBuffers(1, &EBO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用

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
    // 3. 设置顶点属性指针
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
#ifndef _ABOUTOBJ_H_
#define _ABOUTOBJ_H_

#include "head.h"

class ObjFile
{
private:
	vector<Face> faces;

public:
	void readObjFile(string fileName);//��ȡObj�ļ�
	GLuint readTexture(const char *file_name);//��ȡһ��BMP�ļ���Ϊ����
	vector<Face> getFace(){return faces;}
};

#endif
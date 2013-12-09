#ifndef _ABOUTOBJ_H_
#define _ABOUTOBJ_H_

#include "head.h"

class ObjFile
{
private:
	vector<Face> faces;

public:
	void readObjFile(string fileName);//读取Obj文件
	GLuint readTexture(const char *file_name);//读取一个BMP文件作为纹理
	vector<Face> getFace(){return faces;}
};

#endif
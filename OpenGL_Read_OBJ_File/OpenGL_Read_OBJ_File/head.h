#ifndef _OPENGLREADOBJFILE_H_
#define _OPENGLREADOBJFILE_H_

#include "stdafx.h"

#include <windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <gl/glut.h>

using namespace std;

#define _MAX_NUM 50000//最多有多少个点或面，即：max(vertexNumber,textureNumber)
class Vertex
{
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	Vertex(const Vertex &a):x(a.x),y(a.y),z(a.z){}
	Vertex(){}
};
struct Texture
{
	GLfloat x;
	GLfloat y;
};
class Face
{
private:
	Vertex vertex1,vertex2,vertex3;
	Texture texture1,texture2,texture3;
public:
	Face(vector<Vertex> &vertexs,vector<Texture> &textures,long* vertexNum,long* textureNum);

	void set(long vertex1Num,long vertex2Num,long vertex3Num,long texture1Num,long texture2Num,long texture3Num);
	Vertex getVertex1(){return vertex1;}
	Vertex getVertex2(){return vertex2;}
	Vertex getVertex3(){return vertex3;}
	Texture getTexture1(){return texture1;}
	Texture getTexture2(){return texture2;}
	Texture getTexture3(){return texture3;}
};
#endif
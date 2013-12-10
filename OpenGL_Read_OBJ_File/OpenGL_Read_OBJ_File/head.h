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
	//Vertex(const Vertex &a):x(a.x),y(a.y),z(a.z){}//前面必须要加const，不然报错
	//Vertex(){}
};
struct Texture
{
	GLfloat x;
	GLfloat y;
};
class Normal
{
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	//Normal(const Normal &a):x(a.x),y(a.y),z(a.z){}
	//Normal(){}
};
class Face
{
private:
	Vertex vertex1,vertex2,vertex3;
	Texture texture1,texture2,texture3;
	Normal normal1,normal2,normal3;
public:
	void set(vector<Vertex> &vertexs,long* vertexNum);
	void set(vector<Vertex> &vertexs,vector<Texture> &textures,long* vertexNum,long* textureNum);
	void set(vector<Vertex> &vertexs,vector<Texture> &textures,vector<Normal> &normals,long* vertexNum,long* textureNum,long* normalNum);
	Vertex getVertex1(){return vertex1;}
	Vertex getVertex2(){return vertex2;}
	Vertex getVertex3(){return vertex3;}
	Texture getTexture1(){return texture1;}
	Texture getTexture2(){return texture2;}
	Texture getTexture3(){return texture3;}
	Normal getNormal1(){return normal1;}
	Normal getNormal2(){return normal2;}
	Normal getNormal3(){return normal3;}
};
#endif
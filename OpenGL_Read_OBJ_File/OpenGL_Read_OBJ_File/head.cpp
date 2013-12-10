#include "stdafx.h"
#include "head.h"

void Face::set(vector<Vertex> &vertexs,long* vertexNum)
{
	//文件的行号是从1开始标的
	vertex1 = vertexs[vertexNum[0] - 1];//vertexNum从0开始
	vertex2 = vertexs[vertexNum[1] - 1];
	vertex3 = vertexs[vertexNum[2] - 1];
}

void Face::set(vector<Vertex> &vertexs,vector<Texture> &textures,long* vertexNum,long* textureNum)
{
	//结构体或者类可以直接赋值么？答：可以，但是如果有指针在数据成员中则不行。因为这样两个数据成员指的是同一个内存地址，会出错。实际应该是两个数据成员指向两个内存地址（new一个出来给新的，新的只是内存地址对应的值和旧的一样，地址不能一样）
	
	//文件的行号是从1开始标的
	vertex1 = vertexs[vertexNum[0] - 1];//vertexNum从0开始
	vertex2 = vertexs[vertexNum[1] - 1];
	vertex3 = vertexs[vertexNum[2] - 1];

	texture1 = textures[textureNum[0] - 1];
	texture2 = textures[textureNum[1] - 1];
	texture3 = textures[textureNum[2] - 1];
}

void Face::set(vector<Vertex> &vertexs,vector<Texture> &textures,vector<Normal> &normals,long* vertexNum,long* textureNum,long* normalNum)
{	
	//文件的行号是从1开始标的
	vertex1 = vertexs[vertexNum[0] - 1];//vertexNum从0开始
	vertex2 = vertexs[vertexNum[1] - 1];
	vertex3 = vertexs[vertexNum[2] - 1];

	texture1 = textures[textureNum[0] - 1];
	texture2 = textures[textureNum[1] - 1];
	texture3 = textures[textureNum[2] - 1];

	normal1 = normals[normalNum[0] - 1];
	normal2 = normals[normalNum[1] - 1];
	normal3 = normals[normalNum[2] - 1];
}
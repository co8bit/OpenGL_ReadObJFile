#include "stdafx.h"
#include "head.h"

void Face::set(vector<Vertex> &vertexs,long* vertexNum)
{
	//�ļ����к��Ǵ�1��ʼ���
	vertex1 = vertexs[vertexNum[0] - 1];//vertexNum��0��ʼ
	vertex2 = vertexs[vertexNum[1] - 1];
	vertex3 = vertexs[vertexNum[2] - 1];
}

void Face::set(vector<Vertex> &vertexs,vector<Texture> &textures,long* vertexNum,long* textureNum)
{
	//�ṹ����������ֱ�Ӹ�ֵô���𣺿��ԣ����������ָ�������ݳ�Ա�����С���Ϊ�����������ݳ�Աָ����ͬһ���ڴ��ַ�������ʵ��Ӧ�����������ݳ�Աָ�������ڴ��ַ��newһ���������µģ��µ�ֻ���ڴ��ַ��Ӧ��ֵ�;ɵ�һ������ַ����һ����
	
	//�ļ����к��Ǵ�1��ʼ���
	vertex1 = vertexs[vertexNum[0] - 1];//vertexNum��0��ʼ
	vertex2 = vertexs[vertexNum[1] - 1];
	vertex3 = vertexs[vertexNum[2] - 1];

	texture1 = textures[textureNum[0] - 1];
	texture2 = textures[textureNum[1] - 1];
	texture3 = textures[textureNum[2] - 1];
}

void Face::set(vector<Vertex> &vertexs,vector<Texture> &textures,vector<Normal> &normals,long* vertexNum,long* textureNum,long* normalNum)
{	
	//�ļ����к��Ǵ�1��ʼ���
	vertex1 = vertexs[vertexNum[0] - 1];//vertexNum��0��ʼ
	vertex2 = vertexs[vertexNum[1] - 1];
	vertex3 = vertexs[vertexNum[2] - 1];

	texture1 = textures[textureNum[0] - 1];
	texture2 = textures[textureNum[1] - 1];
	texture3 = textures[textureNum[2] - 1];

	normal1 = normals[normalNum[0] - 1];
	normal2 = normals[normalNum[1] - 1];
	normal3 = normals[normalNum[2] - 1];
}
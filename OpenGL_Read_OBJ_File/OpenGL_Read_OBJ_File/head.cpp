#include "stdafx.h"
#include "head.h"

Face::Face(vector<Vertex> &vertexs,vector<Texture> &textures,long* vertexNum,long* textureNum)
{
	//TODO:����ֱ�Ӹ�ֵô��
	
	//�ļ����к��Ǵ�1��ʼ���
	vertex1 = vertexs[vertexNum[0] - 1];
	vertex2 = vertexs[vertexNum[1] - 1];
	vertex3 = vertexs[vertexNum[2] - 1];

	texture1 = textures[textureNum[0] - 1];
	texture2 = textures[textureNum[1] - 1];
	texture3 = textures[textureNum[2] - 1];
}
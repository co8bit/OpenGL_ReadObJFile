#include "stdafx.h"
#include"aboutObj.h"

void ObjFile::readObjFile(string fileName)
{
	ifstream fin;
	vector<Vertex> vertexs;
	vector<Texture> textures;
	vector<Normal> normals;

	string line,word;

	fin.open(fileName);
	if(!fin)
	{
		cout<<"Read obj error !"<<endl;
		exit(0);
	}
	int j = 1;
	while(getline(fin,line))
	{
		if (j == 26950)//该处理第j行了,use for debug
		{
			j--;
			j++;
		}
		if(line.size() == 0 || line[0] == '#') {j++;continue;}
		istringstream is(line);
		is >> word;
		if(word == "v")
		{
			Vertex p;
			is>>p.x>>p.y>>p.z;
			vertexs.push_back(p);
		}
		else 
		if(word == "vt")
		{
			Texture p;
			is>>p.x>>p.y;
			textures.push_back(p);
		}
		else
		if(word == "vn")
		{
			Normal p;
			is>>p.x>>p.y>>p.z;
			normals.push_back(p);
		}
		else
		if(word == "f")
		{
			int c = 0;
			long vertexNum[3];
			long textureNum[3];
			long normalNum[3];

			int i = 0;
			Face face;
			while(is >> word)//处理每行的第1、2、3个点
			{
				c = count(word.begin(),word.end(),'/');
				if(c == 0)
				{
					vertexNum[i] = atoi(word.c_str());
				}
				else
				if(c == 1)
				{
					vertexNum[i] = atoi(string(word.begin(),word.begin()+word.find("/")).c_str());
					textureNum[i] = atoi(string(word.begin()+word.find("/")+1,word.end()).c_str());
				}
				else
				if(c == 2)
				{
					int a = word.find("/");
					int b = word.find("/",a+1);
					vertexNum[i] = atoi(string(word.begin(),word.begin()+a).c_str());
					textureNum[i] = atoi(string(word.begin()+a+1,word.begin()+b).c_str());
					normalNum[i] = atoi(string(word.begin()+b+1,word.end()).c_str());
				}
				i++;
			}
			switch (c)
			{
				case 0:face.set(vertexs,vertexNum);break;
				case 1:face.set(vertexs,textures,vertexNum,textureNum);break;
				case 2:face.set(vertexs,textures,normals,vertexNum,textureNum,normalNum);break;
				default:break;
			}
			faces.push_back(face);
		}
		j++;
	}
	fin.close();
}


inline int power_of_two(int n)
{
	if(n<=0) return 0;
	return (n&(n-1))==0;
}

GLuint ObjFile::readTexture(const char *file_name)//读取一个BMP文件作为纹理
{
	GLint width,height,total_bytes;
	GLuint last_texture_ID,texture_ID = 0;
	GLubyte *pixels = NULL;
	FILE *pFile;

	if((pFile=fopen(file_name,"rb"))==NULL)
	{
		cout<<"Read texture error"<<endl;
		return 0;
	}

	fseek(pFile,18,SEEK_SET);
	fread(&width,sizeof(width),1,pFile);
	fread(&height,sizeof(height),1,pFile);
	fseek(pFile,54,SEEK_SET);

	total_bytes = (width*3+(4-width*3%4)%4)*height;

	if((pixels=(GLubyte *)malloc(total_bytes))==NULL)
	{
		fclose(pFile);
		return 0;
	}

	if(fread(pixels,total_bytes,1,pFile)<=0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max);
		if(!power_of_two(width)||!power_of_two(height)||width>max||height>max)
		{
			const GLint new_width = 1024;
			const GLint new_height = 1024;
			GLint new_total_bytes;
			GLubyte *new_pixels = NULL;

			new_total_bytes = (new_width*3+(4-new_width*3%4)%4)*new_height;
			new_pixels = (GLubyte *)malloc(new_total_bytes);
			if(new_pixels==NULL)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			gluScaleImage(GL_RGB,width,height,GL_UNSIGNED_BYTE,pixels,new_width,new_height,GL_UNSIGNED_BYTE,new_pixels);

			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	glGenTextures(1,&texture_ID);
	if(texture_ID==0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D,(GLint *)&last_texture_ID);
	glBindTexture(GL_TEXTURE_2D,texture_ID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_BLEND);//如果要把纹理和光照混合，最后一个参数应该是GL_BLEND或者GL_MODULATE等，表示将光照结果与纹理颜色进行叠加，而不能仅使用纹理颜色来替换原有的像素颜色，这样就只能看见纹理，显示不了光照结果了。 
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pixels);
	glBindTexture(GL_TEXTURE_2D,last_texture_ID);

	free(pixels);
	fclose(pFile);
	return texture_ID;
}


// OpenGL_Read_OBJ_File.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "head.h"
#include"aboutObj.h"

GLfloat dx = 0,dy = 0,dz = 0;
GLfloat ax = 0,ay = 0,az = 0;
GLint mx = 0,my = 0;
GLint MouseDown = 0;
GLfloat aspect = 1;
vector<Face> faces;
GLuint texture;

void myIdle()
{
	Sleep(10);
	glutPostRedisplay();
}

void myReshape(int width,int height)
{
	aspect = (float)width/(height?height:1);
	glViewport(0,0,width,height);//ʹ�� glViewport �������ӿڡ�����ǰ���������������ӿڵ����½ţ�0,0 ��ʾ�����·����������������ֱ��ǿ�Ⱥ͸߶�
	glMatrixMode(GL_PROJECTION);//׼������ͶӰ�任������ѡ������
	glLoadIdentity();//������Ҫ�ڽ��б任ǰ�ѵ�ǰ��������Ϊ��λ����
	gluPerspective(75, 1, 1, 400000000);//��ͶӰ�൱��������Զ���۲�õ��Ľ��������һ������״̬
	glMatrixMode(GL_MODELVIEW);//���õ�ǰ�����ľ���Ϊ�� ģ����ͼ���󡱡�
	glLoadIdentity();
	gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);//ǰ����������ʾ�˹۲���λ�ã��м�����������ʾ�˹۲�Ŀ���λ�ã�����������������(0,0,0)��(x,y,z)��ֱ�ߣ�����ʾ�˹۲�����Ϊ�ġ��ϡ�����
}

void myKeyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'w':
		dz+=1.0f;
		break;
	case 's':
		dz-=1.0f;
		break;
	case 'a':
		dx-=1.0f;
		break;
	case 'd':
		dx+=1.0f;
		break;
	case 'q':
		dy+=1.0f;
		break;
	case 'e':
		dy-=1.0f;
		break;
	}
}

void myMouse(int button,int state,int x,int y)
{
	if(button==GLUT_DOWN) MouseDown = 1,mx = x,my = y;
	else if(button==GLUT_WHEEL_UP)
	{
		dz+=1.0f;
	}
	else if(button==GLUT_WHEEL_DOWN)
	{
		dz-=1.0f;
	}
	else
	{
		MouseDown = 0;
	}
}

void myMotion(int x,int y)
{
	if(MouseDown)
	{
		ax += (y-my)/5.0f;
		ay += (x-mx)/5.0f;
		mx = x;
		my = y;
	}
}

void setLight()//���ù�Դ
{
	/*
	 *��һ�ֹ�Դ
	 */
	static const GLfloat light_position[] = {50.0f,50.0f,50.0f,0.0f};//��ʾ��Դ���ڵ�λ�á����ĸ�ֵ��X, Y, Z, W����ʾ��������ĸ�ֵ WΪ�㣬���ʾ�ù�Դλ������Զ����ǰ����ֵ��ʾ�������ڵķ������ֹ�Դ��Ϊ�����Թ�Դ��ͨ����̫�����Խ��Ƶı���Ϊ�Ƿ����Թ�Դ��������ĸ�ֵ W ��Ϊ�㣬�� X/W, Y/W, Z/W ��ʾ�˹�Դ��λ�á����ֹ�Դ��Ϊλ���Թ�Դ��
	static const GLfloat light_ambient[] = {0.0f,0.0f,0.0f,0.0f};//��ʾ�ù�Դ�������Ĺ⣬�����ǳ���εķ���������������������ջ����е�ǿ�ȣ���ɫ����
	static const GLfloat light_diffuse[] = {1.0f,0.9f,0.9f,0.0f};//��ʾ�ù�Դ�������Ĺ⣬���䵽�ֲڱ���ʱ���������䣬���õ��Ĺ��ǿ�ȣ���ɫ����
	static const GLfloat light_specular[] = {1.0f,1.0f,1.0f,0.0f};//��ʾ�ù�Դ�������Ĺ⣬���䵽�⻬����ʱ�������淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ����
	static const GLfloat light_direction[] = {-1.0f,-1.0f,-1.0f};

	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);

	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light_direction);//��Դ����ķ���
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,10.0f);//��ʾ�۹�ĳ̶ȣ�Ϊ��ʱ��ʾ���շ�Χ�����������Ĺ���ǿ����ͬ��Ϊ����ʱ��ʾ���������뼯�У����Է��䷽���λ���ܵ�������գ�����λ���ܵ����ٹ��ա���ֵԽ�󣬾۹�Ч����Խ���ԡ�
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,120.0f);//���ǹ�Դ������������ǽǶȵ�һ�루��ͼ 2������ȡֵ��Χ�� 0 �� 90 ֮�䣬Ҳ����ȡ 180 �������ֵ��ȡֵΪ 180 ʱ��ʾ��Դ������߸��� 360 �ȣ�����ʹ�þ۹�ƣ���ȫ��Χ���䡣
	
	//glLightfv(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	//*/
	
	/*
	 *�ڶ���̫����Դ������һ�ְ�ɫ�Ĺ�Դ
	 *
	{
		GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	} 
	*/
}

void setMaterial()// ��������Ĳ���
{
		/*
		 *��һ�ֲ���
		 *
		GLfloat sun_mat_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_diffuse[]  = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
		GLfloat sun_mat_shininess  = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT,   sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION,  sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
		*/

		/*
		 *�ڶ��ֲ���
		 */
		GLfloat earth_mat_ambient_and_diffuse[]  = {0.5f, 0.5f, 0.5f, 1.0f};//��ʾ���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ���� 
		//ͨ����GL_AMBIENT �� GL_DIFFUSE ��ȡ��ͬ��ֵ�����Դﵽ�Ƚ���ʵ��Ч����
		//GLfloat earth_mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};//��ʾ�������䵽�ò����ϣ�������������γɵĹ���ǿ�ȣ���ɫ����
		GLfloat earth_mat_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};//��ʾ�������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���ɫ����
		GLfloat earth_mat_shininess  = 30.0f;//������ֻ��һ��ֵ����Ϊ������ָ������ȡֵ��Χ�� 0 �� 128����ֵԽС����ʾ����Խ�ֲڣ����Դ����Ĺ������䵽���棬Ҳ���Բ����ϴ�����㡣��ֵԽ�󣬱�ʾ����Խ�����ھ��棬��Դ���䵽����󣬲�����С�����㡣
		GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};//���������ĸ�ֵ��ɣ���ʾһ����ɫ��OpenGL ��Ϊ�ò��ʱ����΢΢�����ⷢ����ߣ��������۾��о���������������ɫ����������ֱȽ�΢���������ڲ���Ӱ�쵽�����������ɫ��
		glMaterialfv(GL_FRONT, GL_AMBIENT,   earth_mat_ambient_and_diffuse);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   earth_mat_ambient_and_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  earth_mat_specular);
		glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION,  earth_mat_emission);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//����
	glPushMatrix();
	

	//�����ӽ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 400000000);

	//��ͼ�任
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dx,dy,dz);
	glRotatef(ax,1.0f,0.0f,0.0f);
	glRotatef(ay,0.0f,1.0f,0.0f);

	setLight();
	setMaterial();
	
	glBindTexture(GL_TEXTURE_2D,texture);//ʹ������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for (int i = 0; i < faces.size(); i++)
	{
		glBegin(GL_TRIANGLES);
		
		
		glTexCoord2f(faces[i].getTexture1().x,faces[i].getTexture1().y);
		glNormal3f(faces[i].getNormal1().x,faces[i].getNormal1().y,faces[i].getNormal1().z);
		glVertex3f(faces[i].getVertex1().x,faces[i].getVertex1().y,faces[i].getVertex1().z);//����Ļ���Ӧ����󣬲�Ȼ����Ϊ������������
		
		
		glTexCoord2f(faces[i].getTexture2().x,faces[i].getTexture2().y);
		glNormal3f(faces[i].getNormal2().x,faces[i].getNormal2().y,faces[i].getNormal2().z);
		glVertex3f(faces[i].getVertex2().x,faces[i].getVertex2().y,faces[i].getVertex2().z);
		
		
		glTexCoord2f(faces[i].getTexture3().x,faces[i].getTexture3().y);
		glNormal3f(faces[i].getNormal3().x,faces[i].getNormal3().y,faces[i].getNormal3().z);
		glVertex3f(faces[i].getVertex3().x,faces[i].getVertex3().y,faces[i].getVertex3().z);
		
		glEnd();
	}
	

	glFlush ();

	glPopMatrix();
    glutSwapBuffers();
}

void init(int tempObj = 3,int tempTexture = 4)
{
	ObjFile objFile;
	
	switch (tempObj)
	{
	case 1:objFile.readObjFile("Ball_dABF.obj");break;
	case 2:objFile.readObjFile("Beetle_ABF.obj");break;
	case 3:objFile.readObjFile("Cow_dABF.obj");break;
	case 4:objFile.readObjFile("Gargoyle_ABF.obj");break;
	case 5:objFile.readObjFile("Isis_dABF.obj");break;
	default:break;
	}
	faces = objFile.getFace();

	
	switch (tempTexture)
	{
	case 0:texture = 0;break;
	case 1:texture = objFile.readTexture("Texture.bmp");break;
	case 2:texture = objFile.readTexture("Texture2.bmp");break;
	case 3:texture = objFile.readTexture("metal.bmp");break;
	case 4:texture = objFile.readTexture("defaulttext.bmp");break;
	default:break;
	}

	glClearColor(0.93,0.94,0.98,1.0);//1,1,1�ǰ�ɫ
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

int _tmain(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(320,180);
	glutInitWindowSize(1280,720);
	glutCreateWindow("OpenGl");

	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboard);
	glutMouseFunc(&myMouse);
	glutMotionFunc(&myMotion);
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);

	init(2,4);

	glutMainLoop();
	return 0;
}


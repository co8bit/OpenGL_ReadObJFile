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
	gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
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

void setLight()
{
	static const GLfloat light_position[] = {50.0f,50.0f,50.0f,0.0f};
	static const GLfloat light_ambient[] = {0.0f,0.0f,0.0f,0.0f};
	static const GLfloat light_diffuse[] = {1.0f,0.9f,0.9f,0.0f};
	static const GLfloat light_specular[] = {1.0f,1.0f,1.0f,0.0f};
	static const GLfloat light_direction[] = {-1.0f,-1.0f,-1.0f};

	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light_direction);
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,10.0f);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,120.0f);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
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

	for (int i = 0; i < faces.size(); i++)
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);
  
		glVertex3f(faces[i].getVertex1().x,faces[i].getVertex1().y,faces[i].getVertex1().z);
  
		
		glVertex3f(faces[i].getVertex2().x,faces[i].getVertex2().y,faces[i].getVertex2().z);
  
		
		glVertex3f(faces[i].getVertex3().x,faces[i].getVertex3().y,faces[i].getVertex3().z);
  
		glEnd();
	}

	glFlush ();

	glPopMatrix();
    glutSwapBuffers();
}

void init()
{
	ObjFile objFile;
	objFile.readObjFile("Cow_dABF.obj");
	faces = objFile.getFace();

	glClearColor(0.93,0.94,0.98,1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	setLight();
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
	init();

	glutMainLoop();
	return 0;
}


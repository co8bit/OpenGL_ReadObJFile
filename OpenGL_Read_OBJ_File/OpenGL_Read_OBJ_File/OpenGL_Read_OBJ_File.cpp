// OpenGL_Read_OBJ_File.cpp : 定义控制台应用程序的入口点。
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
	glViewport(0,0,width,height);//使用 glViewport 来定义视口。其中前两个参数定义了视口的左下脚（0,0 表示最左下方），后两个参数分别是宽度和高度
	glMatrixMode(GL_PROJECTION);//准备操作投影变换矩阵，先选择上它
	glLoadIdentity();//我们需要在进行变换前把当前矩阵设置为单位矩阵。
	gluPerspective(75, 1, 1, 400000000);//正投影相当于在无限远处观察得到的结果，它是一种理想状态
	glMatrixMode(GL_MODELVIEW);//设置当前操作的矩阵为“ 模型视图矩阵”。
	glLoadIdentity();
	gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);//前三个参数表示了观察点的位置，中间三个参数表示了观察目标的位置，最后三个参数代表从(0,0,0)到(x,y,z)的直线，它表示了观察者认为的“上”方向。
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

void setLight()//设置光源
{
	/*
	 *第一种光源
	 */
	static const GLfloat light_position[] = {50.0f,50.0f,50.0f,0.0f};//表示光源所在的位置。由四个值（X, Y, Z, W）表示。如果第四个值 W为零，则表示该光源位于无限远处，前三个值表示了它所在的方向。这种光源称为方向性光源，通常，太阳可以近似的被认为是方向性光源。如果第四个值 W 不为零，则 X/W, Y/W, Z/W 表示了光源的位置。这种光源称为位置性光源。
	static const GLfloat light_ambient[] = {0.0f,0.0f,0.0f,0.0f};//表示该光源所发出的光，经过非常多次的反射后，最终遗留在整个光照环境中的强度（颜色）。
	static const GLfloat light_diffuse[] = {1.0f,0.9f,0.9f,0.0f};//表示该光源所发出的光，照射到粗糙表面时经过漫反射，所得到的光的强度（颜色）。
	static const GLfloat light_specular[] = {1.0f,1.0f,1.0f,0.0f};//表示该光源所发出的光，照射到光滑表面时经过镜面反射，所得到的光的强度（颜色）。
	static const GLfloat light_direction[] = {-1.0f,-1.0f,-1.0f};

	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);

	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light_direction);//光源发射的方向
	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,10.0f);//表示聚光的程度，为零时表示光照范围内向各方向发射的光线强度相同，为正数时表示光照向中央集中，正对发射方向的位置受到更多光照，其它位置受到较少光照。数值越大，聚光效果就越明显。
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,120.0f);//它是光源发射光线所覆盖角度的一半（见图 2），其取值范围在 0 到 90 之间，也可以取 180 这个特殊值。取值为 180 时表示光源发射光线覆盖 360 度，即不使用聚光灯，向全周围发射。
	
	//glLightfv(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	//*/
	
	/*
	 *第二种太阳光源，它是一种白色的光源
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

void setMaterial()// 设置物体的材质
{
		/*
		 *第一种材质
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
		 *第二种材质
		 */
		GLfloat earth_mat_ambient_and_diffuse[]  = {0.5f, 0.5f, 0.5f, 1.0f};//表示各种光线照射到该材质上，经过很多次反射后最终遗留在环境中的光线强度（颜色）。 
		//通常，GL_AMBIENT 和 GL_DIFFUSE 都取相同的值，可以达到比较真实的效果。
		//GLfloat earth_mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};//表示光线照射到该材质上，经过漫反射后形成的光线强度（颜色）。
		GLfloat earth_mat_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};//表示光线照射到该材质上，经过镜面反射后形成的光线强度（颜色）。
		GLfloat earth_mat_shininess  = 30.0f;//该属性只有一个值，称为“镜面指数”，取值范围是 0 到 128。该值越小，表示材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
		GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};//该属性由四个值组成，表示一种颜色。OpenGL 认为该材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色，但这光线又比较微弱，以至于不会影响到其它物体的颜色。
		glMaterialfv(GL_FRONT, GL_AMBIENT,   earth_mat_ambient_and_diffuse);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   earth_mat_ambient_and_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  earth_mat_specular);
		glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION,  earth_mat_emission);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//操作
	glPushMatrix();
	

	//设置视角
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 400000000);

	//视图变换
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(dx,dy,dz);
	glRotatef(ax,1.0f,0.0f,0.0f);
	glRotatef(ay,0.0f,1.0f,0.0f);

	setLight();
	setMaterial();
	
	glBindTexture(GL_TEXTURE_2D,texture);//使用纹理
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for (int i = 0; i < faces.size(); i++)
	{
		glBegin(GL_TRIANGLES);
		
		
		glTexCoord2f(faces[i].getTexture1().x,faces[i].getTexture1().y);
		glNormal3f(faces[i].getNormal1().x,faces[i].getNormal1().y,faces[i].getNormal1().z);
		glVertex3f(faces[i].getVertex1().x,faces[i].getVertex1().y,faces[i].getVertex1().z);//定点的绘制应在最后，不然就认为这个点绘制完了
		
		
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

	glClearColor(0.93,0.94,0.98,1.0);//1,1,1是白色
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


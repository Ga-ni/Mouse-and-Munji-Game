// ConsoleApplication2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <gl/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

void init();
void display();
void timer(int);
void keyboard_handler(unsigned char key);
void drawMunji(int);
static int delay = 1;
static GLfloat viewer[3] = { 3.0, 3.0, 3.0 };
float theta = 0.0, theta2 = 0.0;
int two_state = 0, state = 0;
GLUquadricObj *pQuad;
float x = 3, y = 3, z = 3;

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Walking person");
	//glutTimerFunc(delay, timer, 0);
	//glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
void keyboard_handler(unsigned char key)
{
	if (key == 'x') x += 0.1;
	if (key == 'X') x -= 0.1;
	if (key == 'y') x += 0.1;
	if (key == 'Y') x -= 0.1;
	if (key == 'z') x += 0.1;
	if (key == 'Z') x -= 0.1;
	if (key == 'p')
	{
		if (state == 0)
		{
			state = 1;
			init();
		}
		else
		{
			state = 0;
			init();
		}
	}
	glutPostRedisplay();
}
void init()
{
	pQuad = gluNewQuadric();
	glMatrixMode(GL_PROJECTION); // change to projection view
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glClearColor(125 / 255.0, 206 / 255.0, 250 / 255.0, 1.0);
	glClearColor(255 / 255.0, 255 / 255.0, 255 / 255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glFrustum(-50.0, 50.0, -50.0, 50.0, -10.0, -50.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}
void timer(int t)
{
	theta += 1;
	//theta2 += 1;
	if (theta > 360)
		theta -= 360;
	if (two_state == 0)
		theta2 += 0.5;
	if (two_state == 1)
		theta2 -= 0.5;
	if (theta2 > 3)
		two_state = 1;
	if (theta2 < -3)
		two_state = 0;
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}
void drawSphere(int r, int b)
{
	float x, y, z = 0, la, lo;
	double PI = atan(1.0)*4.0;
	for (la = -80; la < 80; la = la + b)
	{
		glBegin(GL_QUAD_STRIP);
		for (lo = -180; lo <= 180; lo = lo + b)
		{
			x = 0.1f * r*sin(lo*PI / 180)*cos(la*PI / 180);
			y = 0.1f * r*cos(lo*PI / 180)*cos(la*PI / 180);
			z = 0.1f * r*sin(la*PI / 180);
			glVertex3f(x, y, z);
			x = 0.1f * r*sin(lo*PI / 180)*cos((la + b)*PI / 180);
			y = 0.1f * r*cos(lo*PI / 180)*cos((la + b)*PI / 180);
			z = 0.1f * r*sin((la + b)*PI / 180);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f - r*0.1);
	la = -80;
	for (lo = -180; lo <= 180; lo = lo + b)
	{
		x = 0.1f * r*sin(lo*PI / 180)*cos(la*PI / 180);
		y = 0.1f * r*cos(lo*PI / 180)*cos(la*PI / 180);
		z = 0.1f * r*sin(la*PI / 180);
		glVertex3f(x, y, z);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f + r*0.1);
	la = 80;
	for (lo = -180; lo <= 180; lo = lo + b)
	{
		x = 0.1f * r*sin(lo*PI / 180)*cos(la*PI / 180);
		y = 0.1f * r*cos(lo*PI / 180)*cos(la*PI / 180);
		z = 0.1f * r*sin(la*PI / 180);
		glVertex3f(x, y, z);
	}
	glEnd();
}


void drawCircle(float a, int b)
{
	double PI = atan(1.0)*4.0;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f);
	for (int i = -180; i <= 180; i = i + b)
	{
		double radian = i*PI / 180;
		glVertex3f(0.1f*sin(radian)*cos(0)*a, 0.1f*cos(radian)*cos(0)*a, 0.1f*sin(0));
	}
	glEnd();
}


void drawCylinder(float under, float up, float length, int num1, int num2, float color, float green)
{
	double PI = atan(1.0)*4.0;
	float x = (up - under) / num1;
	glPushMatrix();
	for (float i = 0; i < num1; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (int j = -180; j <= 180; j = j + num2)
		{
			double radian = j*PI / 180;
			glVertex3f(0.1f*sin(radian)*cos(0) * up, 0.1f*cos(radian)*cos(0) * up, 0.1f*sin(0));
			glVertex3f(0.1f*sin(radian)*cos(0) * (up - x), 0.1f*cos(radian)*cos(0) * (up - x), 0.1f*sin(0) + 0.1*(length / ((float)num1)));
		}
		glEnd();
		up = up - x;
		glTranslatef(0.0, 0.0, 0.1*length / ((float)num1));
	}
	glPopMatrix();
}


//void drawFeather(float length, float thick, float color, float green)
//{
//	glColor3f(0.7, 0.35, 0.0);
//	glPushMatrix();
//	drawCircle(0.05*thick, 20);
//	drawCylinder(0.1*thick, 0.05*thick, 1.5*length, 20, 20, color, green);
//	glTranslatef(0.0, 0.0, 0.15*length);
//	drawCylinder(0.0, 0.1*thick, 0.25*length, 20, 20, color, green);
//	glPopMatrix();
//}
//void firstWing(int num, int r)
//{
//	float color = 0, size = 5;
//	glPushMatrix();
//	for (int i = 0; i < num; i++)
//	{
//		drawFeather(size, size, color, 0);
//		size += 2.0 / (float)num;
//		color -= color / (float)num;
//		glTranslatef(0.0, 0.02, 0.0);
//		glRotatef(-theta2*r, 0.0, 0.0, 1.0);
//		glRotatef(-2 * (i + 1) / 8, 1.0, 0.0, 0.0);
//	}
//	glPopMatrix();
//}
//void lastWing(int num, float angle, int r)
//{
//	float color = 0, size = 5;
//	glPushMatrix();
//	for (int i = 0; i < num; i++)
//	{
//		glRotatef((-angle)*r, 0.0, 1.0, 0.0);
//		drawFeather(size, 7, color, 0);
//	}
//	glPopMatrix();
//}
//void head(float a, float b, float angle, int r)
//{
//	float color = 0.35, length = 2.5;
//	glPushMatrix();
//	double PI = atan(1.0)*4.0;
//	for (int i = -180; i <= 180; i = i + b)
//	{
//		double radian = i*PI / 180;
//		GLfloat x = 0.1f*sin(radian)*cos(0)*a;
//		GLfloat y = 0.1f*cos(radian)*cos(0)*a;
//		GLfloat z = 0.1f*sin(0);
//		glPushMatrix();
//		glTranslatef(x, y, z);
//		if (i < 0)
//			glRotatef(angle*r, 0.0, 1.0, 0.0);
//		else if (i == 0)
//			glRotatef(angle*r, 0.0, 0.0, 0.0);
//		else
//			glRotatef((-angle)*r, 0.0, 1.0, 0.0);
//		drawFeather(length, 11, 2, 1.1);
//		//gluSphere(pQuad, 0.1, 20, 20);
//		glPopMatrix();
//	}
//	glPopMatrix();
//}


void drawMunji(int num)
{
	GLfloat x = 0, y = 0;

	glLineWidth(1);

	glBegin(GL_LINES);
	for (int i = 0; i<num; i = i + 5)
	{
		glVertex2f(0.0, 0.0);
		double angle = i*3.141592 / 180;
		x = 0.14*(cos(angle) * 10) / 2;
		y = 0.14*(sin(angle) * 10) / 2;

		glVertex2f(x, y);

	}
	//roatate(30,)
	for (int i = 0; i<num; i = i + 5)
	{
		glVertex2f(0.0, 0.0);
		double angle = i*3.141592 / 180;
		x = 0.14*(cos(angle) * 10) / 2;
		y = 0.14*(sin(angle) * 10) / 2;

		glVertex2f(x, y);

	}
	glEnd();
}
void drawRoom() {

	glScaled(2, 2, 2);
	//glRotated(5, 1, 0,0 );
	glTranslated(-15, -15, -15);


	glColor3f(255.0 / 255.0, 153.0 / 255.0, 204.0 / 255.0);
	glBegin(GL_POLYGON);
	//glVertex3f(-1.0, -1.0, -1.0); glVertex3f(1.0, -1.0, -1.0); glVertex3f(1.0, -1.0, 1.0); glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(0, 15, 35); glVertex3f(40, 15, 35); glVertex3f(40, 30, 15); glVertex3f(20, 30, 15);
	//glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(40, 20, 15); glVertex3f(20, 20, 15);
	glEnd(); //아래쪽

	glColor3f(204.0 / 255.0, 102.0 / 255.0, 153.0 / 255.0);
	glBegin(GL_POLYGON);
	//glVertex3f(-1.0, -1.0, 1.0); glVertex3f(1.0, -1.0, 1.0); glVertex3f(1.0, 1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(20, 20, 15); glVertex3f(40, 20, 15); glVertex3f(40, 40, 15); glVertex3f(20, 40, 15);
	glEnd(); //앞쪽

	glColor3f(153.0 / 255.0, 51.0 / 255.0, 102.0 / 255.0);
	glBegin(GL_POLYGON);
	//glVertex3f(-1.0, -1.0, -1.0); glVertex3f(-1.0, -1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0); glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(0, 15, 35); glVertex3f(20, 20, 15); glVertex3f(20, 40, 15); glVertex3f(15, 40, 35);
	glEnd();
	//왼쪽

	glFlush();


}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85.0, 1.0, 5.0, 50.0);
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glTranslatef(0.0, 0.0, -0.3);
	//glOrtho(0.0, 50.0, 0.0, 50.0, -50.0, 50.0);
	//gluLookAt(3, 0, 0, 0, 0, 0, 0, 1, 0);
	//gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);


	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	drawRoom();
	glPopMatrix();
	glLoadIdentity();


	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		float x = -20 + (rand() % 40);
		float y = -20 + (rand() % 40);
		float z = (rand() % 5);
		x /= 10; y /= 10; z /= 10;
		printf("%f %f %f\n", x, y, z);

		glPushMatrix();

		glTranslatef(x, y, z);
		glScaled(0.5, 0.5, 0.5);
		//z축 40부터 65 x축, y축 5부터 45
		glColor3f(0.0, 0.0, 0.0);
		//gluSphere(pQuad, 0.5, 20, 20);
		glutSolidSphere(0.5, 20, 20);

		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-0.13, 0.04, 0.4);
		glutSolidSphere(0.14, 20, 20);
		//gluSphere(pQuad, 0.14, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-0.09, 0.06, 0.5);
		gluSphere(pQuad, 0.05, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.13, 0.04, 0.4);
		gluSphere(pQuad, 0.14, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.09, 0.06, 0.5);
		gluSphere(pQuad, 0.05, 20, 20);
		glPopMatrix();


		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -0.1);
		drawMunji(360);
		glPopMatrix();

		glPopMatrix();
	}

	//srand(time(NULL));
	//for (int i = 0; i < 10; i++) {
	//   int x = 5 + (rand() % 40);
	//   int y = 5 + (rand() % 40);
	//   int z = 40 + (rand() % 10);
	//   glPushMatrix();
	//   //z축 40부터 65 x축, y축 5부터 45
	//   glTranslatef(x, y, z);
	//   glScalef(4, 4, 4);
	//   glColor3f(0.0, 0.0, 0.0);
	//   gluSphere(pQuad, 0.5, 20, 20);

	//   glPushMatrix();
	//   glColor3f(1.0, 1.0, 1.0);
	//   glTranslatef(-0.13, 0.04, 0.4);
	//   gluSphere(pQuad, 0.14, 20, 20);
	//   glPopMatrix();

	//   glPushMatrix();
	//   glColor3f(0.0, 0.0, 0.0);
	//   glTranslatef(-0.09, 0.06, 0.5);
	//   gluSphere(pQuad, 0.05, 20, 20);
	//   glPopMatrix();

	//   glPushMatrix();
	//   glColor3f(1.0, 1.0, 1.0);
	//   glTranslatef(0.13, 0.04, 0.4);
	//   gluSphere(pQuad, 0.14, 20, 20);
	//   glPopMatrix();

	//   glPushMatrix();
	//   glColor3f(0.0, 0.0, 0.0);
	//   glTranslatef(0.09, 0.06, 0.5);
	//   gluSphere(pQuad, 0.05, 20, 20);
	//   glPopMatrix();


	//   glPushMatrix();
	//   glColor3f(0.0, 0.0, 0.0);
	//   glTranslatef(0.0, 0.0, -0.1);
	//   drawMunji(360);
	//   glPopMatrix();

	//   glPopMatrix();
	//}





	glutSwapBuffers();
	glFlush();
}
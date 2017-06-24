// ConsoleApplication2.cpp : ÄÜ¼Ö ÀÀ¿ë ÇÁ·Î±×·¥¿¡ ´ëÇÑ ÁøÀÔÁ¡À» Á¤ÀÇÇÕ´Ï´Ù.
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
void drawMunji(int);
void keyboard_handler(unsigned char, int, int);
static int delay = 1;
float theta = 0.0, theta2 = 0.0;
int two_state = 0, state = 0;
GLUquadricObj *pQuad;
static GLfloat transX = 0.0;
static GLfloat transY = 0.0;
static GLfloat transZ = 0.0;
static GLfloat scale = 1.0;
static GLfloat minZ = 100.0;
static GLfloat maxZ = -100.0;
static GLfloat rotate = 0.0;
static GLfloat munjiArr[10][3] = { 0, };


int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Walking person");
	//glutTimerFunc(delay, timer, 0);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}



void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		rotate = -90.0;
		transX -= 0.1; glutPostRedisplay();
		
	}

	if (key == 'w')
	{
		transY += 0.05;

			glutPostRedisplay();

	}
	if (key == 's')
	{
		transY -= 0.05; 
		
			glutPostRedisplay();
	}
	if (key == 'd')
	{
		rotate = 90.0;
		transX += 0.1; glutPostRedisplay();
	}
	if (key == 'e')
	{
		rotate = 0.0;
		if (transZ <= maxZ) {
			transZ += 0.05; glutPostRedisplay();
		}
	}
	if (key == 'q')
	{
		rotate = 180.0;
		if (minZ <= transZ + 1.0) {
			transZ -= 0.05;  glutPostRedisplay();
		}
	}
		
}
void init()
{
	pQuad = gluNewQuadric();
	glMatrixMode(GL_PROJECTION); // change to projection view
	glLoadIdentity();

	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(125 / 255.0, 206 / 255.0, 250 / 255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	
	minZ = 100.0;
	maxZ = -100.0;
	for (int i = 0; i < 10; i++) {
		munjiArr[i][0] = -20 + (rand() % 40);
		munjiArr[i][1] = -20 + (rand() % 40);
		munjiArr[i][2] = -20 + (rand() % 20); //(rand() % 5);
		munjiArr[i][0] /= 10; munjiArr[i][1] /= 10; munjiArr[i][2] /= 10;
		if (munjiArr[i][2] <= minZ) {
			minZ = munjiArr[i][2];
		}
		if (munjiArr[i][2] >= maxZ) {
			maxZ = munjiArr[i][2];
		}
	}
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
			//glColor3f(1.0, 1.0, 1.0);
			//glColor3f((fabs(i) / (float)num1) / 2.0 + color, (fabs(i) / (float)num1) / 4.0 + color, green);
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
void drawFeather(float length, float thick, float color, float green)
{
	glColor3f(0.7, 0.35, 0.0);
	glPushMatrix();
	drawCircle(0.05*thick, 20);
	drawCylinder(0.1*thick, 0.05*thick, 1.5*length, 20, 20, color, green);
	glTranslatef(0.0, 0.0, 0.15*length);
	drawCylinder(0.0, 0.1*thick, 0.25*length, 20, 20, color, green);
	glPopMatrix();
}
void firstWing(int num, int r)
{
	float color = 0, size = 5;
	glPushMatrix();
	for (int i = 0; i < num; i++)
	{
		drawFeather(size, size, color, 0);
		size += 2.0 / (float)num;
		color -= color / (float)num;
		glTranslatef(0.0, 0.02, 0.0);
		glRotatef(-theta2*r, 0.0, 0.0, 1.0);
		glRotatef(-2 * (i + 1) / 8, 1.0, 0.0, 0.0);
	}
	glPopMatrix();
}
void lastWing(int num, float angle, int r)
{
	float color = 0, size = 5;
	glPushMatrix();
	for (int i = 0; i < num; i++)
	{
		glRotatef((-angle)*r, 0.0, 1.0, 0.0);
		drawFeather(size, 7, color, 0);
	}
	glPopMatrix();
}
void head(float a, float b, float angle, int r)
{
	float color = 0.35, length = 2.5;
	glPushMatrix();
	double PI = atan(1.0)*4.0;
	for (int i = -180; i <= 180; i = i + b)
	{
		double radian = i*PI / 180;
		GLfloat x = 0.1f*sin(radian)*cos(0)*a;
		GLfloat y = 0.1f*cos(radian)*cos(0)*a;
		GLfloat z = 0.1f*sin(0);
		glPushMatrix();
		glTranslatef(x, y, z);
		if (i < 0)
			glRotatef(angle*r, 0.0, 1.0, 0.0);
		else if (i == 0)
			glRotatef(angle*r, 0.0, 0.0, 0.0);
		else
			glRotatef((-angle)*r, 0.0, 1.0, 0.0);
		drawFeather(length, 11, 2, 1.1);
		//gluSphere(pQuad, 0.1, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();
}



void drawMunji(int num)
{

	GLfloat x = 0, y = 0;

	glLineWidth(1);

	glBegin(GL_LINES);
	for (int i = 0; i < num; i = i + 5)
	{
		glVertex2f(0.0, 0.0);
		double angle = i*3.141592 / 180;
		x = 0.14*(cos(angle) * 10) / 2;
		y = 0.14*(sin(angle) * 10) / 2;

		glVertex2f(x, y);

	}
	//roatate(30,)
	for (int i = 0; i < num; i = i + 5)
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
	glVertex3f(0, 15, 35); glVertex3f(40, 15, 35); glVertex3f(40, 30, 15); glVertex3f(20, 30, 15);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35); glVertex3f(40, 20, 15); glVertex3f(20, 20, 15);
	glEnd();

	glColor3f(204.0 / 255.0, 102.0 / 255.0, 153.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex3f(20, 20, 15); glVertex3f(40, 20, 15); glVertex3f(40, 40, 15); glVertex3f(20, 40, 15);
	glEnd();//¿ÞÂÊ



	glColor3f(153.0 / 255.0, 51.0 / 255.0, 102.0 / 255.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 15, 35); glVertex3f(20, 20, 15); glVertex3f(20, 40, 15); glVertex3f(15, 40, 35);
	glEnd();
	//¾ÕÂÊ

	glFlush();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
	//gluLookAt(3, 0, 0, 0, 0, 0, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	//glRotated(-10, 1, 0, 0);
	

	glPushMatrix();
	glTranslatef(transX, transY, transZ);
	glScalef(scale, scale, scale);
	
	
	
	glRotatef(rotate, 0, 1, 0);
	

	glPushMatrix();
	glColor3f(0.847059, 0.74902, 0.847059);
	glTranslatef(0.0, 0.02, 0.0);
	gluSphere(pQuad, 0.59, 20, 20);//À­¸Ó¸®
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.847059, 0.74902, 0.847059);
	drawCylinder(6.3, 6, 5.5, 20, 20, 0, 0);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0.0);
	glColor3f(0.847059, 0.74902, 0.847059);
	gluSphere(pQuad, 0.18, 20, 20);//¿ÞÂÊ±Í
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.44, 0.44, 0.1);
	glScaled(1.2, 1.2, 1.2);
	glColor3f(0.854902, 0.439216, 0.839216);
	gluSphere(pQuad, 0.09, 20, 20);//¿ÞÂÊ ¾È¿¡ ±Í
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.0);
	glColor3f(0.847059, 0.74902, 0.847059);
	gluSphere(pQuad, 0.18, 20, 20);//¿À¸¥ÂÊ±Í
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.44, 0.44, 0.1);
	glScaled(1.2, 1.2, 1.2);
	glColor3f(0.854902, 0.439216, 0.839216);
	gluSphere(pQuad, 0.09, 20, 20);//¿À¸¥ÂÊ ¾È¿¡ ±Í
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.15, -0.4, 0.0);
	glColor3f(0.847059, 0.74902, 0.847059);
	//gluSphere(pQuad, 0.45, 20, 20);
	glutSolidSphere(0.6, 20, 20);
	glPopMatrix();//¿ÞÂÊ º¼


	glPushMatrix();
	glTranslatef(0.15, -0.4, 0.0);
	glColor3f(0.847059, 0.74902, 0.848059);
	gluSphere(pQuad, 0.6, 20, 20);
	glPopMatrix();// ¿À¸¥ÂÊ º¼




	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.2, -0.2, 0.55);
	gluSphere(pQuad, 0.1, 20, 20);
	glPopMatrix();//¿ÞÂÊ ´«(Èò)

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.19, -0.2, 0.6);
	glScaled(1.2, 1.2, 1.2);
	gluSphere(pQuad, 0.05, 20, 20);
	glPopMatrix();//¿ÞÂÊ ´«(°Ë)

	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.2, -0.2, 0.55);
	gluSphere(pQuad, 0.1, 20, 20);
	glPopMatrix();//¿À¸¥ÂÊ ´«(Èò)

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.19, -0.2, 0.6);
	glScaled(1.2, 1.2, 1.2);
	gluSphere(pQuad, 0.05, 20, 20);
	glPopMatrix();//¿À¸¥ÂÊ ´«(°Ë)

	glPushMatrix();
	glColor3f(1, 0.270588, 0);
	glTranslatef(0, -0.35, 0.65);
	gluSphere(pQuad, 0.05, 20, 20);
	glPopMatrix();//ÄÚ


	glPushMatrix();
	glTranslatef(0.0, -1.3, 0.00);
	glColor3f(201.0 / 255.0, 163.0 / 255.0, 196.0 / 255.0);
	gluSphere(pQuad, 0.89, 20, 20);//À­¸ö
	glPopMatrix();

	//glPushMatrix();
	//glTranslatef(0.0, -1.6, 0.05);
	//glScaled(2, 2, 2);
	//glColor3f(0.847059, 0.74902, 0.848059);
	///*glColor3f(250.0 / 255.0, 235.0 / 255.0, 255.0 / 255.0);*/
	//gluSphere(pQuad, 0.5, 20, 20);//¹è¶§Áö
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -2.15, 0);
	glScaled(2, 2, 2);
	glColor3f(0.847059, 0.74902, 0.848059);
	drawSphere(1, 2);
	glPopMatrix();//¿À¸¥´Ù¸®

	glPushMatrix();
	glTranslatef(-0.5, -2.15, 0);
	glScaled(2, 2, 2);
	glColor3f(0.847059, 0.74902, 0.848059);
	drawSphere(1, 2);
	glPopMatrix();//¿Þ´Ù¸®

	glPushMatrix();
	glTranslatef(0.89, -0.8, 0);
	glScaled(1.4, 1.4, 1.4);
	glColor3f(0.847059, 0.74902, 0.848059);
	drawSphere(1, 2);
	glPopMatrix();//¿À¸¥ÆÈ

	glPushMatrix();
	glTranslatef(-0.89, -0.8, 0);
	glScaled(1.4, 1.4, 1.4);
	glColor3f(0.847059, 0.74902, 0.848059);
	drawSphere(1, 2);
	glPopMatrix();//¿ÞÆÈ
	glPopMatrix();
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		
		printf("%f %f %f\n", munjiArr[i][0], munjiArr[i][1], munjiArr[i][2]);
		glPushMatrix();
		glTranslatef(munjiArr[i][0], munjiArr[i][1], munjiArr[i][2]);
		glScaled(0.5, 0.5, 0.5);
		//zÃà 40ºÎÅÍ 65 xÃà, yÃà 5ºÎÅÍ 45
		glColor3f(0.0, 0.0, 0.0);
		gluSphere(pQuad, 0.5, 20, 20);

		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-0.13, 0.04, 0.4);
		gluSphere(pQuad, 0.14, 20, 20);
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

	glPopMatrix();
	glutSwapBuffers();
	glFlush();
}
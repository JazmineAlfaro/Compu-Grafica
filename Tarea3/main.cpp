#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <math.h>
#include<GL/glut.h>
#include <unistd.h>
#define KEY_ESC 27
#include <utility>
#include <time.h>
#include <vector>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
#define PI 3.14159265359

float w, h;

GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };
	
	//enable light : try without it
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	//light 0 "on": try without it
	glEnable(GL_LIGHT0);
	
	//shading model : try GL_FLAT
	glShadeModel(GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	
	//enable material : try without it
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glClearColor(RED, GREEN, BLUE, ALPHA);
}

float a = 0.0;
void tetera(){
	
	glTranslatef(0,0,-30);
	
	/*gluPerspective(60.0,1*w/h,1.0,30);
	glTranslatef(0,0,-30);*/
	
	//glOrtho(-w/32, w/32, -h/32, h/32, -25.0f, 25.0f);
	glPushMatrix();
	
	glColor3f(1,1,1);
	glTranslatef(4*cos(a),4*sin(a),0);
	glutSolidTeapot(2.0);
	a+=0.03;
	
	glPopMatrix();
	glutSwapBuffers();
	
	glFlush();
}
	
float t = 0.0;
void sphere(){
	t+=0.001;
	glColor3d(0,0,1);
	glTranslatef(4*cos(t),4*sin(t),0);
	glutSolidSphere(2.0,20,20);
	
}
	
float f = 0.0;
float v = 0.0;
float centerx = 0.0;
float centery = 0.0;
void solar_system(){
	
	f+=0.2;
	v+=0.2;
	
gluPerspective(60.0,1*w/h,1.0,50);
	gluLookAt(0, 0, 50, 0,3*sin(f*PI/180), 0, 0, 1, 0);
	
	
	glTranslatef(0,0,-50);
	
	glPushMatrix();
	//sol
	glColor3d(1,1,0);
	glRotatef(v,0,0,1);
	glutSolidSphere(4,8,8);
	
	glPushMatrix();
	
	//tierra
	glColor3d(0,0,1);
	glRotatef(3*v,0,0,1);
	glTranslatef(10*cos(f*PI/180),10*sin(f*PI/180),0);
	centerx = 10*cos(f*PI/180);
	centery = 10*sin(f*PI/180);
	glutSolidSphere(2,8,8);
	
	
	//luna
	glColor3d(1,1,1);
	glRotatef(1.5*v,0,0,1);
	glTranslatef(3*cos(f*PI/180),3*sin(f*PI/180),0);
	glutSolidSphere(0.5,8,8);
	glPopMatrix();
	
	
	glPushMatrix();
	glColor3d(1,0,0);
	glRotatef(v,0,0,1);
	glTranslatef(18*cos(f*PI/180),18*sin(f*PI/180),0);
	
	
	
	glutSolidSphere(1,8,8);
	glPopMatrix();
	
	glPopMatrix();
	
	
	glutSwapBuffers();
	
	glFlush();
	
}		
		
int pos = 1;
void window_display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-w/32, w/32, -h/32, h/32, -25.0f, 25.0f);
	
	if (pos == 1) {
		gluPerspective(60.0,1*w/h,1.0,50);
		//gluLookAt(0, 0, 50, 0,3*sin(f*PI/180), 3*cos(f*PI/180), 0, 1, 0);
	} else {
		gluPerspective(60.0,1*w/h,1.0,50);
		gluLookAt(0, 0, 50, centerx,centery, 0, 0, 1, 0);
	}
	
	
			
	switch(pos){
		case(1):
			tetera();
			break;
		case(2):
			solar_system();
			break;
	}

	/*
	glutSwapBuffers();
	
	glFlush();
	*/
}
					
void window_reshape(GLsizei width, GLsizei height){
	
	w = width;
	h = height;
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-25.0f, 25.0f, -25.0f, 25.0f, -25.0f, 25.0f);
	
	glMatrixMode(GL_MODELVIEW);
}
	

void window_key(int key, int x, int y)
{
	/*if(key == GLUT_KEY_RIGHT){
		glutPostRedisplay();
	}
	
	if(key == GLUT_KEY_LEFT){
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_UP){
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_DOWN){
		glutPostRedisplay();
	}
	if(key == GLUT_KEY_RIGHT){
		glutPostRedisplay();
	}*/
	
	if(key == GLUT_KEY_F1){
		
		if(pos>1) pos-=1;
		
		cout<<pos<<endl;
		window_display();
	}
	
	if(key == GLUT_KEY_F2){
		if(pos<5) pos+=1;
		else if (pos==5) pos=1;
		
		cout<<pos<<endl;
		window_display();
		
		
		
	}
	
	glutPostRedisplay();	
	
}
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
	}
}				
						
GLvoid callback_motion(int x, int y)
{
	
	glutPostRedisplay();						
}	

void window_idle(){
	glutPostRedisplay();
}
	

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TP 3 : ");
	
	
	initGL();
	//init_scene();
	
	glutDisplayFunc(&window_display);
	glutIdleFunc(&window_idle);
	glutReshapeFunc(&window_reshape);
	
	glutSpecialFunc(window_key);
//	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	
	glutMainLoop();
	
	return 1;
}

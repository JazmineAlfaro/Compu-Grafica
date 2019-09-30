

#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>

#include<GL/glut.h>
#include <unistd.h>
#define KEY_ESC 27
#include <utility>
#include <time.h>
#include <vector>
#include <math.h>
using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27
# define PI           3.14159265358979323846  // pi 
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
glColor3f(1,0,1);
glRotatef(a,0,0,1);
glTranslatef(4,0,0);
glutSolidTeapot(2.0);

a+=0.15;

}

float t = 0.0;
float s = 0.0;
void sphere(){
t+=0.001;
s+=0.15;
glColor3d(0,0,1);
glTranslatef(8*cos(t),0,0);
glutSolidSphere(2.0,20,20);
glColor3d(1,1,1);
glRotatef(s,0,0,1);
glTranslatef(10,0,0);
glutSolidTeapot(2.0);


}

float d = 0.0;
float b = 0.0;
float c = 0.0;
void system(){
b += 0.001;
glTranslatef(8*cos(b),0.0,0.0); 
glColor3d(0,0,1);
glutSolidSphere(1,20,20);

c += 0.15;
glPushMatrix();
glColor3d(1,1,1);
glRotatef(c,0,0,1);
glTranslatef(10,0,0);
glutSolidTeapot(2.0);

glColor3d(1,1,0);
glRotatef(c*3,0,1,0);
glTranslatef(5,0,0);
//glutSolidTorus(2.0);
glutSolidTorus(0.5,1.0,20,20);
glPopMatrix();

glPushMatrix();
glColor3d(1,1,1);
glRotatef(c,1,0,0);
glTranslatef(0,10,0);
glutSolidCube(2.0);
glPopMatrix();

}	

float f = 0.0;
float v = 0.0;
void solar_system(){
f+=0.01;
v+=0.05;

glPushMatrix();
//sol
glColor3d(1,1,0);
glRotatef(v,0,0,1);
glutSolidSphere(4,8,8);

glPushMatrix();
//tierra
glColor3d(0,0,1);
glRotatef(3*v,0,0,1);
glTranslatef(10,0,0);
glRotatef(f,0,0,1);
glutSolidSphere(2,8,8);
//luna
glColor3d(1,1,1);
glRotatef(1.5*v,0,0,1);

glTranslatef(4,0,0);
glRotatef(2*f,0,0,1);
glutSolidSphere(0.5,8,8);
glPopMatrix();


glPushMatrix();
glColor3d(1,0,0);
glRotatef(v,0,0,1);
glTranslatef(18,0,0);
glRotatef(f,0,0,1);
glutSolidSphere(1,8,8);
glPopMatrix();

glPopMatrix();
}		

void rectangulo(float w, float h){
	
	glBegin(GL_POLYGON);
	glRotatef(50*PI/180,1,0,0);
	glVertex2f(0,-h/2);
	glVertex2f(0,h/2);
	glVertex2f(w,h/2);
	glVertex2f(w,-h/2);
	glEnd();
	
}




int pos = 0;
void window_display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w/32, w/32, -h/32, h/32, -25.0f, 25.0f);
	/*
	switch(pos){
	case(1):
		tetera();
	break;
	case(2):
		sphere();
	break;
	case(3):
		system();
	break;
	case(4):
		solar_system();
	break;
	}
	*/

	glBegin(GL_LINE_LOOP);
	glColor3d(0,0,255);
	glVertex2f(0,0);
	glVertex2f(0,20);
	
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3d(255,0,0);
	glVertex2f(0,0);
	glVertex2f(20,0);
	
	glEnd();
	
	glColor3f(1,0.5,0);
	rectangulo(4,2);
	
	
	
	
	
	glPushMatrix();
	glColor3f(1,1,0);
	rectangulo(10,1);
	
	
	
	glutPostRedisplay();
	glPopMatrix();
	
	glutSwapBuffers();

	glFlush();
}

void window_reshape(GLsizei width, GLsizei height){

w = width;
h = height;
glViewport(0, 0, width, height);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0f, 300.0f, 0.0f, 300.0f, -1.0f, 1.0f);

glMatrixMode(GL_MODELVIEW);
}


void window_key(int key, int x, int y)
{
	if(key == GLUT_KEY_RIGHT){
		if(pos<5) pos+=1;
		else if (pos==5) pos=1;
		
		cout<<pos<<endl;
		window_display();
	}
	
	if(key == GLUT_KEY_LEFT){
		if(pos>1) pos-=1;
		
		cout<<pos<<endl;
		window_display();
	}
	
}


//function called on each frame
void window_idle(){
	glutPostRedisplay();
}
	
	
	int main(int argc, char **argv)
	{
		glutInit(&argc, argv);
		
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		
		
		glutInitWindowSize(600, 600);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("TP 2 : Transformaciones");
		
		
		initGL();
		//init_scene();
		
		glutDisplayFunc(&window_display);
		
		glutReshapeFunc(&window_reshape);
		
		glutSpecialFunc(window_key);
		
		//function called on each frame
		glutIdleFunc(&window_idle);
		
		glutMainLoop();
		
		return 1;
	}



#define GLUT_DISABLE_ATEXIT_HACK
//#include <windows.h>
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

bool r = false;
int mx = 0;
int my = 0;

float ax = 0.0;
float ay = 0.0;
float speed = 0.1;

void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mx = x;
		my = y;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

		r = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		r = false;
	}
}

void OnMouseMotion(int x, int y) {
	int dx = mx - x;
	int dy = my - y;
	
	mx = x;
	my = y;
	
	ax += dx * speed;
	ay += dy * speed;
}



GLvoid initGL(){
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
	
void circulo(float cx, float cy, float r, int num_segments){
	glBegin(GL_POLYGON);
	for(int i = 0; i < num_segments; ++i){
		float theta = 2.0f * PI * float(i) / float(num_segments);//get the current angle
		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component
		glVertex3f(x + cx, y + cy,0);//output vertex
	}
	
	glEnd();
}

void rectangulo(float w, float h){
	glBegin(GL_POLYGON);
	glVertex3f(0,-h/2,0);
	glVertex3f(0,h/2,0);
	glVertex3f(w,h/2,0);
	glVertex3f(w,-h/2,0);
	glEnd();
	
}

float funround(float var){ 
	float value = (int)(var * 100 + .5); 
	return (float)value / 100; 
} 	
	
	
float calcular_x1(float tam, float angle){
	float x1 = sin(angle*PI/180) * tam;
	return funround(x1);
}

float calcular_y1(float x1, float tam){
	float y1 = pow(tam,2) - pow(x1,2);
	y1 = sqrt(y1);
	return funround(y1) ;
}

float angle1 = 45.0 ;
float angle2 = 30.0 ;
float tam1 = 5;
float tam2 = 8;
float tam3 = 7;
float g = 1; // grosor
float len = 6.0;	
float radio = 1;
	
void window_display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w/32, w/32, -h/32, h/32, -25.0f, 25.0f);

	float cx1 = calcular_x1(tam2,angle1);
	float cy1 = calcular_y1(cx1,tam2);
	
	if(angle1>90 && angle1<=270){
		cy1 = -cy1;
	}
	
	float cx2 = calcular_x1(tam3,angle2);
	float cy2 = calcular_y1(cx2,tam3);
	
	if(angle2>90 && angle2<=270){
		cy2 = -cy2;
	}
	
	
	glPushMatrix();
		glColor3f(1,0.5,0);
		glTranslatef(-tam1/2,0,0);
		rectangulo(tam1,g);
	glPopMatrix();

	
	glPushMatrix();
		glColor3f(1,0,1);
		glRotatef(angle1,0,0,1);
		rectangulo(tam2,g);
	glPopMatrix();
	
	
	
	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(cy1,cx1,0);
		glRotatef(angle2,0,0,1);
		rectangulo(tam3,g);
	glPopMatrix();
	
	
	
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(cy1+cy2,cx1+cx2-len,0);
	circulo(0,0,radio,50);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(cy1+cy2,cx1+cx2,0);
		glBegin(GL_LINES);
			glColor3f(0,1,0);
			glVertex3f(0,0,0);
			glVertex3f(0,-len,0);
		glEnd();
	glPopMatrix();
	
	
	
	if(angle1 > 360){
		angle1 -= 360;
	}
	
	if(angle2 > 360){
		angle2 -= 360;
	}
	
	glutSwapBuffers();
}

void window_reshape(GLsizei width, GLsizei height){

w = width;
h = height;
glViewport(0, 0, width, height);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0f, 400.0f, 0.0f, 400.0f, -1.0f, 1.0f);

glMatrixMode(GL_MODELVIEW);
}


void window_key(int key, int x, int y)
{
	if(key == GLUT_KEY_RIGHT){
		angle2-= 1.0;
		window_display();
	}
	
	if(key == GLUT_KEY_LEFT){
		angle2 += 1.0;
		window_display();
	}
	
	if(key == GLUT_KEY_UP){
		angle1 += 1.0;
		window_display();
	}
	
	if(key == GLUT_KEY_DOWN){
		angle1 -= 1.0;
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
	
	
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Grúa");
	
	
	initGL();
	//init_scene();
	
	glutDisplayFunc(&window_display);
	
	glutReshapeFunc(&window_reshape);
	
	glutSpecialFunc(window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	//function called on each frame
	glutIdleFunc(&window_idle);
	
	glutMainLoop();
	
	return 1;
}

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif


#define GLUT_DISABLE_ATEXIT_HACK	
#include <windows.h>
#include <math.h>
#define pi 3.14159265359
#define KEY_ESC 27
#include<iostream>

using namespace std;

void drawCircle(float c_x, float c_y, float r){
	glBegin(GL_LINE_LOOP);
	glColor3d(255,0,0);
	int s = 50;
	for(int i = 0; i < s; i++){
		float angle = 2 * pi* i / float(s);
		float x = r * cos(angle);
		float y = r * sin(angle);
		glVertex2f(x + c_x, y + c_y);
	}
	glEnd();
}

void cuadrado(float centrox,float centroy, float tam){
	glBegin(GL_LINE_LOOP);
	glColor3d(0,0,255);
	glVertex2f(centrox-tam,centroy-tam);
	glVertex2f(centrox+tam,centroy-tam);
	glVertex2f(centrox+tam,centroy+tam);
	glVertex2f(centrox-tam,centroy+tam);
	glEnd();
}

void circulos(int num, float p_radio, float f_radio){
	float rad = f_radio;
	for(int i=0;i<num;++i){
		drawCircle(rad-f_radio,0,rad);
		rad -= rad*p_radio;
	}
	
}
	
void circulos2(int num, float p_radio, float f_radio){
	float c_x = -40;
	float rad = f_radio;
	for(int i=0;i<num;++i){
		cout<<"C_X: "<<c_x<<"RAD: "<<rad<<endl;
		drawCircle(c_x,0,rad);
		c_x += rad;
		rad -= rad*p_radio;
		c_x += rad;
		cout<<rad<<endl;
	}		
}

	
void circulos3(int num, float p_radio, float f_radio, float angle){
	float c_x = -40;
	float c_y = -40; 
	float rad = f_radio;
	float aux;
	float dis ;
	for(int i=0;i<num;++i){
		drawCircle(c_x,c_y,rad);
		dis = rad;
		rad -= rad*p_radio;
		dis += rad;
		c_y += dis*sin(angle/180*pi);
		c_x += dis*sin((90-angle)/180*pi);
	}		
}

//dibuja un simple gizmo
void displayGizmo(){
	//circulos3(10,0.1,20,50);
}

int pos = 0 ;
//
//funcion llamada a cada imagen
void glPaint(void) {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//El fondo de la escena al color initial
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glLoadIdentity();
	
	
	switch(pos){
	case(1):
		cuadrado(0,0,30);
		break;
	case(2):
		drawCircle(0, 0, 6);
		break;
	case(3):
		circulos(10,0.1,20);
		break;
	case(4):
		circulos2(10,0.1,20);
		break;
	case(5):
		circulos3(10,0.1,20,50);
		break;
	}
	
	
	
	//dibuja el gizmo
	//displayGizmo();
	
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	
	//modo projeccion 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(-100.0f,  100.0f,-100.0f, 100.0f, -1.0f, 1.0f); 
	
	//xmin,xmax,ymin,ymax
	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}


GLvoid window_key(unsigned char key, int x, int y) {
	/*switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	
	default:
		break;
	}
	*/
	if(key == 'c'){
		if(pos<5) pos+=1;
		else if (pos==5) pos=1;
		
		cout<<pos<<endl;
		
		glPaint();
		//else 
	}
}
//
//el programa principal
//
int main(int argc, char** argv) {
	
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP1 OpenGL : hello_world_OpenGL"); //titulo de la ventana
	
	init_GL(); //funcion de inicializacion de OpenGL
	
	glutDisplayFunc(glPaint); 
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	
	glutMainLoop(); //bucle de rendering
	
	return 0;
}

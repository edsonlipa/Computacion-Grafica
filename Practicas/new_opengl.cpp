#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"

using namespace std;
int x1=0,x2=0,y_1=3,y2=3;
#define radio 150
#define nLados 3
#define M_pi 3.141592653589793238

void Inicio()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.2,0.2,0.2,0);
  gluOrtho2D(-500,500,-500,500);
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
      glColor3f(0.0,1.0,1.0);
      glPointSize(6);
      glBegin(GL_POINTS);
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)),
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}
void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	int x0=-250,y0=-250,xend=+250,yend=250;
  // punto_medio( x0, y0,  xend,  yend);
  // incremental_basico(x0,y0,xend,yend);
	// draw_line(x0,y0,xend,yend);
  drawHollowCircle(0,0,200);

  drawHollowCircle(0,250,80);

  drawHollowCircle(-200,200,80);
  drawHollowCircle(200,200,80);

  drawHollowCircle(-200,-200,80);
  drawHollowCircle(200,-200,80);
	glFlush();
}
void keyboard(unsigned char key, int x, int y) {
switch (key) {
  case 'c':
    if (glIsEnabled(GL_CULL_FACE))
      glDisable(GL_CULL_FACE);
    else
      glEnable(GL_CULL_FACE);
    break;
  case 'w':
            glTranslatef(0.0f, 1.0f, 0.0f);
        break;

  case 's':
      glTranslatef(0.0f, -1.0f, 0.0f);
      break;

  case 'a':
      glTranslatef(-1.0f, 0.0f, 0.0f);
      break;

  case 'd':
      glTranslatef(1.0f, 0.0f, 0.0f);
      break;
  case 'j':
      glTranslatef(1.0, 0.0, 1.0);
      break;
  case 'k':
      glTranslatef(1.0, 0.0, -1.0);
      break;
  case '1':
      glRotatef(5.0,0.,0.,1.);
    break;
  case '2':
      glRotatef(5.0,0.,0.,-1.);
      break;
  case '3':
      glRotatef(1.0,1.,0.,0.);

      break;
  }
  glutPostRedisplay();
}
void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
int main ( int argc , char ** argv )
{
glutInit (&argc,argv ) ;
glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ) ;
glutInitWindowPosition (500 , 100) ;
glutInitWindowSize ( 500,500 ) ;
glutCreateWindow ( " Algoritmos Lineas " ) ;
Inicio() ;
// glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutKeyboardFunc(keyboard);
glutDisplayFunc (draw) ;
// glutDisplayFunc (display) ;
glutMainLoop () ;

}

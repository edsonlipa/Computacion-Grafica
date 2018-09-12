#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"

using namespace std;
#define radio 150
#define nLados 3
#define M_pi 3.141592653589793238

void Inicio()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(1.0,1.0,1.0,0.0);
  gluOrtho2D(-500,500,-500,500);
}

void draw_line(int x0,int y0, int xf, int yf)
{

  glBegin(GL_LINES);
	glColor3f(0.1,0.0,1.0);
	glVertex2i(x0,y0);
	glVertex2i(xf,yf);
	glEnd();
}
void draw_poligon() {
	glClear(GL_COLOR_BUFFER_BIT);
  double current_x=radio*cos(0),current_y=radio*sin(0);
  double new_x,new_y;
  if (nLados>2) {
    double section =360/nLados;
    for (double i = section; i <= 360; i+=section) {
      new_x=radio*cos((i*M_pi)/180);
      new_y=radio*sin((i*M_pi)/180);
      draw_line(current_x,current_y,new_x,new_y);

      current_x=new_x;
      current_y=new_y;
    }

  }
  glFlush();

}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	GLint x0=0,y0=0,xf=0,yf=100;
	draw_line(x0,y0,xf,yf);
	glFlush();
}

int main ( int argc , char ** argv )
{
glutInit (&argc,argv ) ;
glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ) ;
glutInitWindowPosition (500 , 100) ;
glutInitWindowSize ( 500,500 ) ;
glutCreateWindow ( " poligonos regulares con n lados " ) ;
Inicio() ;
glutDisplayFunc (draw_poligon) ;
glutMainLoop () ;
return 0;
}

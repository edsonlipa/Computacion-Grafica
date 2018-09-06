#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"

using namespace std;
int x1=0,x2=0,y_1=3,y2=3;
void Inicio()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.5,0.5,0.5,0);
  gluOrtho2D(-500,500,-500,500);
}
void draw_point(int x,int y){
	glColor3f(1.0,0.3,0.5);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void incremental_basico(int x0,int y0, int xend, int yend){
  std::cout << "/* incremental basico */" << '\n';
  int x=0,y=0,valor;
	float m=(yend-y0)/(xend-x0);
	for(x=x0;x<=xend;x++){
		  y=(y0+m*(x-x0));
		  draw_point(x,y);
	}
}
void punto_medio(int x0,int y0, int xend, int yend){
  std::cout << "/* punto medio */" << '\n';
  int dx,dy,incE,incNE,d,x,y;
	dx=xend-x0;
	dy=yend-y0;
	d=2*dy-dx; /* Valor inicial de d*/
	incE=2*dy; /*Incremento de E*/
	incNE=2*(dy-dx);/* Incremento de NE*/
	x=x0;
	y=y0;
	draw_point(x,y);
	while (x < xend){
		if(d <=0){
			d=d+incE;
			x=x+1;
		}else{
		   d=d+incNE;
		   x=x+1;
		   y=y+1;
		}
		draw_point(x,y);
	}
}
void draw_line(int x0,int y0, int xend, int yend)
{
	glBegin(GL_LINES);
	glColor3f(1.0,1.0,1.0);
	glVertex2i(x0,y0);
	glVertex2i(xend,yend);
	glEnd();
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	int x0=-250,y0=-250,xend=+250,yend=250;
  // punto_medio( x0, y0,  xend,  yend);
  incremental_basico(x0,y0,xend,yend);
	draw_line(x0,y0,xend,yend);

	glFlush();
}

int main ( int argc , char ** argv )
{
glutInit (&argc,argv ) ;
glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ) ;
glutInitWindowPosition (500 , 100) ;
glutInitWindowSize ( 500,500 ) ;
glutCreateWindow ( " Algoritmos Lineas " ) ;
Inicio() ;
glutDisplayFunc (draw) ;
glutMainLoop () ;

}

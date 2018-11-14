#include <bits/stdc++.h>
#include "GL/freeglut.h"
#include "GL/gl.h"

using namespace std;
#define radio 150
#define nLados 3
#define M_pi 3.141592653589793238
int n_vertices;
bool save_points;
std::vector<pair<int,int>> vertices;
std::set<pair<int,int>> puntos;
std::set<pair<int,int>> painted;


void Inicio()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(0.2,0.2,0.2,0);
	glOrtho(-500,500,-500,500,-1.0,1.0);
  // gluOrtho2D(-500,500,-500,500);
}
void draw_point(int x,int y){
	// glColor3f(1.0,0.3,0.5);//rosado
	glColor3f(0.0,1.0,1.0);//celeste
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	if(save_points)puntos.insert(make_pair(x,y));
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
  // std::cout << "/* punto medio */" << '\n';
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
void draw_line(int x0,int y0, int xend, int yend){
	glBegin(GL_LINES);
	glColor3f(1.0,1.0,1.0);
	glVertex2i(x0,y0);
	glVertex2i(xend,yend);
	glEnd();
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
void bresenham(float x1, float y1, float x2, float y2){
    // Find Delta
    float dx = x2-x1;
    float dy = y2-y1;
    // Find Signs
    int sx = (dx>=0) ? 1 : (-1);
    int sy = (dy>=0) ? 1 : (-1);
    // Get Initial Points
    float x = x1;
    float y = y1;
    // Flag to check if swapping happens
    int isSwaped = 0;
    // Swap if needed
    if(abs(dy) > abs(dx))
    {
        // swap dx and dy
        float tdx = dx;
        dx =dy;
        dy = tdx;

        isSwaped = 1;
    }

    // Decision parameter
    float p = 2*(abs(dy)) - abs(dx);

    //Print Initial Point
    draw_point(x,y);
    // Loop for dx times
    for(int i = 0; i<= abs(dx);i++)
    {
        // Depending on decision parameter
        if(p < 0)
        {
            if(isSwaped == 0){
                x = x + sx;
                draw_point(x,y);
            }
            else{
                y = y+sy;
                draw_point(x,y);
            }
            p = p + 2*abs(dy);
        }
        else
        {
            x = x+sx;
            y = y+sy;
            draw_point(x,y);
            p = p + 2*abs(dy) - 2*abs(dx);
        }
    }
}
void draw_polygon_by_click(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
			std::cout << "/* click*/ "<<x<<" "<<y << '\n';
        if ( vertices.size()<n_vertices )
					vertices.push_back( make_pair(x-500,500-y) );
    }

}
void mouse_move(int x, int y){
		std::cout << x<<"-" << y<<"///"<<x-500<< "-"<< 500-y<< '\n';
		glutPostRedisplay();
		// glColor3f(0.0,1.0,1.0);
		// glPointSize(6);
		// glBegin(GL_POINTS);
		// glVertex2f(
		// 		x ,
		// 		y );
}
void detectarBorde(float x1,float y1,float x2,float y2,int *le,int *re){
    float temp,x,mx;
    int i;

    if(y1>y2)
    {
        temp=x1,x1=x2,x2=temp;
        temp=y1,y1=y2,y2=temp;
    }

    if(y1==y2)
        mx=x2-x1;
    else
        mx=(x2-x1)/(y2-y1);

    x=x1;

    for(i=int(y1);i<=(int)y2;i++)
    {
        if(x<(float)le[i]) le[i]=(int)x;
        if(x>(float)re[i]) re[i]=(int)x;
        x+=mx;
    }
}


void paint_polygon(vector<pair<int,int>> V){
		// int
		int le[1000],re[1000],i,j;
    for(i=0;i<1000;i++)
        le[i]=1000,re[i]=0;
    int p=0;
    for(p=0;p<V.size()-1;p++){
        detectarBorde(V[p].first,V[p].second,V[p+1].first,V[p+1].second,le,re);
    }
    detectarBorde(V[p].first,V[p].second,V[0].first,V[0].second,le,re);
    for(j=0;j<1000;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<re[j];i++)
                // draw_point(i,j);
								painted.insert(make_pair(i,j));
    }
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	int x0=-250,y0=-250,xend=+250,yend=250;
  // incremental_basico(x0,y0,xend,yend);
	// draw_line(x0,y0,xend,yend);
	std::cout << "/* 					n */"<< vertices.size() << '\n';
	if (!vertices.empty() )
 {
		 for (int v = 0; v < vertices.size()-1; v++) {
			 bresenham(vertices[v].first, vertices[v].second, vertices[v+1].first,vertices[v+1].second);

		 }
		 if (n_vertices==vertices.size()) {
			 bresenham(vertices[n_vertices-1].first, vertices[n_vertices-1].second, vertices[0].first,vertices[0].second);
			 save_points=false;
		 }
		 paint_polygon(vertices);
		 if (!save_points) {
		 	for (auto p:painted) {
		 		draw_point(p.first,p.second);
		 	}
		 }
 }
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
	      glScalef(2,2,2);
	      break;
	  case 'k':
	      glScalef(0.5,0.5,0.5);
	      break;
	  case 'q':
	      glRotatef(5.0,0.,0.,1.);
	    break;
	  case 'e':
	      glRotatef(-5.0,0.,0.,1.);
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
	if (argc==2) {
		n_vertices=stoi(argv[1]);
		save_points=true;
	}else{
		return 0;
	}
glutInit (&argc,argv ) ;
glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ) ;
glutInitWindowPosition (500 , 100) ;
glutInitWindowSize ( 1000,1000) ;
glutCreateWindow ( " poligonos y pintado " ) ;
Inicio() ;
// glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);

glutPassiveMotionFunc (mouse_move);
glutMouseFunc(draw_polygon_by_click);
glutDisplayFunc (draw) ;
// glutDisplayFunc (display) ;
glutMainLoop () ;

}

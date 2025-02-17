/*
* Author : Neevan Redkar
* Date : 2025-01-31
*/

#include <GL/glut.h>
#include <iostream>

void myInit(void){
  glClearColor(1.0,1.0,1.0,1.0);
  glPointSize(4.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-640.0,640.0,-360.0,360.0);
}

void plotAxes(){
    for(int i=-640;i<640;i++){
        glBegin(GL_POINTS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2i(i,0);
        glEnd();
    }
    for(int i=-360;i<360;i++){
        glBegin(GL_POINTS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2i(0,i);
        glEnd();
    }
    glFlush();
}


void bresemhamCirc(int rad,int h,int k){
    int x=0,y=rad;
    int d=3-2*rad;
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    while(x<=y){
        if(d<=0){
            d=d+4*x+6;
        }else{
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
        glBegin(GL_POINTS);
        glVertex2i(x+h,y+k);
        glVertex2i(-x+h,y+k);
        glVertex2i(x+h,-y+k);
        glVertex2i(-x+h,-y+k);
        glVertex2i(y+h,x+k);
        glVertex2i(-y+h,x+k);
        glVertex2i(y+h,-x+k);
        glVertex2i(-y+h,-x+k);
        glEnd();
    }
    glFlush();

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f,0.0f,0.0f);
    bresemhamCirc(100,200,200);
    glColor3f(1.0f,0.0f,0.0f);
    bresemhamCirc(100,500,200);
    plotAxes();
    glFlush();
}

int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(1280,720);
  glutInitWindowPosition(100,150);
  glutCreateWindow("Bresenham Circle Drawing");
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();
  return 0;
}
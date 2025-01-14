/*
  Author : Neevan Redkar 
  Date : 2025-01-14

*/


#include <GL/glut.h>
#include <math.h>
#define pi 3.14159

void myInit(void){
  glClearColor(1.0,1.0,1.0,1.0);
  glColor3f(0.0f,0.0f,0.0f);
  glPointSize(4.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,640.0,0.0,480.0);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINES);
   glVertex2i(200,360);
   glVertex2i(400,360);
   glVertex2i(400,360);
   glVertex2i(450,300);
   glVertex2i(450,300);
   glVertex2i(500,300);
   glVertex2i(500,300);
   glVertex2i(500,225);
   glVertex2i(200,360);
   glVertex2i(125,300);
   glVertex2i(125,300);
   glVertex2i(25,295);
   glVertex2i(25,295);
   glVertex2i(27,225);
   glVertex2i(27,225);
   glVertex2i(500,225);
   glVertex2i(425,250);
   glVertex2i(425,200);
   glVertex2i(425,250);
   glVertex2i(375,250);
   glVertex2i(375,250);
   glVertex2i(375,200);
   glVertex2i(375,200);
   glVertex2i(425,200);
   
  glEnd();
  
    
  glFlush();
  

}
int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100,150);
  glutCreateWindow("My first program");
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();
  return 0;
}

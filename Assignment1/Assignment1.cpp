/*
  Author : Neevan Redkar 
  Date : 2025-01-14

*/


#include <GL/glut.h>
#include <iostream>


void myInit(void){
  glClearColor(0.0,1.0,1.0,1.0);
  //glColor3f(0.0f,0.0f,0.0f);
  glPointSize(4.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,640.0,0.0,480.0);
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  /*
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
   glVertex2i(430,260);
   glVertex2i(430,190);
   glVertex2i(430,260);
   glVertex2i(370,260);
   glVertex2i(370,260);
   glVertex2i(370,190);
   glVertex2i(370,190);
   glVertex2i(430,190);
   
  glEnd();
  */
  glColor3f(0.0f,0.0f,1.0f);
  glBegin(GL_POLYGON);
   glVertex2i(200,360);
   glVertex2i(400,360);
  
   glVertex2i(450,300);
  
   glVertex2i(500,300);
   
   glVertex2i(500,225);
   glVertex2i(200,360);
   glVertex2i(125,300);
   glVertex2i(125,225);
   
   
   glVertex2i(500,225);
   glEnd();
   glColor3f(0.0f,0.0f,1.0f);
   glBegin(GL_POLYGON);
   glVertex2i(125,300);
   glVertex2i(25,295);
   glVertex2i(25,225);
   glVertex2i(125,225);
   glEnd();
  glColor3f(1.0f,0.0f,0.0f);
  glBegin(GL_POLYGON);
   glVertex2i(490,300);
   glVertex2i(500,300);
   glVertex2i(500,280);
   glVertex2i(490,280);
   glEnd();
   glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_POLYGON);
   
   glVertex2i(25,295);
   glVertex2i(25,275);
   glVertex2i(40,275);
    glVertex2i(40,295);
   
   glEnd();
  glColor3f(0.0f,0.0f,0.0f);
  glBegin(GL_POLYGON);
   glVertex2i(425,250);
   glVertex2i(425,200);
   glVertex2i(375,200);
   glVertex2i(375,250);
  glEnd();
  glBegin(GL_POLYGON);
   glVertex2i(150,250);
   glVertex2i(150,200);
   glVertex2i(100,200);
   glVertex2i(100,250);
  glEnd();
  glFlush();
  

}

int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100,150);
  glutCreateWindow("Assignment 1");
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();
  return 0;
}

/*
  Author - Neevan Redkar
  Subject - Computer Graphics
  Title - DDA

*/

#include <GL/glut.h>
#include<cmath>
#include <iostream>
using namespace std;
void myInit(void){
glClearColor(1.0,1.0,1.0,1.0);
glColor3f(0.0f,0.0f,0.0f);
glPointSize(4.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,640.0,0.0,480.0);
}
float sign(float x){
if(x<0){
return-1;
}
else if(x==0){
return 1;
}
else{
return 1;
}
}
void ddaLine(int x1, int y1, int x2, int y2) {
int dx = x2 - x1;
int dy = y2 - y1;
int length;
if(abs(dx)>abs(dy)){
length=dx;
}
else{
length=dy;
}
float DX = dx / float(length);
float DY = dy / float(length);
float x = x1;
float y = y1;
glColor3f(1.0, 0.0, 0.0);
sign(DX);
sign(DY);
glBegin(GL_POINTS);
for (int i = 0; i <= length; i++) {
glVertex2i(round(x), round(y));
x +=(DX);
y +=(DY);
}
glEnd();
glFlush();
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
ddaLine(100, 100, 500, 50);
glutSwapBuffers();
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(640, 480);
glutCreateWindow("DDA Line Drawing");
myInit();
glutDisplayFunc(display);
glutMainLoop();
return 0;
}
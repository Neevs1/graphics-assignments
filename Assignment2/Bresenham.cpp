/*
  Author - Neevan Redkar
  Subject - Computer Graphics
  Title - Bresenham

*/

#include <GL/glut.h>
#include<cmath>
#include <iostream>
using namespace std;
void myInit(void){
glClearColor(1.0,1.0,1.0,1.0);
glColor3f(0.0f,0.0f,0.0f);
glPointSize(2.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,640.0,0.0,480.0);
}
int sign(int x,int y){
if(x-y<0){
return-1;
}

return 1;

}
void BresenhamLine(int x1, int y1, int x2, int y2) {
if(x1==x2&&y1==y2){
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
    cout<<"Error - Origin and Destination are same"<<endl;
    return;

}
int x=x1,y=y1;
int dx = (x2 - x1);
int dy = (y2 - y1);
int s1 = sign(x2, x1);
int s2 = sign(y2, y1);
int interchange;
if (dy > dx) {
    int temp = dx;
    dx = dy;
    dy = temp;
    interchange = 1;
}else{
    interchange = 0;
}
int e = 2 * dy - dx;
glBegin(GL_POINTS);
glVertex2i(x, y);
glEnd();
for (int i = 0; i < dx; i++) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    while (e >= 0) {
        if (interchange == 1) {
            x = x + s1;
        } else {
            y = y + s2;
        }
        cout<<x<<" "<<y<<endl;
        e = e - 2 * dx;
    }
    if(interchange == 1){
        y = y + s2;
    }else{
        x=x+s1;
    }
    cout<<x<<" "<<y<<endl;
    e=e+ 2*dy;

}
glFlush();
}
void display() {
glClear(GL_COLOR_BUFFER_BIT);
BresenhamLine(10, 5, 10, 5);
glutSwapBuffers();
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(640, 480);
glutCreateWindow("Bresenham Line Drawing");
myInit();
glutDisplayFunc(display);
glutMainLoop();
return 0;
}
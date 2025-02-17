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

void BresenhamLine(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2i(x1, y1);
        glEnd();
        glFlush();
        //cout << "Error - Origin and Destination are same" << endl;
        return;
    }

    int x = x1, y = y1;
    int dx = abs(x2 - x1);  // Absolute value for dx
    int dy = abs(y2 - y1);  // Absolute value for dy
    int s1 = (x2 > x1) ? 1 : -1;  // Correct sign calculation for x
    int s2 = (y2 > y1) ? 1 : -1;  // Correct sign calculation for y
    int interchange = 0;

    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }

    int e = 2 * dy - dx;  // Initialize error term
    glPointSize(2.0);

    for (int i = 0; i <= dx; i++) {  // Loop runs from 0 to dx (inclusive)
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2i(x, y);
        glEnd();

        while (e >= 0) {
            if (interchange == 1) {
                x += s1;  // Move in x direction if slope > 1
            } else {
                y += s2;  // Move in y direction if slope <= 1
            }
            e -= 2 * dx;  // Update error term
        }

        if (interchange == 1) {
            y += s2;  // Move in y direction if slope > 1
        } else {
            x += s1;  // Move in x direction if slope <= 1
        }
        e += 2 * dy;  // Update error term
    }

    glFlush();
}

void plotAxes(){
    BresenhamLine(-640,0,640,0);
    BresenhamLine(0,-360,0,360);
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
#include <cmath>
#include<iostream>
#include <GL/glut.h> 

void init() 
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);      
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); 
}

void drawKochCurve(int x1, int y1, int x2, int y2, int depth) 
{
    if (depth == 0) 
    {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
        return;
    }

    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;

    float x3 = x1 + dx;
    float y3 = y1 + dy;

    float x5 = x2 - dx;
    float y5 = y2 - dy;

    float x4 = (x3 + x5) / 2 - (y5 - y3) * sqrt(3) / 2;
    float y4 = (y3 + y5) / 2 + (x5 - x3) * sqrt(3) / 2;

    drawKochCurve(x1, y1, x3, y3, depth - 1);
    drawKochCurve(x3, y3, x4, y4, depth - 1);
    drawKochCurve(x4, y4, x5, y5, depth - 1);
    drawKochCurve(x5, y5, x2, y2, depth - 1);
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(0.0, 0.0, 1.0); 
    drawKochCurve(100.0, 200.0, 400.0, 200.0, 4); 
    glFlush(); 
}


int main(int argc,char** argv) 
{
    glutInit(&argc,argv);                          
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);    
    glutInitWindowSize(640, 480);                  
    glutInitWindowPosition(100,100);               
    glutCreateWindow("Fractals");       
    init();                                         
    glutDisplayFunc(display);                       
    glutMainLoop();                                 
    return 0;
}
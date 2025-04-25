#include<iostream>
#include <GL/glut.h>
#include <math.h>

int cp[4][2]={{100,100},{150,200},{200,50},{250,100}};//controlpoints (static)

void init()//initialization finction
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0,0.0,0.0);        
    gluOrtho2D(0.0,640.0,0.0,480.0);
}

void ControlPoints()//function to plot the control points
{
    int i;
    glColor3f(0.0,0.0,1.0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    for(i=0;i<4;i++)
    {
        glVertex2f(cp[i][0],cp[i][1]);
    }
    glEnd();
}

int midpoint(int a,int b)//function to calculate midpoint
{
return (a+b)/2;
}

void Bezier1()//function to draw the bezier curve
{
    float t,x,y;
    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_LINE_STRIP);
    for ( t = 0.0; t <= 1.0; t += 0.01) {
         x = pow(1 - t, 3) * cp[0][0] +
                  3 * t * pow(1 - t, 2) * cp[1][0] +
                  3 * pow(t, 2) * (1 - t) * cp[2][0] +
                  pow(t, 3) * cp[3][0];

         y = pow(1 - t, 3) * cp[0][1] +
                  3 * t * pow(1 - t, 2) * cp[1][1] +
                  3 * pow(t, 2) * (1 - t) * cp[2][1] +
                  pow(t, 3) * cp[3][1];

        glVertex2f(x, y);
    }

    glEnd();
}

void display()//display function
{
    glClear(GL_COLOR_BUFFER_BIT);
    ControlPoints();
    Bezier1();
    glFlush();
}

int main(int argc,char** argv)//main function
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);//select display mode
    glutInitWindowSize(640,480);//declare window size
    glutInitWindowPosition(150,200);//declare window position
    glutCreateWindow("Bezier Curve");//window name
    init();//call initialization function
    glutDisplayFunc(display);//call display function
    glutMainLoop();
    return 0;
}
/*
* Author : Neevan Redkar
* Date : 2025-01-31
*/

#include <GL/glut.h>
#include <iostream>
#include <cmath>
int choice =0;
void myInit(void){
  glClearColor(1.0,1.0,1.0,1.0);
  glPointSize(5.0);
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


void bresenhamCirc(int rad,int h,int k){
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
void bresenhamSpiral(int maxRad,int h,int k, int numTurns){
    float angleStep = 0.05f; // Angle increment for smooth spiral
    float radiusStep = 0.1f; // Radius increment for each step
    float theta = 0.0f; // Initial angle
    float r = 0.0f; // Initial radius

    glBegin(GL_LINE_STRIP); // Use GL_LINE_STRIP to connect points
    while (r <= maxRad) {
        // Calculate x and y coordinates
        int x = static_cast<int>(r * cos(theta)) + h;
        int y = static_cast<int>(r * sin(theta)) + k;

        // Plot the point
        glVertex2i(x, y);

        // Increment angle and radius
        theta += angleStep;
        r += radiusStep;
    }
    glEnd();
    glFlush();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    plotAxes();
    
    switch(choice){
        case 1:
            glColor3f(0.0f,0.0f,0.0f);
            bresenhamCirc(100,-200,200);
            break;
        case 2:
            glColor3f(1.0f,0.0f,0.0f); //red circle rightmost
            bresenhamCirc(75,550,250);
            glColor3f(0.0f,0.0f,0.0f); //black circle centre
            bresenhamCirc(75,380,250);
            glColor3f(0.0f,0.5f,1.0f); //cyan circle leftmost
            bresenhamCirc(75,210,250);
            glColor3f(0.9f,0.72f,0.0f); //yellow circle bottomleft
            bresenhamCirc(75,295,175);
            glColor3f(0.0f,0.75f,0.0f); //green circle bottomright
            bresenhamCirc(75,465,175);
            break;
        case 3:
            glColor3f(0.0f,0.0f,0.0f);
            bresenhamCirc(100,-200,-200);
            bresenhamCirc(80,-200,-200);
            bresenhamCirc(60,-200,-200);
            bresenhamCirc(40,-200,-200);
            break;
        case 4:
            
            glColor3f(0.0f,0.0f,0.0f);
            glLineWidth(5.0);
            glBegin(GL_LINES);
            glVertex2f(150,-258);
            glVertex2f(310,-258);
            glVertex2f(310,-258);
            glVertex2f(230,(int)(-1*sqrt(3)*(310-150)/2)+22);
            glVertex2f(230,(int)(-1*sqrt(3)*(310-150)/2)+22);
            glVertex2f(150,-258);
            glEnd();
            bresenhamCirc(((int)((310-150)/sqrt(3))),230,(int)((-1.5*sqrt(3)*(310-150)/2)));
            bresenhamCirc(((int)((310-150)/(2*sqrt(3)))),230,(int)((-1.5*sqrt(3)*(310-150)/2)));
            
            break;
       case 5:
            glColor3f(0.0f,0.0f,0.0f);
            bresenhamSpiral(100,0,0,5);
            
            break;
    }
    
    
    glFlush();
}

void processMenuEvents(int option) {
    switch (option) {
      case 1:
        choice = 1;
        break;
      case 2:
        choice = 2;
        break;
      case 3:
        choice =3;
        break;
      case 4:
        choice=4;
        break;
      case 5:
       choice=5;
        break;
      
    }
    
}

int main(int argc, char** argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(1280,720);
  glutInitWindowPosition(100,150);
  glutCreateWindow("Bresenham Circle Drawing");
  glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("Bresenham Circle", 1);
  glutAddMenuEntry("Olympic Emblem", 2);
  glutAddMenuEntry("Concentric Circles", 3);
  glutAddMenuEntry("Pattern", 4);
  glutAddMenuEntry("Spiral", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();
  return 0;
}
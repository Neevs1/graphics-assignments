/*
 *
 * Author : Neevan Redkar
 * Title : 2D Transformations
 * Date : 24|02|2025 
 * 
 *
*/

#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

#define intx 160
#define inty 160
int mx,my;

void myInit(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(0.0f,0.0f,0.0f);
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

void translate(){
    glBegin(GL_POLYGON);
    glVertex2i(mx-50,my-50);
    glVertex2i(mx+50,my-50);
    glVertex2i(mx+50,my+50);
    glVertex2i(mx-50,my+50);
    glEnd();
    glutPostRedisplay();
}

void myMouse(int button,int state,int x,int y){
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        mx=x-640;
        my=-1*(y-360);
    }

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2i(intx-50,inty-50);
    glVertex2i(intx+50,inty-50);
    glVertex2i(intx+50,inty+50);
    glVertex2i(intx-50,inty+50);
    glEnd();
    translate();
    plotAxes();
    glFlush();
}





void processMenuEvents(){

}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(100,150);
    glutCreateWindow("2D Transform");
    glutMouseFunc(myMouse);
    /*glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Translate",1);
    glutAddMenuEntry("Rotate",2);
    glutAddMenuEntry("Scale",3);
    glutAddMenuEntry("Reflect",4);
    glutAddMenuEntry("Shear",5);
    glutAddMenuEntry("Exit",6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);*/
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
  }
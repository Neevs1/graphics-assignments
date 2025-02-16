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
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-640.0,640.0,-360.0,360.0);
}
int sign(int x,int y){
if(x-y<0){
return-1;
}

return 1;

}
void BresenhamLine(int x1, int y1, int x2, int y2) {
if(x1==x2&&y1==y2){
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    
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
glPointSize(2.0);
glBegin(GL_POINTS);
glVertex2i(x, y);
glEnd();
for (int i = 0; i < dx; i++) {
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glColor3f(0.0f,0.0f,0.0f);
    
    glVertex2i(x, y);
    glEnd();
    while (e >= 0) {
        if (interchange == 1) {
            x = x + s1;
        } else {
            y = y + s2;
        }
       // cout<<x<<" "<<y<<endl;
        e = e - 2 * dx;
    }
    if(interchange == 1){
        y = y + s2;
    }else{
        x=x+s1;
    }
    //cout<<x<<" "<<y<<endl;
    e=e+ 2*dy;

}
glFlush();
}

void dottedBresenhamLine(int x1, int y1, int x2, int y2) {
    if(x1==x2&&y1==y2){
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glColor3f(0.0f,0.0f,0.0f);
        
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
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    for (int i = 0; i < dx; i++) {
        glPointSize(2.0);
        glBegin(GL_POINTS);
        if(i%2==0){
        glColor3f(0.0f,0.0f,0.0f);
        
        glVertex2i(x, y);
        }else{
            glColor3f(1.0f,1.0f,1.0f);
            
            glVertex2i(x, y);
        }
        glEnd();
        while (e >= 0) {
            if (interchange == 1) {
                x = x + s1;
            } else {
                y = y + s2;
            }
           // cout<<x<<" "<<y<<endl;
            e = e - 2 * dx;
        }
        if(interchange == 1){
            y = y + s2;
        }else{
            x=x+s1;
        }
        //cout<<x<<" "<<y<<endl;
        e=e+ 2*dy;
    
    }
    glFlush();
    }
void dashedBresenhamLine(int x1, int y1, int x2, int y2) {
        if(x1==x2&&y1==y2){
            glPointSize(2.0);
            glBegin(GL_POINTS);
            glColor3f(0.0f,0.0f,0.0f);
           
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
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glColor3f(0.0f,0.0f,0.0f);
        
        glVertex2i(x, y);
        glEnd();
        for (int i = 0; i < dx; i++) {
            glPointSize(2.0);
            glBegin(GL_POINTS);
            if(i%10==0||i%10==1||i%10==2||i%10==3||i%10==4){
            glColor3f(0.0f,0.0f,0.0f);
            
            
            glVertex2i(x, y);
            }else if(i%10==5||i%10==6||i%10==7||i%10==8||i%10==9){
                glColor3f(1.0f,1.0f,1.0f);
                
                glVertex2i(x, y);
            }
            glEnd();
            while (e >= 0) {
                if (interchange == 1) {
                    x = x + s1;
                } else {
                    y = y + s2;
                }
               // cout<<x<<" "<<y<<endl;
                e = e - 2 * dx;
            }
            if(interchange == 1){
                y = y + s2;
            }else{
                x=x+s1;
            }
            //cout<<x<<" "<<y<<endl;
            e=e+ 2*dy;
        
        }
        glFlush();
        }
void SolidBresenhamLine(int x1, int y1, int x2, int y2) {
            if(x1==x2&&y1==y2){
               glPointSize(5.0);
                glBegin(GL_POINTS);
                glColor3f(0.0f,0.0f,0.0f);
                
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
            glPointSize(5.0);
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
            for (int i = 0; i < dx; i++) {
                glPointSize(5.0);
                glBegin(GL_POINTS);
                glColor3f(0.0f,0.0f,0.0f);
               
                glVertex2i(x, y);
                glEnd();
                while (e >= 0) {
                    if (interchange == 1) {
                        x = x + s1;
                    } else {
                        y = y + s2;
                    }
                   // cout<<x<<" "<<y<<endl;
                    e = e - 2 * dx;
                }
                if(interchange == 1){
                    y = y + s2;
                }else{
                    x=x+s1;
                }
                //cout<<x<<" "<<y<<endl;
                e=e+ 2*dy;
            
            }
            glFlush();
            }

void plotAxes(){
    BresenhamLine(-640,0,640,0);
    BresenhamLine(0,-360,0,360);
}

void display() {
glClear(GL_COLOR_BUFFER_BIT);
BresenhamLine(-100, 50, -100, 150);
dottedBresenhamLine(100, 250, 200, 250);
dashedBresenhamLine(50, 50, 250, 50);
SolidBresenhamLine(50, 150, 250, 150);
plotAxes();
glutSwapBuffers();
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(1280, 720);
glutCreateWindow("Bresenham Line Drawing");
myInit();
glutDisplayFunc(display);
glutMainLoop();
return 0;
}
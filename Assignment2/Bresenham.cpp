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

void plotAxes{
    
}

}
void BresenhamLine(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2i(x1, y1);
        glEnd();
        glFlush();
        cout << "Error - Origin and Destination are same" << endl;
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

void dottedBresenhamLine(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2i(x1, y1);
        glEnd();
        glFlush();
        cout << "Error - Origin and Destination are same" << endl;
        return;
    }

    int x = x1, y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int s1 = (x2 > x1) ? 1 : -1;
    int s2 = (y2 > y1) ? 1 : -1;
    int interchange = 0;

    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        interchange = 1;
    }

    int e = 2 * dy - dx;
    glPointSize(2.0);

    for (int i = 0; i <= dx; i++) {
        glBegin(GL_POINTS);
        if (i % 2 == 0) {
            glColor3f(0.0f, 0.0f, 0.0f);
        } else {
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        glVertex2i(x, y);
        glEnd();

        while (e >= 0) {
            if (interchange == 1) {
                x += s1;
            } else {
                y += s2;
            }
            e -= 2 * dx;
        }

        if (interchange == 1) {
            y += s2;
        } else {
            x += s1;
        }
        e += 2 * dy;
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
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
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
            if (i % 10 < 5) {
                glColor3f(0.0f, 0.0f, 0.0f);  // Black
                glVertex2i(x, y);
            } else {
                glColor3f(1.0f, 1.0f, 1.0f);  // White
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
               e -= 2 * dx; 
            }
            if(interchange == 1){
                y = y + s2;
            }else{
                x=x+s1;
            }
            //cout<<x<<" "<<y<<endl;
            e+= 2*dy;
        
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
            int dx = abs(x2 - x1);
            int dy = abs(y2 - y1);
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
dottedBresenhamLine(-200, 250, -100, 250);
dashedBresenhamLine(-250, -50, -50, -25);
SolidBresenhamLine(50, -150, 250, -150);
//pattern starts here
BresenhamLine(160,300,560,300);
BresenhamLine(160,100,560,100);
BresenhamLine(160,100,160,300);
BresenhamLine(560,100,560,300);//square outer ends here
BresenhamLine(160,200,360,300);
BresenhamLine(360,300,560,200);
BresenhamLine(160,200,360,100);
BresenhamLine(360,100,560,200);//inner diamond ends here
BresenhamLine(260,250,460,250);
BresenhamLine(260,150,460,150);
BresenhamLine(260,150,260,250);
BresenhamLine(460,150,460,250);//square inner ends here
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
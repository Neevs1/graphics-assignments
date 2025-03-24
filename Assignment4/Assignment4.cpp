#include <iostream>
#include <GL/glut.h>
using namespace std;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int mx, my;
float boundaryColor[3] = {0, 0, 0}; // Boundary color (black)
float interiorColor[3] = {1, 1, 1}; // Interior color (white)
float fillColor[3] = {1, 0, 0};     // Fill color (red)
float readpixel[3];

void getpixel(int x, int y, float *color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void setpixel(int x,int y)
{
	glColor3fv(fillColor);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();
}

void floodfill(int x,int y)
{
	getpixel(x,y,readpixel);
	if(readpixel[0]==interiorColor[0] && readpixel[1]==interiorColor[1] && readpixel[2]==interiorColor[2])
	{
		setpixel(x,y);
		floodfill(x+1,y);
		floodfill(x,y+1);
		floodfill(x-1,y);
		floodfill(x,y-1);
        
		glEnd();
		glFlush();
	}
}


void boundaryfill(int x,int y){
    
    if(x>640||x<0||y>480||y<0){
        return;
    }
    getpixel(x,y,readpixel);
    if (
    (readpixel[0] != boundaryColor[0] || readpixel[1] != boundaryColor[1] || readpixel[2] != boundaryColor[2]) &&
    (readpixel[0] != fillColor[0] || readpixel[1] != fillColor[1] || readpixel[2] != fillColor[2])
){
        setpixel(x,y);
        // cout<<"x= "<<x<<" and y = "<<y<<endl; debug statement
		boundaryfill(x+1,y);
		boundaryfill(x,y+1);
        boundaryfill(x,y-1);
		boundaryfill(x-1,y);
		
		glFlush();
    }
}

void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mx = x;
        my = 480 - y; // Convert y-coordinate to OpenGL coordinate system
        floodfill(mx, my);
    }
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'b':
         boundaryfill(x,480-y);
        case 'E':
            exit(0);
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

    for (int i = 0; i <= dx; i++) {
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
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

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the grid
    BresenhamLine(75, 50, 75, 450);
    BresenhamLine(175, 50, 175, 450);
    BresenhamLine(275, 50, 275, 450);
    BresenhamLine(375, 50, 375, 450);
    BresenhamLine(75, 50, 375, 50);
    BresenhamLine(75, 150, 375, 150);
    BresenhamLine(75, 250, 375, 250);
    BresenhamLine(75, 350, 375, 350);
    BresenhamLine(75, 450, 375, 450);

    BresenhamLine(400,200,425,200);
    BresenhamLine(400,200,400,225);
    BresenhamLine(425,200,425,225);
    BresenhamLine(400,225,425,225);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Assignment 1");
    glutDisplayFunc(display);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    myInit();
    glutMainLoop();
    return 0;
}
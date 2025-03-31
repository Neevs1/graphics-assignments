#include <iostream>
#include <GL/glut.h>
using namespace std;

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); //Set bgcolor to white
    glColor3f(0.0f, 0.0f, 0.0f); //set cursor colour to blackk
    glPointSize(1.0); //set point size to 1
    glMatrixMode(GL_PROJECTION); //set mode to projection
    glLoadIdentity(); //Load identity matrix
    gluOrtho2D(0.0, 640.0, 0.0, 480.0); //Set the drawing space
}

int mx, my,choice=0;
float boundaryColor[3] = {0, 0, 0}; // Boundary color (black)
float interiorColor[3] = {1, 1, 1}; // Interior color (white)
float fillColor[3] = {1, 0, 0};     // Fill color (red)
float fillColor2[3] = {0,0,1}; //Secondary fill colour (blue)
float readpixel[3];

void getpixel(int x, int y, float *color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color); //function to read the pixel
}

void setpixel(int x,int y) //function for setting colour of a pixel
{ 
	
	glBegin(GL_POINTS); //points mode
	glVertex2f(x,y);
	glEnd();
	glFlush();
}

void floodfill(int x,int y) //four connected floodfill
{
	getpixel(x,y,readpixel); //scans colour of specific pixel
	if(readpixel[0]==interiorColor[0] && readpixel[1]==interiorColor[1] && readpixel[2]==interiorColor[2]) //checks if pixel has same
    //colour as defined interior colour. If yes, colours selected pixel
	{
        glColor3fv(fillColor); //colours pixel red
		setpixel(x,y);
        //four connected method
		floodfill(x+1,y);
		floodfill(x,y+1);
		floodfill(x-1,y);
		floodfill(x,y-1);
        
		glEnd();
		glFlush();
	}
}


void boundaryfill(int x,int y){
    //four connected boundary fill
    if(x>640||x<0||y>480||y<0){
        return;
    }
    getpixel(x,y,readpixel);//scans pixel
    if (
    (readpixel[0] != boundaryColor[0] || readpixel[1] != boundaryColor[1] || readpixel[2] != boundaryColor[2]) &&
    (readpixel[0] != fillColor2[0] || readpixel[1] != fillColor2[1] || readpixel[2] != fillColor2[2])
    /* checks for two conditions : given pixel is not same as fill colour,and given pixel is not boundary colour
    */
){
        glColor3fv(fillColor2);
        setpixel(x,y);
        
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
        switch(choice){
            case 1:
            floodfill(mx,my); //flood fills executed if option 1 selected
            
            break;
            case 2:
            boundaryfill(mx,my);//boundary fill executed if option 2 selected
            
            break;
        }
        
    }
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) { //use key e for exiting program
        case 'e':
            exit(0);
    }
}

void BresenhamLine(int x1, int y1, int x2, int y2) { //bresenham line from previous assignment
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
    glClear(GL_COLOR_BUFFER_BIT); //sets background to white

    // Draw the star
    BresenhamLine(50, 200, 250, 200);
    BresenhamLine(75, 50, 150, 300);
    BresenhamLine(150, 300, 225, 50);
    BresenhamLine(75, 50, 250, 200);
    BresenhamLine(50, 200, 225, 50);
    
    glFlush(); 
}

void menuOptions(int option){
    //controls the menu
    switch(option){
        case 1: //sets choice to 1
        choice = option;
        break;
        case 2: //sets choice to2
        choice = option;
        break;
        case 3: //exits program
        exit(0);

    }

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);// Initializes the GLUT library and processes command line arguments
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);// Sets the display mode with single buffer, RGB color, and depth buffer
    glutInitWindowSize(640, 480);// Sets the initial window size to 640x480 pixels
    glutInitWindowPosition(100, 150);// Sets the initial window position to (100,150) on screen
    glutCreateWindow("Assignment 4");// Creates a window with the title "Assignment 4"
    glutDisplayFunc(display);// Registers the display callback function for window redraws
    glutMouseFunc(myMouse);// Registers the mouse callback function for mouse events
    glutKeyboardFunc(myKeyboard);// Registers the keyboard callback function for key presses
    glutCreateMenu(menuOptions);// Creates a popup menu with the specified callback function
    glutAddMenuEntry("Flood Fill",1);// Adds "Flood Fill" as the first menu option with ID 1
    glutAddMenuEntry("Boundary Fill",2);// Adds "Boundary Fill" as the second menu option with ID 2
    glutAddMenuEntry("Exit",3);// Adds "Exit" as the third menu option with ID 3
    glutAttachMenu(GLUT_RIGHT_BUTTON);// Attaches the menu to the right mouse button
    myInit();
    glutMainLoop();//Starts together the main infinite loop
    return 0;
}
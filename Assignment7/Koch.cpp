#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

// Global parameters
const float W = 0.3f;  // Weight factor (fractional dimension)
const float MAX_OFFSET = 0.5f; // Maximum displacement factor

void init() 
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);      
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    srand(time(0)); // Seed random number generator
}

// Returns a random value between -1 and 1
float gaussRandom() 
{
    return 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
}

// Calculate length of segment
float segmentLength(float x1, float y1, float x2, float y2) 
{
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// Recursive fractal line generation
void fractalLine(float x1, float y1, float x2, float y2, int depth) 
{
    if (depth <= 0) 
    {
        // Base case: draw straight line
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
        return;
    }

    // Calculate midpoint
    float midX = (x1 + x2) / 2.0f;
    float midY = (y1 + y2) / 2.0f;

    // Calculate segment length
    float L = segmentLength(x1, y1, x2, y2);

    // Add displacement to midpoint
    float dx = L * W * MAX_OFFSET * gaussRandom();
    float dy = L * W * MAX_OFFSET * gaussRandom();

    // Displace the midpoint
    midX += dx;
    midY += dy;

    // Recursively process the two new segments
    fractalLine(x1, y1, midX, midY, depth - 1);
    fractalLine(midX, midY, x2, y2, depth - 1);
}

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(0.0, 0.0, 1.0); // Blue color
    
    // Draw fractal line between two points with 8 recursion levels
    fractalLine(50.0, 250.0, 450.0, 250.0, 8);
    
    glFlush(); 
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);                          
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    
    glutInitWindowSize(500, 500);                  
    glutInitWindowPosition(100, 100);               
    glutCreateWindow("Fractal Line with Midpoint Displacement");       
    init();                                         
    glutDisplayFunc(display);                       
    glutMainLoop();                                 
    return 0;
}
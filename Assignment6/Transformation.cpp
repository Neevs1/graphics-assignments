/*
 *
 * Author : Neevan Redkar
 * Title : 2D Transformations
 * Date : 24|02|2025 
 * 
 *
*/

#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float vertices[100][2];
int   numVertices = 0;

void init()
{
    glClearColor(1,1,1,1);
    glPointSize(4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320,320,-240,240);
}
float scaleX = 1.0f, scaleY = 1.0f;
float rotateAngle = 0.0f;
float shearX  = 0.0f;          
float shearY  = 0.0f;          
bool  reflectX = false;
bool  reflectY = false;
float origTranslateX = -300.0f, origTranslateY = 0.0f;
void multiplyMatrix(float A[3][3], float B[3][3], float R[3][3])
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            R[i][j] = 0;
            for (int k = 0; k < 3; ++k)
                R[i][j] += A[i][k] * B[k][j];
        }
}

void applyTransformation(float M[3][3], float& x, float& y)
{
    float p[3] = { x, y, 1.0f }, r[3] = {0};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            r[i] += M[i][j] * p[j];
    x = r[0];  y = r[1];
}


void getTransformationMatrix(float F[3][3])
{
    
    float S[3][3] = {
        { scaleX, 0, 0 },
        { 0, scaleY, 0 },
        { 0, 0, 1 }
    };


    float H[3][3] = {
        { 1, shearX, 0 },
        { shearY, 1, 0 },
        { 0, 0, 1 }
    };

    
    float rad = rotateAngle * 3.14159f / 180.0f;
    float R[3][3] = {
        { cos(rad), -sin(rad), 0 },
        { sin(rad),  cos(rad), 0 },
        {    0,         0,    1 }
    };

    /* reflect */
    float Ref[3][3] = {
        { reflectY ? -1.0f : 1.0f, 0, 0 },
        { 0, reflectX ? -1.0f : 1.0f, 0 },
        { 0, 0, 1 }
    };

    
    float T1[3][3], T2[3][3], T3[3][3];
    multiplyMatrix(H,  S,   T1);   // H·S
    multiplyMatrix(R,  T1,  T2);   // R·H·S
    multiplyMatrix(Ref,T2,  T3);   // Ref·R·H·S

    
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            F[i][j] = T3[i][j];
}


void ddaLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1, dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float Xinc = dx / float(steps);
    float Yinc = dy / float(steps);
    float x = x1, y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; ++i)
    {
        glVertex2i(round(x), round(y));
        x += Xinc;
        y += Yinc;
    }
    glEnd();
}


void drawAxes()
{
    glColor3f(0,0,0);
    ddaLine(-320,0, 320,0);
    ddaLine(0,-240, 0,240);
}


void computeCentroid(float& cx, float& cy)
{
    cx = cy = 0;
    for (int i = 0; i < numVertices; ++i)
    {
        cx += vertices[i][0];
        cy += vertices[i][1];
    }
    cx /= numVertices;
    cy /= numVertices;
}


void display()   //Display Function
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    /* draw original (yellow) */
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i)
        glVertex2f(vertices[i][0] + origTranslateX,
                   vertices[i][1] + origTranslateY);
    glEnd();

    /* composite matrix */
    float M[3][3];
    getTransformationMatrix(M);

    /* centroid for origin‑centred transform */
    float cx, cy;
    computeCentroid(cx, cy);

    /* draw transformed (green) */
    glColor3f(0,0.8,0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i)
    {
        float x = vertices[i][0] - cx;
        float y = vertices[i][1] - cy;
        applyTransformation(M, x, y);
        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers();
    glFlush();
}


void menu(int option) //Menu Creation
{
    switch(option)
    {
        case 1:  // scale
            cout << "scaleX scaleY: ";
            cin >> scaleX >> scaleY;
            break;
        case 2:  // rotate
            cout << "rotation angle (deg): ";
            cin >> rotateAngle;
            break;
        case 3:  // reflect Y
            reflectY = !reflectY; break;
        case 4:  // reflect X
            reflectX = !reflectX; break;
        case 5:  // shear
            cout << "shearX shearY: ";
            cin >> shearX >> shearY;
            break;
        case 6:  // reset
            scaleX = scaleY = 1.0f;
            rotateAngle = 0.0f;
            shearX = shearY = 0.0f;
            reflectX = reflectY = false;
            break;
    }
    glutPostRedisplay();
}

void createMenu()
{
    int sub = glutCreateMenu(menu);
    glutAddMenuEntry("Scale",1);
    glutAddMenuEntry("Rotate",2);
    glutAddMenuEntry("Reflect Y-axis",3);
    glutAddMenuEntry("Reflect X-axis",4);
    glutAddMenuEntry("Shear",5);
    glutAddMenuEntry("Reset Transformations",6);

    glutCreateMenu(menu);
    glutAddSubMenu("Transformations", sub);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void inputVertices()
{
    cout << "Number of vertices: ";
    cin  >> numVertices;
    for (int i = 0; i < numVertices; ++i)
    {
        cout << "Vertex " << i+1 << " (x y): ";
        cin  >> vertices[i][0] >> vertices[i][1];
    }
}

int main(int argc, char** argv)
{
    inputVertices();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("2D Transformations with Shear");
    init();
    createMenu();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

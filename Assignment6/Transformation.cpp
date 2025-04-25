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
float translateX = 0.0f;        // New translation parameters
float translateY = 0.0f;
bool  reflectX = false;
bool  reflectY = false;
float origTranslateX = 0.0f, origTranslateY = 0.0f;

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

void getTransformationMatrix(float F[3][3], float cx, float cy)
{
    // Translation matrix to move centroid to origin
    float T1[3][3] = {
        {1, 0, -cx},
        {0, 1, -cy},
        {0, 0, 1}
    };
    
    // Scaling matrix
    float S[3][3] = {
        { scaleX, 0, 0 },
        { 0, scaleY, 0 },
        { 0, 0, 1 }
    };

    // Shearing matrix
    float H[3][3] = {
        { 1, shearX, 0 },
        { shearY, 1, 0 },
        { 0, 0, 1 }
    };

    // Rotation matrix
    float rad = rotateAngle * 3.14159f / 180.0f;
    float R[3][3] = {
        { cos(rad), -sin(rad), 0 },
        { sin(rad),  cos(rad), 0 },
        {    0,         0,    1 }
    };

    // Reflection matrix
    float Ref[3][3] = {
        { reflectY ? -1.0f : 1.0f, 0, 0 },
        { 0, reflectX ? -1.0f : 1.0f, 0 },
        { 0, 0, 1 }
    };

    // Translation matrix to move back to original position
    float T2[3][3] = {
        {1, 0, cx},
        {0, 1, cy},
        {0, 0, 1}
    };

    // Additional translation matrix (new)
    float T3[3][3] = {
        {1, 0, translateX},
        {0, 1, translateY},
        {0, 0, 1}
    };

    // Temporary matrices for multiplication
    float temp1[3][3], temp2[3][3], temp3[3][3], temp4[3][3], temp5[3][3], temp6[3][3];
    
    // Order of transformations: T1 -> S -> H -> R -> Ref -> T2 -> T3
    multiplyMatrix(S, T1, temp1);      // S·T1
    multiplyMatrix(H, temp1, temp2);   // H·S·T1
    multiplyMatrix(R, temp2, temp3);   // R·H·S·T1
    multiplyMatrix(Ref, temp3, temp4); // Ref·R·H·S·T1
    multiplyMatrix(T2, temp4, temp5);  // T2·Ref·R·H·S·T1
    multiplyMatrix(T3, temp5, temp6);  // T3·T2·Ref·R·H·S·T1 (new translation added last)
    
    // Copy final matrix to F
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            F[i][j] = temp6[i][j];
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    /* draw original untranslated shape (red) */
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i)
        glVertex2f(vertices[i][0], vertices[i][1]);
    glEnd();

    /* draw original translated shape (yellow) */
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i)
        glVertex2f(vertices[i][0] + origTranslateX,
                   vertices[i][1] + origTranslateY);
    glEnd();

    /* compute centroid of translated shape */
    float cx, cy;
    computeCentroid(cx, cy);
    cx += origTranslateX;
    cy += origTranslateY;

    /* get transformation matrix */
    float M[3][3];
    getTransformationMatrix(M, cx, cy);

    /* draw transformed shape (green) */
    glColor3f(0,0.8,0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; ++i)
    {
        float x = vertices[i][0] + origTranslateX;
        float y = vertices[i][1] + origTranslateY;
        applyTransformation(M, x, y);
        glVertex2f(x, y);
    }
    glEnd();

    glutSwapBuffers();
    glFlush();
}

void menu(int option)
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
        case 6:  // translate (new option)
            cout << "translateX translateY: ";
            cin >> translateX >> translateY;
            break;
        case 7:  // reset
            scaleX = scaleY = 1.0f;
            rotateAngle = 0.0f;
            shearX = shearY = 0.0f;
            translateX = translateY = 0.0f;
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
    glutAddMenuEntry("Translate",6);  // New menu option
    glutAddMenuEntry("Reset Transformations",7);

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
    glutCreateWindow("2D Transformations with Shear and Translate");
    init();
    createMenu();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
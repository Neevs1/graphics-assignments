/*
 *
 * Author : Neevan Redkar
 * Title : 2D Transformations
 * Date : 24|02|2025 
 * 
 *
*/

#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

struct Point {
    float x, y;
};

vector<Point> polygonPoints;
bool polygonComplete = false;
int windowWidth = 800, windowHeight = 600;

void drawPolygon() {
    if (polygonPoints.empty()) return;

    glBegin(GL_POLYGON);
    for (const auto& point : polygonPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (!polygonPoints.empty()) {
        glColor3f(1.0, 1.0, 1.0); // White color for polygon
        drawPolygon();
        
        // Draw points
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0); // Red color for points
        for (const auto& point : polygonPoints) {
            glVertex2f(point.x, point.y);
        }
        glEnd();
    }
    
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (polygonComplete) return;
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert screen coordinates to OpenGL coordinates
        Point p;
        p.x = (float)x / windowWidth * 2.0 - 1.0;
        p.y = 1.0 - (float)y / windowHeight * 2.0;
        
        polygonPoints.push_back(p);
        glutPostRedisplay();
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && polygonPoints.size() >= 3) {
        polygonComplete = true;
        cout << "Polygon complete. Select a transformation from the menu." << endl;
    }
}

void translatePolygon(float tx, float ty) {
    for (auto& point : polygonPoints) {
        point.x += tx;
        point.y += ty;
    }
}

void scalePolygon(float sx, float sy) {
    // Find centroid
    float cx = 0, cy = 0;
    for (const auto& point : polygonPoints) {
        cx += point.x;
        cy += point.y;
    }
    cx /= polygonPoints.size();
    cy /= polygonPoints.size();
    
    // Scale relative to centroid
    for (auto& point : polygonPoints) {
        point.x = cx + (point.x - cx) * sx;
        point.y = cy + (point.y - cy) * sy;
    }
}

void rotatePolygon(float angle) {
    // Convert angle to radians
    float radians = angle * M_PI / 180.0;
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);
    
    // Find centroid
    float cx = 0, cy = 0;
    for (const auto& point : polygonPoints) {
        cx += point.x;
        cy += point.y;
    }
    cx /= polygonPoints.size();
    cy /= polygonPoints.size();
    
    // Rotate around centroid
    for (auto& point : polygonPoints) {
        float x = point.x - cx;
        float y = point.y - cy;
        
        point.x = cx + (x * cosTheta - y * sinTheta);
        point.y = cy + (x * sinTheta + y * cosTheta);
    }
}

void reflectPolygon(char axis) {
    for (auto& point : polygonPoints) {
        if (axis == 'x' || axis == 'X') {
            point.y = -point.y;
        }
        else if (axis == 'y' || axis == 'Y') {
            point.x = -point.x;
        }
    }
}

void shearPolygon(float sh, char axis) {
    // Find centroid
    float cx = 0, cy = 0;
    for (const auto& point : polygonPoints) {
        cx += point.x;
        cy += point.y;
    }
    cx /= polygonPoints.size();
    cy /= polygonPoints.size();
    
    for (auto& point : polygonPoints) {
        if (axis == 'x' || axis == 'X') {
            point.x += sh * (point.y - cy);
        }
        else if (axis == 'y' || axis == 'Y') {
            point.y += sh * (point.x - cx);
        }
    }
}

void transformationMenu(int choice) {
    if (!polygonComplete || polygonPoints.empty()) {
        cout << "Please complete the polygon first." << endl;
        return;
    }
    
    switch (choice) {
        case 1: { // Translation
            float tx, ty;
            cout << "Enter translation factors (tx ty): ";
            cin >> tx >> ty;
            translatePolygon(tx, ty);
            break;
        }
        case 2: { // Scaling
            float sx, sy;
            cout << "Enter scaling factors (sx sy): ";
            cin >> sx >> sy;
            scalePolygon(sx, sy);
            break;
        }
        case 3: { // Rotation
            float angle;
            cout << "Enter rotation angle (degrees): ";
            cin >> angle;
            rotatePolygon(angle);
            break;
        }
        case 4: { // Reflection
            char axis;
            cout << "Enter axis of reflection (x/y): ";
            cin >> axis;
            reflectPolygon(axis);
            break;
        }
        case 5: { // Shearing
            float sh;
            char axis;
            cout << "Enter shearing factor and axis (factor x/y): ";
            cin >> sh >> axis;
            shearPolygon(sh, axis);
            break;
        }
        case 6: { // Reset
            polygonPoints.clear();
            polygonComplete = false;
            break;
        }
    }
    
    glutPostRedisplay();
}

void createMenu() {
    glutCreateMenu(transformationMenu);
    glutAddMenuEntry("Translation", 1);
    glutAddMenuEntry("Scaling", 2);
    glutAddMenuEntry("Rotation", 3);
    glutAddMenuEntry("Reflection", 4);
    glutAddMenuEntry("Shearing", 5);
    glutAddMenuEntry("Reset", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Polygon Transformations");
    
    init();
    createMenu();
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    
    cout << "Instructions:" << endl;
    cout << "1. Left-click to add points to the polygon" << endl;
    cout << "2. Right-click to complete the polygon" << endl;
    cout << "3. Right-click again to open the transformation menu" << endl;
    
    glutMainLoop();
    return 0;
}
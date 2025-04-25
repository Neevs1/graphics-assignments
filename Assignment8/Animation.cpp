#include <GL/glut.h>
#include <cmath>
#include <iostream>


float riverOffset = 0.0f;   // River offset for animation
float birdX = -1.0f;        // Initial position of birds
float sunX = -1.0f;
float sunY = -0.2f;  // Added vertical position for sun
float moonX = -1.0f;
float moonY = -0.4f;
bool moonRisen = false;

bool birdUp = false;       // Flag to track if the bird is flying up
float busX = 0;            // Initial position of the bus
float busY = 0;            // Initial position of the bus

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawSun() {
    if (!moonRisen) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float angle = 2.0f * 3.1416f * i / 100;
            float x = 0.1f * cos(angle);
            float y = 0.1f * sin(angle);
            glVertex2f(sunX + x, sunY + y);
        }
        glEnd();
    }
}

void drawMoon() {
    if (moonRisen) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 100; i++) {
            float angle = 2.0f * 3.1416f * i / 100;
            float x = 0.1f * cos(angle);
            float y = 0.1f * sin(angle);
            glVertex2f(moonX + x, moonY + y);
        }
        glEnd();
    }
}

void drawGround() {
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.3f);
    glColor3f(0.0f, 0.8f, 0.0f);
    glVertex2f(-1.0f, -0.3f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.75f);
    glVertex2f(1.0f, -0.75f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void drawSky() {
    if (moonRisen) {
        glColor3f(0.0f, 0.0f, 0.2f); // Dark night sky
        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.3f);
        glVertex2f(1.0f, -0.3f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f); // Stars
        for (int i = 0; i < 100; i++) {
            float x = (float)(rand() % 200 - 100) / 100.0f;
            float y = (float)(rand() % 200 - 100) / 100.0f;
            glVertex2f(x, y);
        }
        glEnd();
    } else if(sunX < 0.25f) {
        glColor3f(0.5f, 0.8f, 1.0f); // Day sky
        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.3f);
        glColor3f(1.0, 0.0, 1.0);
        glVertex2f(1.0f, -0.3f);
        glColor3f(1.0, 0.0, 1.0);
        glVertex2f(1.0f, 1.0f);
        glColor3f(0.5f, 0.8f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();
    }else if(sunX > 0.75f) {
        glColor3f(1.0, 0.0, 1.0); // Day sky
        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.3f);
        glColor3f(0.5f, 0.8f, 1.0f);
        glVertex2f(1.0f, -0.3f);
        glColor3f(0.5f, 0.8f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3f(0.5f, 0.8f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();
    }else{
        glColor3f(0.5f, 0.8f, 1.0f); // Dark night sky
        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.3f);
        glVertex2f(1.0f, -0.3f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();

    }
   
}

void drawMountains() {
    
    glBegin(GL_TRIANGLES);
    glColor3f(0.4f,0.4f,0.4f);
    glVertex2f(-1.0f, -0.3f);
    glColor3f(0.8f,0.8f,0.8f);
    glVertex2f(-0.7f, 0.3f);
    glColor3f(0.4f,0.4f,0.4f);
    glVertex2f(-0.4f, -0.3f);

    glVertex2f(-0.6f, -0.3f);
    glColor3f(0.8f,0.8f,0.8f);
    glVertex2f(-0.2f, 0.4f);
    glColor3f(0.4f,0.4f,0.4f);
    glVertex2f(0.2f, -0.3f);

    glVertex2f(0.0f, -0.3f);
    glColor3f(0.8f,0.8f,0.8f);
    glVertex2f(0.5f, 0.5f);
    glColor3f(0.4f,0.4f,0.4f);
    glVertex2f(1.0f, -0.3f);
    glEnd();
}

/*void drawRiver() {
    glColor3f(0.0f, 0.4f, 1.0f);
    glBegin(GL_POLYGON);
    for (float x = -1.0f + riverOffset; x <= 1.0f + riverOffset; x += 0.05f) {
        // Increase the height and width of the river
        float y = -0.9f + 0.2f * sin(x * 3.0f); // Wider and higher sine wave
        glVertex2f(x, y);
    }
    glEnd();
}*/

void drawBus(){
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the bus body
    glBegin(GL_QUADS);
    glVertex2f(busX-0.4f, -0.4f);
    glVertex2f(busX+0.4f, -0.4f);
    glVertex2f(busX+0.4f, -0.8f);
    glVertex2f(busX-0.4f, -0.8f);
    glEnd();
    glColor3f(0.4,0.4,0.4); // Grey color for the bus cladding
    glBegin(GL_QUADS);
    glVertex2f(busX+0.4f, -0.8f);
    glVertex2f(busX-0.4f, -0.8f);
    glVertex2f(busX-0.4f, -0.75f);
    glVertex2f(busX+0.4f, -0.75f);
    glEnd();

    
    // Windshield (front window)
    glColor3f(0.6f, 0.8f, 1.0f); // Light blue for glass
    glBegin(GL_QUADS);
    glVertex2f(busX+0.35f, -0.5f);
    glVertex2f(busX+0.25f, -0.5f);
    glVertex2f(busX+0.25f, -0.6f);
    glVertex2f(busX+0.35f, -0.6f);
    glEnd();

    // Side windows (3 windows)
    glColor3f(0.6f, 0.8f, 1.0f); // Light blue for glass
    // Window 1
    glBegin(GL_QUADS);
    glVertex2f(busX+0.15f, -0.5f);
    glVertex2f(busX+0.05f, -0.5f);
    glVertex2f(busX+0.05f, -0.6f);
    glVertex2f(busX+0.15f, -0.6f);
    glEnd();
    // Window 2
    glBegin(GL_QUADS);
    glVertex2f(busX-0.05f, -0.5f);
    glVertex2f(busX-0.15f, -0.5f);
    glVertex2f(busX-0.15f, -0.6f);
    glVertex2f(busX-0.05f, -0.6f);
    glEnd();
    // Window 3
    glBegin(GL_QUADS);
    glVertex2f(busX-0.25f, -0.5f);
    glVertex2f(busX-0.35f, -0.5f);
    glVertex2f(busX-0.35f, -0.6f);
    glVertex2f(busX-0.25f, -0.6f);
    glEnd();

    // Window frames (black borders)
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    // Windshield frame
    glBegin(GL_LINE_LOOP);
    glVertex2f(busX+0.35f, -0.5f);
    glVertex2f(busX+0.25f, -0.5f);
    glVertex2f(busX+0.25f, -0.6f);
    glVertex2f(busX+0.35f, -0.6f);
    glEnd();
    // Window 1 frame
    glBegin(GL_LINE_LOOP);
    glVertex2f(busX+0.15f, -0.5f);
    glVertex2f(busX+0.05f, -0.5f);
    glVertex2f(busX+0.05f, -0.6f);
    glVertex2f(busX+0.15f, -0.6f);
    glEnd();
    // Window 2 frame
    glBegin(GL_LINE_LOOP);
    glVertex2f(busX-0.05f, -0.5f);
    glVertex2f(busX-0.15f, -0.5f);
    glVertex2f(busX-0.15f, -0.6f);
    glVertex2f(busX-0.05f, -0.6f);
    glEnd();
    // Window 3 frame
    glBegin(GL_LINE_LOOP);
    glVertex2f(busX-0.25f, -0.5f);
    glVertex2f(busX-0.35f, -0.5f);
    glVertex2f(busX-0.35f, -0.6f);
    glVertex2f(busX-0.25f, -0.6f);
    glEnd();
    glLineWidth(1.0f);

    // Bus door (right side)
glColor3f(0.8f, 0.8f, 0.8f); // Light gray for door
glBegin(GL_QUADS);
glVertex2f(busX+0.2f, -0.75f);
glVertex2f(busX+0.1f, -0.75f);
glVertex2f(busX+0.1f, -0.55f);
glVertex2f(busX+0.2f, -0.55f);
glEnd();

// Door frame
glColor3f(0.0f, 0.0f, 0.0f); // Black for frame
glLineWidth(2.0f);
glBegin(GL_LINE_LOOP);
glVertex2f(busX+0.2f, -0.75f);
glVertex2f(busX+0.1f, -0.75f);
glVertex2f(busX+0.1f, -0.55f);
glVertex2f(busX+0.2f, -0.55f);
glEnd();

// Door window
if(!moonRisen) {
    glColor3f(0.6f, 0.8f, 1.0f); // Light blue glass
} else {
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray glass for night mode
}

glBegin(GL_QUADS);
glVertex2f(busX+0.19f, -0.65f);
glVertex2f(busX+0.11f, -0.65f);
glVertex2f(busX+0.11f, -0.57f);
glVertex2f(busX+0.19f, -0.57f);
glEnd();

// Door handle
glColor3f(0.3f, 0.3f, 0.3f); // Dark gray handle
glLineWidth(3.0f);
glBegin(GL_LINES);
glVertex2f(busX+0.15f, -0.7f);
glVertex2f(busX+0.18f, -0.7f);
glEnd();
glLineWidth(1.0f);

       // Wheel rotation animation
       static float wheelAngle = 0.0f;
       wheelAngle += 5.0f; // Rotation speed
   
       // Draw wheels (approximated as 20-sided polygons)
       const int segments = 20;
       const float radius = 0.08f;
       const float hubRadius = 0.04f;
   
       // Front wheel
       glPushMatrix();
       glTranslatef(busX+0.275f, -0.775f, 0.0f);
       glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
       
       // Tire
       glColor3f(0.2f, 0.2f, 0.2f);
       glBegin(GL_POLYGON);
       for(int i = 0; i < segments; i++) {
           float angle = 2.0f * 3.14159f * i / segments;
           glVertex2f(radius * cos(angle), radius * sin(angle));
       }
       glEnd();
       
       // Hubcap
       glColor3f(0.5f, 0.5f, 0.5f);
       glBegin(GL_POLYGON);
       for(int i = 0; i < segments; i++) {
           float angle = 2.0f * 3.14159f * i / segments;
           glVertex2f(hubRadius * cos(angle), hubRadius * sin(angle));
       }
       glEnd();
       
       glPopMatrix();
   
       // Rear wheel
       glPushMatrix();
       glTranslatef(busX-0.25f, -0.775f, 0.0f);
       glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
       
       // Tire
       glColor3f(0.2f, 0.2f, 0.2f);
       glBegin(GL_POLYGON);
       for(int i = 0; i < segments; i++) {
           float angle = 2.0f * 3.14159f * i / segments;
           glVertex2f(radius * cos(angle), radius * sin(angle));
       }
       glEnd();
       
       // Hubcap
       glColor3f(0.5f, 0.5f, 0.5f);
       glBegin(GL_POLYGON);
       for(int i = 0; i < segments; i++) {
           float angle = 2.0f * 3.14159f * i / segments;
           glVertex2f(hubRadius * cos(angle), hubRadius * sin(angle));
       }
       glEnd();
       
       glPopMatrix();
}

void drawTree(float x) {
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.02f, -0.3f);
    glVertex2f(x + 0.02f, -0.3f);
    glVertex2f(x + 0.02f, -0.15f);
    glVertex2f(x - 0.02f, -0.15f);
    glEnd();

    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.07f, -0.15f);
    glVertex2f(x + 0.07f, -0.15f);
    glVertex2f(x, -0.05f);
    glEnd();
}

void drawHouse(float centerX, float centerY, float width, float height) {
    // Calculate dimensions based on parameters
    float halfWidth = width / 2.0f;
    float roofHeight = height * 0.4f;
    float doorWidth = width * 0.3f;
    float doorHeight = height * 0.5f;    
    // Main house body (rectangle)
    glColor3f(1.0f, 0.5f, 0.0f); // Orange color
    glBegin(GL_POLYGON);
    glVertex2f(centerX - halfWidth, centerY);
    glVertex2f(centerX + halfWidth, centerY);
    glVertex2f(centerX + halfWidth, centerY + height);
    glVertex2f(centerX - halfWidth, centerY + height);
    glEnd();

    // Door (centered on the house)
    glColor3f(0.4f, 0.2f, 0.0f); // Brown color
    glBegin(GL_POLYGON);
    glVertex2f(centerX - doorWidth/2, centerY);
    glVertex2f(centerX + doorWidth/2, centerY);
    glVertex2f(centerX + doorWidth/2, centerY + doorHeight);
    glVertex2f(centerX - doorWidth/2, centerY + doorHeight);
    glEnd();

    // Roof (triangle)
    glColor3f(0.8f, 0.0f, 0.0f); // Red color
    glBegin(GL_TRIANGLES);
    glVertex2f(centerX - halfWidth - 0.02f, centerY + height); // Slightly wider base
    glVertex2f(centerX + halfWidth + 0.02f, centerY + height);
    glVertex2f(centerX, centerY + height + roofHeight); // Roof peak
    glEnd();
}


void drawBirds() {
    if (!moonRisen) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        for (int i = 0; i < 5; ++i) {
            float bx = birdX + i * 0.2f;
            float by = 0.7f + 0.05f * (i % 2);
            if(birdUp){
                glVertex2f(bx - 0.02f,  by - 0.02f);
                glVertex2f(bx,by);
                glVertex2f(bx, by);
                glVertex2f(bx + 0.02f, by - 0.02f);
            }else{
            glVertex2f(bx - 0.02f, by);
            glVertex2f(bx, by - 0.02f);
            glVertex2f(bx, by - 0.02f);
            glVertex2f(bx + 0.02f, by);
            }
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky();
    drawMountains();
    drawGround();
    //drawRiver();
    drawSun();
    drawMoon();
    drawHouse(-0.7f, -0.7f, 0.2f, 0.2f); // Small house on left
    drawHouse(0.0f, -0.4f, 0.3f, 0.3f);  // Medium house in center
    drawHouse(0.7f, -0.4f, 0.4f, 0.4f);  // Large house on right
    drawBus();
    drawTree(-0.8f);
    drawTree(-0.6f);
    drawTree(-0.4f);
    drawTree(0.3f);
    drawTree(1.0f);
    drawBirds();
    glFlush();
}

void update(int value) {
    if (!moonRisen) {
        sunX += 0.01f;
        // Parabolic trajectory for sun (lower at sides, higher in middle)
        sunY = -0.2f + 0.8f * (1.0f - pow((sunX + 1.0f)/2.0f - 0.5f, 2));
        
        if (sunX > 1.2f) {
            sunX = -1.2f;
            sunY = -0.2f;
            moonRisen = true;
        }
        
        // Bus movement (unchanged)
        if(busX > 0.35 && busX < 0.45f) { busX += 0.005f; }
        else { busX += 0.04f; }
        if(busX > 1.2f) busX = -1.2f;
    }

    if (moonRisen) {
        moonX += 0.01f;
        // Parabolic trajectory for moon (opposite of sun)
        moonY = -0.2f + 0.8f * (1.0f - pow((moonX + 1.0f)/2.0f - 0.5f, 2));
        
        if (moonX > 1.2f) {
            moonX = -1.2f;
            moonY = -0.4f;
            moonRisen = false;
        }
    }

    // Rest of the update function remains the same...
    riverOffset += 0.002f;
    if (riverOffset > 2.0f) riverOffset = 0.0f;

    birdX += 0.03f;
    if (birdX > 1.2f) birdX = -1.2f;
    if((int)(100*birdX) % 2 == 0){
        birdUp = !birdUp;
    }else{
        birdUp = !birdUp;
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animation Assignment");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
#include "ShapeDrawer.h"
#include <GL/freeglut.h>
#include <iostream> 

void ShapeDrawer::drawCube(float size) {
    
    glutSolidCube(size);
}
void ShapeDrawer::drawWireCube(float size) {

    glutWireCube(size);
}

void ShapeDrawer::drawSphere(float radius, int slices, int stacks) {
    
    glutSolidSphere(radius, slices, stacks);
}

void ShapeDrawer::drawTeapot(float size) {
    glutSolidTeapot(size);
}

void ShapeDrawer::drawTorus(float innerRadius, float outerRadius, int sides, int rings) {
    glutSolidTorus(innerRadius, outerRadius, sides, rings);
}

void ShapeDrawer::drawCone(float base, float height, int slices, int stacks) {
    glutSolidCone(base, height, slices, stacks);
}
void ShapeDrawer::drawTriangle(float size) {
    //glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
    //   // Top face (y = 1.0f)
    //   // Define vertices in counter-clockwise (CCW) order with normal pointing out
    //glColor3f(0.0f, 1.0f, 0.0f);     // Green
    //glVertex3f(1.0f, 1.0f, -1.0f);
    //glVertex3f(-1.0f, 1.0f, -1.0f);
    //glVertex3f(-1.0f, 1.0f, 1.0f);
    //glVertex3f(1.0f, 1.0f, 1.0f);

    //// Bottom face (y = -1.0f)
    //glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    //glVertex3f(1.0f, -1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //glVertex3f(1.0f, -1.0f, -1.0f);

    //// Front face  (z = 1.0f)
    //glColor3f(1.0f, 0.0f, 0.0f);     // Red
    //glVertex3f(1.0f, 1.0f, 1.0f);
    //glVertex3f(-1.0f, 1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);
    //glVertex3f(1.0f, -1.0f, 1.0f);

    //// Back face (z = -1.0f)
    //glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    //glVertex3f(1.0f, -1.0f, -1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //glVertex3f(-1.0f, 1.0f, -1.0f);
    //glVertex3f(1.0f, 1.0f, -1.0f);

    //// Left face (x = -1.0f)
    //glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    //glVertex3f(-1.0f, 1.0f, 1.0f);
    //glVertex3f(-1.0f, 1.0f, -1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);

    //// Right face (x = 1.0f)
    //glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    //glVertex3f(1.0f, 1.0f, -1.0f);
    //glVertex3f(1.0f, 1.0f, 1.0f);
    //glVertex3f(1.0f, -1.0f, 1.0f);
    //glVertex3f(1.0f, -1.0f, -1.0f);
    //glEnd();  // End of drawi

    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    
    glVertex3f(1.0f, -1.0f, 1.0f);
   
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    
    glVertex3f(1.0f, -1.0f, -1.0f);
    
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left
    glColor3f(1.0f, 0.0f, 0.0f);       // Red
    glVertex3f(0.0f, 1.0f, 0.0f);
    
    glVertex3f(-1.0f, -1.0f, -1.0f);
   
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();   // Done drawing the pyramid
}



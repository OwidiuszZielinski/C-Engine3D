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



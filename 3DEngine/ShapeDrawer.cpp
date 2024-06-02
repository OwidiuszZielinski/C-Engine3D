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
    // Begin drawing the pyramid with 4 triangles
    glBegin(GL_TRIANGLES);

    // Front face
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);

    // Right face
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(size, -size, size);
    glVertex3f(0.0f, -size, -size);

    // Back face
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(0.0f, -size, -size);
    glVertex3f(-size, -size, size);

    // Base (triangle)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(0.0f, -size, -size);

    glEnd();   // Done drawing the pyramid

    // Begin drawing the edges of the pyramid
    glBegin(GL_LINES);

    glColor3f(1.0f, 1.0f, 1.0f);     // White for edges
    // Front edge
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, size);

    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(size, -size, size);

    // Right edge
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(0.0f, -size, -size);

    // Left edge
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, size);

    // Base edges
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);

    glVertex3f(size, -size, size);
    glVertex3f(0.0f, -size, -size);

    glVertex3f(0.0f, -size, -size);
    glVertex3f(-size, -size, size);

    glEnd(); // Done drawing the edges
}


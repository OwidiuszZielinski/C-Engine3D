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
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Wierzcho³ek 1: czerwony
    glVertex3f(-1.0, -1.0, 0.0);

    glColor3f(0.0, 1.0, 0.0); // Wierzcho³ek 2: zielony
    glVertex3f(1.0, -1.0, 0.0);

    glColor3f(0.0, 0.0, 1.0); // Wierzcho³ek 3: niebieski
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
}



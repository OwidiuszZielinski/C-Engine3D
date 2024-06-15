#include "ShapeDrawer.h"
#include <GL/freeglut.h>
#include <iostream> 

/**
 * @brief Rysuje pelny szescian o podanym rozmiarze.
 *
 * @param size Rozmiar szescianu.
 */
void ShapeDrawer::drawCube(float size) {
    glutSolidCube(size);
}

/**
 * @brief Rysuje szescian druciany o podanym rozmiarze.
 *
 * @param size Rozmiar szescianu.
 */
void ShapeDrawer::drawWireCube(float size) {
    glutWireCube(size);
}

/**
 * @brief Rysuje pelna kule o podanych parametrach.
 *
 * @param radius Promien kuli.
 * @param slices Liczba podzialow wokol osi Z (podobne do linii dlugosci geograficznej).
 * @param stacks Liczba podzialow wzdluz osi Z (podobne do linii szerokosci geograficznej).
 */
void ShapeDrawer::drawSphere(float radius, int slices, int stacks) {
    glutSolidSphere(radius, slices, stacks);
}

/**
 * @brief Rysuje pelny czajnik o podanym rozmiarze.
 *
 * @param size Rozmiar czajnika.
 */
void ShapeDrawer::drawTeapot(float size) {
    glutSolidTeapot(size);
}

/**
 * @brief Rysuje pelny torus o podanych parametrach.
 *
 * @param innerRadius Wewnetrzny promien torusa.
 * @param outerRadius Zewnetrzny promien torusa.
 * @param sides Liczba bokow dla kazdej sekcji promieniowej.
 * @param rings Liczba promieniowych podzialow torusa.
 */
void ShapeDrawer::drawTorus(float innerRadius, float outerRadius, int sides, int rings) {
    glutSolidTorus(innerRadius, outerRadius, sides, rings);
}

/**
 * @brief Rysuje pelny stozek o podanych parametrach.
 *
 * @param base Promien podstawy stozka.
 * @param height Wysokosc stozka.
 * @param slices Liczba podzialow wokol podstawy.
 * @param stacks Liczba podzialow wzdluz wysokosci.
 */
void ShapeDrawer::drawCone(float base, float height, int slices, int stacks) {
    glutSolidCone(base, height, slices, stacks);
}
/**
 * @brief Rysuje trójk¹t podanych parametrach.
 *
 * @param size Rozmiar trójk¹ta.
 */

void ShapeDrawer::drawTriangle(float size) {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);    
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);

    glColor3f(0.0f, 1.0f, 0.0f);    
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(size, -size, size);
    glVertex3f(0.0f, -size, -size);

    glColor3f(0.0f, 0.0f, 1.0f);    
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(0.0f, -size, -size);
    glVertex3f(-size, -size, size);

    glColor3f(1.0f, 1.0f, 0.0f);     
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(0.0f, -size, -size);
    glEnd();  
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);  
    
    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, size);

    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(size, -size, size);

    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(0.0f, -size, -size);

    glVertex3f(0.0f, size, 0.0f);
    glVertex3f(-size, -size, size);

    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);

    glVertex3f(size, -size, size);
    glVertex3f(0.0f, -size, -size);

    glVertex3f(0.0f, -size, -size);
    glVertex3f(-size, -size, size);

    glEnd(); 
}


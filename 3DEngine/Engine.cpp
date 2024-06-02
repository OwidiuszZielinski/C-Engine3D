#include "Engine.h"
#include "ShapeDrawer.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

Engine* Engine::instance = nullptr;

Engine::Engine(int argc, char** argv) {
    glutInit(&argc, argv);
    instance = this;
    running = true;
    fps = 60;
    size = 1.0f;
    radius = 0.5f;
    innerRadius = 0.2f;
    height = 1.0f;
    currentShape = ' ';
    rotationX = 0.0f;
    rotationY = 0.0f;
    rotationSpeedX = 0.1f;  // Pocz¹tkowa prêdkoœæ obrotu
    rotationSpeedY = 0.1f;  // Pocz¹tkowa prêdkoœæ obrotu
    lastShape = '\0';
    clickX = 0.0f;
    clickY = 0.0f;
    objectPosX = 0.0f;
    objectPosY = 0.0f;
    objectPosZ = 0.0f;
    drawOnClick = false;
    animate = false;  // Pocz¹tkowo animacja wy³¹czona
    shadingIntensity = 0.0f;
    std::srand(std::time(0)); // Seed the random number generator
}

Engine::~Engine() {
    close();
}

void Engine::initWindow(int width, int height, const char* title, bool fullscreen) {
    if (fullscreen) {
        glutGameModeString("1440x900:32@60");
        glutEnterGameMode();
    }
    else {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow(title);
    }

    glutDisplayFunc(displayCallback);
    glutIdleFunc(idleCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyCallback);
    glutMouseFunc(mouseCallback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0); // Ensure the near and far planes are set correctly
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initialize the camera position
    camera.setPosition(0.0f, 0.0f, 5.0f);
    camera.setTarget(0.0f, 0.0f, 0.0f); // Make sure the target is correct
}

void Engine::setGraphicsMode(int fps, bool enableMouse, bool enableKeyboard, bool doubleBuffer, bool zBuffer) {
    this->fps = fps;
    if (doubleBuffer) {
        glutInitDisplayMode(GLUT_DOUBLE);
    }
    if (zBuffer) {
        glEnable(GL_DEPTH_TEST);
    }
}

void Engine::run() {
    glutTimerFunc(1000 / fps, timerCallback, 0);  // Ustawienie pierwszego timera
    glutMainLoop();
}

void Engine::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
    glClearColor(r, g, b, a);
}

void Engine::changeProjection(int projectionType) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projectionType == 0) { // Orthographic
        gluOrtho2D(0, 1, 0, 1);
    }
    else if (projectionType == 1) { // Perspective
        gluPerspective(45.0, 1.0, 1.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

void Engine::close() {
    if (glutGetWindow()) {
        glutDestroyWindow(glutGetWindow());
    }
}

void Engine::displayCallback() {
    instance->drawScene();
}

void Engine::idleCallback() {
    instance->animateObject();
    glutPostRedisplay();
}



void Engine::keyboardCallback(unsigned char key, int x, int y) {
    if (key == 27) { // Escape key
        instance->running = false;
        instance->close();
        exit(0);
    }
    instance->currentShape = key; // ustawienie aktualnego kszta³tu

    switch (key) {
    case 'b':
    case 'B':
        instance->changeBackgroundColor();
        break;
    case 8: // Backspace key
        instance->setClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Ustawienie koloru t³a na czarny
        break;
    case 'a':
        
        instance->animate = !instance->animate;
        
        break;
    case '+':
        instance->rotationSpeedX += 0.1f;
        instance->rotationSpeedY += 0.1f;
        break;
    case '-':
        instance->rotationSpeedX -= 0.1f;
        instance->rotationSpeedY -= 0.1f;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void Engine::specialKeyCallback(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1:
        instance->changeCameraPosition(0.0f, 1.0f, 0.0f);
        break;
    case GLUT_KEY_F2: // Move camera down
        instance->changeCameraPosition(0.0f, -1.0f, 0.0f);
        break;
    case GLUT_KEY_F3: // Move camera left
        instance->changeCameraPosition(-1.0f, 0.0f, 0.0f);
        break;
    case GLUT_KEY_F4:// Move camera right
        instance->changeCameraPosition(1.0f, 0.0f, 0.0f);
        break;
    case GLUT_KEY_F5: // Move camera forward
        instance->changeCameraPosition(0.0f, 0.0f, -1.0f);
        break;
    case GLUT_KEY_F6: // Move camera backward
        instance->changeCameraPosition(0.0f, 0.0f, 1.1f);
        break;
    case GLUT_KEY_LEFT:
        instance->rotationY -= 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        instance->rotationY += 5.0f;
        break;
    case GLUT_KEY_UP:
        instance->rotationX -= 5.0f;
        break;
    case GLUT_KEY_DOWN:
        instance->rotationX += 5.0f;
        break;
    case GLUT_KEY_F7:
        instance->size += 0.1f;
        instance->height += 0.1f;
        instance->innerRadius += 0.1f;
        instance->radius += 0.1f;
        std::cout << "Zwiêkszono rozmiar: size=" << instance->size << ", height=" << instance->height << ", innerRadius=" << instance->innerRadius << ", radius=" << instance->radius << std::endl;
        break;
    case GLUT_KEY_F8:
        instance->size -= 0.1f;
        instance->height -= 0.1f;
        instance->innerRadius -= 0.1f;
        instance->radius -= 0.1f;
        std::cout << "Zmniejszono rozmiar: size=" << instance->size << ", height=" << instance->height << ", innerRadius=" << instance->innerRadius << ", radius=" << instance->radius << std::endl;
        break;
    }
}

void Engine::mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        instance->clickX = x;
        instance->clickY = y;
        instance->updateObjectPosition(instance->clickX, instance->clickY);
        glutPostRedisplay(); // Zaktualizuj ekran po klikniêciu
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        instance->toggleLighting();
        glutPostRedisplay(); // Zaktualizuj ekran po wy³¹czeniu/w³¹czeniu oœwietlenia
    }
    else if ((button == 3 || button == 4) && state == GLUT_DOWN) { // Rolka w górê (3) lub w dó³ (4)
        if (button == 3) {
            glShadeModel(GL_SMOOTH);
            std::cout << "Zmiana cieniowania na: GL_SMOOTH" << std::endl;
        }
        else if (button == 4) {
            glShadeModel(GL_FLAT);
            std::cout << "Zmiana cieniowania na: GL_FLAT" << std::endl;
        }
        glutPostRedisplay(); // Zaktualizuj ekran po zmianie intensywnoœci cieniowania
    }

}

void Engine::toggleLighting() {
    static bool lightingEnabled = true;
    if (lightingEnabled) {
        glDisable(GL_LIGHTING); // Wy³¹cz oœwietlenie
    }
    else {
        glEnable(GL_LIGHTING); // W³¹cz oœwietlenie
    }
    lightingEnabled = !lightingEnabled; // Prze³¹cz stan oœwietlenia
}


void Engine::updateObjectPosition(int x, int y) {
    
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    winX = (float)x;
    winY = (float)viewport[3] - (float)y; // Przekszta³cenie wspó³rzêdnych okna
    glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    if (winZ == 1.0f) winZ = 0.999f;
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

    instance->objectPosX = posX;
    instance->objectPosY = posY;
    instance->objectPosZ = posZ;
    std::cout << "Kliknieto w: (" << x << ", " << y << "), wspolrzedne swiata: (" << instance->objectPosX << ", " << instance->objectPosY << ", " << instance->objectPosZ << ")" << std::endl;
}
void Engine::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply the camera transformation
    camera.apply();

    // Set the light position
    GLfloat lightPos[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);



    // Draw the selected shape
    drawShape();

    glutSwapBuffers();
}

void Engine::drawShape() {
    glColor3f(1.0f, 0.0f, 0.0f); // Ustawienie koloru na czerwony
    glPushMatrix();
    glTranslatef(objectPosX, objectPosY, objectPosZ); // Ustawienie pozycji obiektu
    glRotatef(rotationX, 1.0, 0.0, 0.0); // Obrót wzd³u¿ osi X
    glRotatef(rotationY, 0.0, 1.0, 0.0); // Obrót wzd³u¿ osi Y

    if (currentShape != lastShape) {
        // Aktualizacja zmiennej lastShape
        lastShape = currentShape;
        // Wyœwietlenie komunikatu tylko raz, gdy kszta³t siê zmienia
        switch (currentShape) {
        case 'c':
        case 'C':
            std::cout << "Rysujemy kostke o rozmiarze " << size << std::endl;
            break;
        case 'w':
        case 'W':
            std::cout << "Rysujemy pusta kostke o rozmiarze " << size << std::endl;
            break;
        case 's':
        case 'S':
            std::cout << "Rysujemy kulê o promieniu : " << radius << std::endl;
            break;
        case 't':
        case 'T':
            std::cout << "Rysujemy czajnik o rozmiarze " << radius << std::endl;
            break;
        case 'o':
        case 'O':
            std::cout << "Rysujemy donata o zewnetrznym promieniu " << radius << std::endl;
            break;
        case 'n':
        case 'N':
            std::cout << "Rysujemy stozek o wysokoœci " << height << std::endl;
            break;
        case 'p':
        case 'P':
            std::cout << "Rysujemy trojkat w boku " << size << std::endl;
            break;
        default:
            break;
        }
    }

    switch (currentShape) {
    case 'c':
    case 'C':
        ShapeDrawer::drawCube(size);
        break;
    case 'w':
    case 'W':
        ShapeDrawer::drawWireCube(size);
        break;
    case 's':
    case 'S':
        ShapeDrawer::drawSphere(radius, 20, 20);
        break;
    case 't':
    case 'T':
        ShapeDrawer::drawTeapot(radius);
        break;
    case 'o':
    case 'O':
        ShapeDrawer::drawTorus(innerRadius, radius, 20, 20);
        break;
    case 'n':
    case 'N':
        ShapeDrawer::drawCone(size, height, 20, 20);
        break;
    case 'p':
    case 'P':
        ShapeDrawer::drawTriangle(size);
        break;
    default:
        break;
    }
    glPopMatrix();
}

void Engine::animateObject() {
    if (animate) {
        rotationX += rotationSpeedX;
        rotationY += rotationSpeedY;
        if (rotationX > 360.0f) rotationX -= 360.0f;
        if (rotationY > 360.0f) rotationY -= 360.0f;
        glutPostRedisplay();  // Aktualizacja ekranu
        glPopMatrix();
    }
}

void Engine::timerCallback(int value) {
    if (instance->running) {
        instance->animateObject();
        glutPostRedisplay();
        glutTimerFunc(1000 / instance->fps, timerCallback, value);
    }
}

void Engine::changeBackgroundColor() {
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    setClearColor(r, g, b, 1.0f);
    std::cout << "Zmieniono kolor tla na: (" << r << ", " << g << ", " << b << ")" << std::endl;
}

void Engine::changeCameraPosition(float dx, float dy, float dz) {
    // Update the camera position incrementally
    camera.move(dx, dy, dz);
}

int main(int argc, char** argv) {
    Engine engine(argc, argv);
    engine.initWindow(1440, 900, "Game Engine", false);
    engine.setGraphicsMode(60, true, true, true, true);
    engine.run();
    return 0;
}

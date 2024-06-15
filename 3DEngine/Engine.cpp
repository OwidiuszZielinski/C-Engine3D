
#include "Engine.h"
#include "ShapeDrawer.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Inicjalizacja wskaznika do instancji klasy Engine.
 */
    Engine* Engine::instance = nullptr;

/**
 * @brief Konstruktor klasy Engine.
 *
 * @param argc Liczba argumentow przekazywanych do aplikacji.
 * @param argv Tablica argumentow przekazywanych do aplikacji.
 */
Engine::Engine(int argc, char** argv) {
    glutInit(&argc, argv);            // Inicjalizacja GLUT
    instance = this;                  // Ustawienie wskaznika instancji na biezacy obiekt
    running = true;                   // Ustawienie flagi uruchomienia na true
    fps = 60;                         // Ustawienie liczby klatek na sekunde
    size = 1.0f;                      // Ustawienie domyslnego rozmiaru obiektu
    radius = 0.5f;                    // Ustawienie domyslnego promienia obiektu
    innerRadius = 0.2f;               // Ustawienie domyslnego wewnetrznego promienia obiektu
    height = 1.0f;                    // Ustawienie domyslnej wysokosci obiektu
    currentShape = ' ';               // Ustawienie domyslnego biezacego ksztaltu
    rotationX = 0.0f;                 // Ustawienie poczatkowej wartosci obrotu w osi X
    rotationY = 0.0f;                 // Ustawienie poczatkowej wartosci obrotu w osi Y
    rotationSpeedX = 0.1f;            // Poczatkowa predkosc obrotu w osi X
    rotationSpeedY = 0.1f;            // Poczatkowa predkosc obrotu w osi Y
    lastShape = '\0';                 // Inicjalizacja ostatniego ksztaltu
    clickX = 0.0f;                    // Inicjalizacja pozycji klikniecia w osi X
    clickY = 0.0f;                    // Inicjalizacja pozycji klikniecia w osi Y
    objectPosX = 0.0f;                // Inicjalizacja pozycji obiektu w osi X
    objectPosY = 0.0f;                // Inicjalizacja pozycji obiektu w osi Y
    objectPosZ = 0.0f;                // Inicjalizacja pozycji obiektu w osi Z
    drawOnClick = false;              // Inicjalizacja flagi rysowania po kliknieciu
    animate = false;                  // Poczatkowo animacja wylaczona
    shadingIntensity = 0.0f;          // Inicjalizacja intensywnosci cieniowania
    std::srand(std::time(0));         // Ustawienie seeda dla generatora liczb losowych
}

/**
 * @brief Destruktor klasy Engine.
 */
Engine::~Engine() {
    close();
}

/**
 * @brief Inicjalizacja okna.
 *
 * @param width Szerokosc okna.
 * @param height Wysokosc okna.
 * @param title Tytul okna.
 * @param fullscreen Czy okno ma byc w trybie pelnoekranowym.
 */
void Engine::initWindow(int width, int height, const char* title, bool fullscreen) {
    if (fullscreen) {
        glutEnterGameMode();
    }
    else {
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutCreateWindow(title);
    }

    // Ustawienie funkcji callback
    glutDisplayFunc(displayCallback);
    glutIdleFunc(idleCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(specialKeyCallback);
    glutMouseFunc(mouseCallback);

    // Wlaczenie testu glebokosci i oswietlenia
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Ustawienie perspektywy
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0); // Ustawienie plaszczyzny bliskiej i dalekiej
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicjalizacja pozycji kamery
    camera.setPosition(0.0f, 0.0f, 5.0f);
    camera.setTarget(0.0f, 0.0f, 0.0f); // Ustawienie celu kamery

    // Inicjalizacja timera
    glutTimerFunc(1000 / fps, timerCallback, 0);
}

/**
 * @brief Ustawienie trybu graficznego.
 *
 * @param fps Liczba klatek na sekunde.
 * @param enableMouse Czy myszka ma byc wlaczona.
 * @param enableKeyboard Czy klawiatura ma byc wlaczona.
 * @param doubleBuffer Czy podwojne buforowanie ma byc wlaczone.
 * @param zBuffer Czy bufor Z ma byc wlaczony.
 */
void Engine::setGraphicsMode(int fps, bool enableMouse, bool enableKeyboard, bool doubleBuffer, bool zBuffer) {
    this->fps = fps;
    if (doubleBuffer) {
        glutInitDisplayMode(GLUT_DOUBLE);
    }
    if (zBuffer) {
        glEnable(GL_DEPTH_TEST);
    }
}

/**
 * @brief Uruchomienie glownej petli aplikacji.
 */
void Engine::run() {
    glutMainLoop();
}

/**
 * @brief Ustawienie koloru tla.
 *
 * @param r Skladowa koloru czerwonego.
 * @param g Skladowa koloru zielonego.
 * @param b Skladowa koloru niebieskiego.
 * @param a Skladowa przezroczystosci.
 */
void Engine::setClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
    glClearColor(r, g, b, a);
}

/**
 * @brief Zmiana projekcji.
 *
 * @param projectionType Typ projekcji: 0 dla ortograficznej, 1 dla perspektywicznej.
 */
void Engine::changeProjection(int projectionType) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (projectionType == 0) { // Ortograficzna
        gluOrtho2D(0, 1, 0, 1);
    }
    else if (projectionType == 1) { // Perspektywiczna
        gluPerspective(45.0, 1.0, 1.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

/**
 * @brief Zamkniecie okna.
 */
void Engine::close() {
    if (glutGetWindow()) {
        glutDestroyWindow(glutGetWindow());
    }
}

/**
 * @brief Funkcja callback do wyswietlania sceny.
 */
void Engine::displayCallback() {
    instance->drawScene();
}

/**
 * @brief Funkcja callback wywolywana w stanie bezczynnosci.
 */
void Engine::idleCallback() {
    instance->animateObject();
    glutPostRedisplay();
}

/**
 * @brief Funkcja callback obslugujaca nacisniecia klawiszy.
 *
 * @param key Nacisniety klawisz.
 * @param x Pozycja kursora myszy w osi X.
 * @param y Pozycja kursora myszy w osi Y.
 */
void Engine::keyboardCallback(unsigned char key, int x, int y) {
    if (key == 27) { // Klawisz Escape
        instance->running = false;
        instance->close();
        exit(0);
    }
    instance->currentShape = key; // Ustawienie aktualnego ksztaltu

    switch (key) {
    case 'b':
    case 'B':
        instance->changeBackgroundColor();
        break;
    case 8: // Klawisz Backspace
        instance->setClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Ustawienie koloru tla na czarny
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
    case 'z':
        instance->changeFPS(5); // Zwiekszenie FPS o 5
        break;
    case 'x':
        instance->changeFPS(-5); // Zmniejszenie FPS o 5
        break;
    }
}

/**
 * @brief Funkcja callback obslugujaca

 specjalne klawisze.
 *
 * @param key Nacisniety specjalny klawisz.
 * @param x Pozycja kursora myszy w osi X.
 * @param y Pozycja kursora myszy w osi Y.
 */
void Engine::specialKeyCallback(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1:
        instance->changeCameraPosition(0.0f, 1.0f, 0.0f); // Przesuniecie kamery w gore
        break;
    case GLUT_KEY_F2: // Przesuniecie kamery w dol
        instance->changeCameraPosition(0.0f, -1.0f, 0.0f);
        break;
    case GLUT_KEY_F3: // Przesuniecie kamery w lewo
        instance->changeCameraPosition(-1.0f, 0.0f, 0.0f);
        break;
    case GLUT_KEY_F4: // Przesuniecie kamery w prawo
        instance->changeCameraPosition(1.0f, 0.0f, 0.0f);
        break;
    case GLUT_KEY_F5: // Przesuniecie kamery do przodu
        instance->changeCameraPosition(0.0f, 0.0f, -1.0f);
        break;
    case GLUT_KEY_F6: // Przesuniecie kamery do tylu
        instance->changeCameraPosition(0.0f, 0.0f, 1.1f);
        break;
    case GLUT_KEY_LEFT:
        instance->rotationY -= 5.0f; // Obrot w lewo
        break;
    case GLUT_KEY_RIGHT:
        instance->rotationY += 5.0f; // Obrot w prawo
        break;
    case GLUT_KEY_UP:
        instance->rotationX -= 5.0f; // Obrot w gore
        break;
    case GLUT_KEY_DOWN:
        instance->rotationX += 5.0f; // Obrot w dol
        break;
    case GLUT_KEY_F7:
        instance->size += 0.1f; // Zwiekszenie rozmiaru
        instance->height += 0.1f;
        instance->innerRadius += 0.1f;
        instance->radius += 0.1f;
        std::cout << "Zwiekszono rozmiar: size=" << instance->size << ", height=" << instance->height << ", innerRadius=" << instance->innerRadius << ", radius=" << instance->radius << std::endl;
        break;
    case GLUT_KEY_F8:
        instance->size -= 0.1f; // Zmniejszenie rozmiaru
        instance->height -= 0.1f;
        instance->innerRadius -= 0.1f;
        instance->radius -= 0.1f;
        std::cout << "Zmniejszono rozmiar: size=" << instance->size << ", height=" << instance->height << ", innerRadius=" << instance->innerRadius << ", radius=" << instance->radius << std::endl;
        break;
    }
    glutPostRedisplay();
}

/**
 * @brief Funkcja callback obslugujaca klikniecia myszy.
 *
 * @param button Nacisniety przycisk myszy.
 * @param state Stan przycisku myszy (GLUT_DOWN lub GLUT_UP).
 * @param x Pozycja kursora myszy w osi X.
 * @param y Pozycja kursora myszy w osi Y.
 */
void Engine::mouseCallback(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        instance->size = 17.0f;           // Ustawienie domyslnego rozmiaru obiektu
        instance->radius = 8.5f;          // Ustawienie domyslnego promienia obiektu
        instance->innerRadius = 1.4f;     // Ustawienie domyslnego wewnetrznego promienia obiektu
        instance->height = 17.0f;         // Ustawienie domyslnej wysokosci obiektu
        instance->clickX = x;         // Zapisanie pozycji klikniecia w osi X
        instance->clickY = y;         // Zapisanie pozycji klikniecia w osi Y
        instance->updateObjectPosition(instance->clickX, instance->clickY);
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {

        instance->toggleLighting();
    }
    else if ((button == 3 || button == 4) && state == GLUT_DOWN) { // Rolka w gore (3) lub w dol (4)
        if (button == 3) {
            glShadeModel(GL_SMOOTH);  // Zmiana cieniowania na GL_SMOOTH
            std::cout << "Zmiana cieniowania na: GL_SMOOTH" << std::endl;
        }
        else if (button == 4) {
            glShadeModel(GL_FLAT);    // Zmiana cieniowania na GL_FLAT
            std::cout << "Zmiana cieniowania na: GL_FLAT" << std::endl;
        }
        glutPostRedisplay(); // Zaktualizuj ekran po zmianie intensywnosci cieniowania
    }
}

/**
 * @brief Przelaczenie oswietlenia.
 */
void Engine::toggleLighting() {
    static bool lightingEnabled = true;
    if (lightingEnabled) {
        glDisable(GL_LIGHTING); // Wylacz oswietlenie
    }
    else {
        glEnable(GL_LIGHTING); // Wlacz oswietlenie
    }
    lightingEnabled = !lightingEnabled; // Przelacz stan oswietlenia
}
/**
 * @brief Aktualizacja pozycji obiektu.
 *
 * @param x Pozycja kursora myszy w osi X.
 * @param y Pozycja kursora myszy w osi Y.
 */
void Engine::updateObjectPosition(int x, int y) {
    GLint viewport[4];               // Tablica przechowujaca parametry widoku
    GLdouble modelview[16];          // Macierz modelu widoku
    GLdouble projection[16];         // Macierz projekcji
    GLfloat winX, winY, winZ;        // Wspolrzedne okna
    GLdouble posX, posY, posZ;       // Wspolrzedne swiata

    glGetIntegerv(GL_VIEWPORT, viewport);                   // Pobranie parametrow widoku
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);           // Pobranie macierzy modelu widoku
    glGetDoublev(GL_PROJECTION_MATRIX, projection);         // Pobranie macierzy projekcji

    winX = static_cast<float>(x);                           // Ustawienie wspolrzednej X okna
    winY = static_cast<float>(viewport[3] - y);             // Przeksztalcenie wspolrzednych okna Y
    glReadPixels(x, static_cast<int>(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ); // Odczytanie komponentu glebokosci

    if (winZ == 1.0f) winZ = 0.999f;                        // Korekta wartosci glebokosci
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ); // Przeksztalcenie wspolrzednych okna na wspolrzedne swiata

    instance->objectPosX = posX;                            // Aktualizacja pozycji X obiektu
    instance->objectPosY = posY;                            // Aktualizacja pozycji Y obiektu
    instance->objectPosZ = posZ;                            // Aktualizacja pozycji Z obiektu
    std::cout << "Kliknieto w: (" << x << ", " << y << "), wspolrzedne swiata: (" << instance->objectPosX << ", " << instance->objectPosY << ", " << instance->objectPosZ << ")" << std::endl;
}

/**
 * @brief Rysowanie sceny.
 */
void Engine::drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Czyszczenie buforow koloru i glebokosci
    glLoadIdentity();

    // Zastosowanie transformacji kamery
    camera.apply();

    // Ustawienie pozycji swiatla
    GLfloat lightPos[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Rysowanie wybranego ksztaltu
    drawShape();

    glutSwapBuffers();
}

/**
 * @brief Rysowanie ksztaltu.
 */
void Engine::drawShape() {
    glColor3f(0.0f, 0.0f, 1.0f); // Ustawienie koloru na niebieski
    glPushMatrix();
    glTranslatef(objectPosX, objectPosY, objectPosZ); // Ustawienie pozycji obiektu
    glRotatef(rotationX, 1.0, 0.0,

        0.0); // Obrot wzdluz osi X
    glRotatef(rotationY, 0.0, 1.0, 0.0); // Obrot wzdluz osi Y

    if (currentShape != lastShape) {
        // Aktualizacja zmiennej lastShape
        lastShape = currentShape;
        // Wyswietlenie komunikatu tylko raz, gdy ksztalt sie zmienia
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
            std::cout << "Rysujemy kule o promieniu : " << radius << std::endl;
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
            std::cout << "Rysujemy stozek o wysokosci " << height << std::endl;
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

/**
 * @brief Animacja obiektu.
 */
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

/**
 * @brief Funkcja callback timera.
 *
 * @param value Wartosc przekazywana do funkcji callback.
 */
void Engine::timerCallback(int value) {
    if (instance->running) {
        instance->animateObject();
        glutPostRedisplay();
        glutTimerFunc(1000 / instance->fps, timerCallback, value);
    }
}

/**
 * @brief Zmiana koloru tla.
 */
void Engine::changeBackgroundColor() {
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    setClearColor(r, g, b, 1.0f);
    std::cout << "Zmieniono kolor tla na: (" << r << ", " << g << ", " << b << ")" << std::endl;
}

/**
 * @brief Zmiana pozycji kamery.
 *
 * @param dx Przesuniecie kamery w osi X.
 * @param dy Przesuniecie kamery w osi Y.
 * @param dz Przesuniecie kamery w osi Z.
 */
void Engine::changeCameraPosition(float dx, float dy, float dz) {
    // Aktualizacja pozycji kamery
    camera.move(dx, dy, dz);
}

/**
 * @brief Zmiana wartosci FPS.
 *
 * @param delta Zmiana liczby klatek na sekunde.
 */
void Engine::changeFPS(int delta) {
    instance->fps += delta;
    if (instance->fps < 1) instance->fps = 1; // FPS nie moze byc mniejszy niz 1
    std::cout << "FPS zmienione na: " << instance->fps << std::endl;
    // Zaktualizuj timer z nowa wartoscia FPS
    glutTimerFunc(1000 / instance->fps, timerCallback, 0);
}

// Glowna funkcja programu
int main(int argc, char** argv) {
    Engine engine(argc, argv);
    engine.initWindow(1440, 900, "Game Engine", false);
    engine.run();
    return 0;
}

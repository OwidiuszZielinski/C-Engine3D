#define ENGINE_H

#include "Camera.h"

class Engine {
public:
    Engine(int argc, char** argv);
    ~Engine();
    void initWindow(int width, int height, const char* title, bool fullscreen);
    void setGraphicsMode(int fps, bool enableMouse, bool enableKeyboard, bool doubleBuffer, bool zBuffer);
    void run();
    void setClearColor(float r, float g, float b, float a);
    void changeProjection(int projectionType);
    void close();
    void changeBackgroundColor();
    void changeCameraPosition(float dx, float dy, float dz);

    static void displayCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialKeyCallback(int key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    static void changeFPS(int fps);
    static void timerCallback(int value); 
    static void toggleLighting();
    
    static Engine* instance;

private:
    void drawScene();
    void drawShape();
    void updateObjectPosition(int x, int y);
    void animateObject(); 

    bool running;
    int fps;
    float size;
    float radius;
    float innerRadius;
    float height;
    char currentShape;
    char lastShape;
    float rotationX;
    float rotationY;
    float rotationSpeedX;
    float rotationSpeedY;
    bool animate;
    int clickX;
    int clickY;
    float objectPosX;
    float objectPosY;
    float objectPosZ;
    bool drawOnClick;
    float clearColor[4];
    float shadingIntensity;
    Camera camera;
};
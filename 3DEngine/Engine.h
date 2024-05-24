#ifndef ENGINE_H
#define ENGINE_H

#include "Camera.h"

class Engine {
public:
    Engine(int argc, char** argv);
    ~Engine();
    void initWindow(int width, int height, const char* title, bool fullscreen = false);
    void setGraphicsMode(int fps, bool enableMouse = true, bool enableKeyboard = true, bool doubleBuffer = true, bool zBuffer = true);
    void run();
    void setClearColor(float r, float g, float b, float a);
    void changeProjection(int projectionType);
    void close();
    void changeCameraPosition(float x, float y, float z);
   
    

private:
    static void displayCallback();
    static void idleCallback();
    static void keyboardCallback(unsigned char key, int x, int y);
    static void specialKeyCallback(int key, int x, int y);
    static void mouseCallback(int button, int state, int x, int y);
    void changeBackgroundColor();
    static Engine* instance;
    float clearColor[4];
    float cameraPosition[2];
    float cameraTarget[2];
    Camera camera;
    
    int fps;
    bool running;
    char currentShape;
    float rotationX, rotationY;
    float size;
    float radius;
    float innerRadius;
    float height;
    void drawScene();
    void drawShape();
    char lastShape;
    float clickX;
    float clickY;
    bool drawOnClick;
};

#endif // ENGINE_H

#ifndef SHAPEDRAWER_H
#define SHAPEDRAWER_H

class ShapeDrawer {
public:
    static void drawCube(float size);
    static void drawSphere(float radius, int slices, int stacks);
    static void drawTeapot(float size);
    static void drawTorus(float innerRadius, float outerRadius, int sides, int rings);
    static void drawCone(float base, float height, int slices, int stacks);
    static void drawWireCube(float size);
    static void drawTriangle(float size);
};

#endif // SHAPEDRAWER_H

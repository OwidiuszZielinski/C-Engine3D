#include "Camera.h"
#include <GL/glut.h>

Camera::Camera() {
    posX = 0.0f;
    posY = 0.0f;
    posZ = 5.0f; // Default position
    targetX = 0.0f;
    targetY = 0.0f;
    targetZ = 0.0f; // Default target
}

void Camera::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
}

void Camera::setTarget(float x, float y, float z) {
    targetX = x;
    targetY = y;
    targetZ = z;
}

void Camera::move(float dx, float dy, float dz) {
    posX += dx;
    posY += dy;
    posZ += dz;
}

void Camera::apply() {
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);
}

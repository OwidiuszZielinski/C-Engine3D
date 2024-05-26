#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    Camera();
    void setPosition(float x, float y, float z);
    void setTarget(float x, float y, float z);
    void move(float dx, float dy, float dz);
    void apply();

    // Add getters for current position
    float getPosX() const { return posX; }
    float getPosY() const { return posY; }
    float getPosZ() const { return posZ; }

private:
    float posX, posY, posZ;
    float targetX, targetY, targetZ;
};

#endif // CAMERA_H

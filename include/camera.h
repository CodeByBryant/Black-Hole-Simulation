#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    
    float distance;
    float yaw;
    float pitch;
    
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    
    Camera();
    
    void updatePosition();
    void rotate(float deltaYaw, float deltaPitch);
    void zoom(float delta);
    void pan(float deltaX, float deltaY);
    
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};

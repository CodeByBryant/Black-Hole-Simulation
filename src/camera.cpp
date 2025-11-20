#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera() {
    position = glm::vec3(0.0f, 5.0f, 15.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    distance = 15.0f;
    yaw = 0.0f;
    pitch = 20.0f;
    
    fov = 45.0f;
    aspectRatio = 16.0f / 9.0f;
    nearPlane = 0.1f;
    farPlane = 1000.0f;
    
    updatePosition();
}

void Camera::updatePosition() {
    float pitchRad = glm::radians(pitch);
    float yawRad = glm::radians(yaw);
    
    position.x = target.x + distance * cos(pitchRad) * sin(yawRad);
    position.y = target.y + distance * sin(pitchRad);
    position.z = target.z + distance * cos(pitchRad) * cos(yawRad);
}

void Camera::rotate(float deltaYaw, float deltaPitch) {
    yaw += deltaYaw;
    pitch += deltaPitch;
    
    pitch = std::max(-89.0f, std::min(89.0f, pitch));
    
    updatePosition();
}

void Camera::zoom(float delta) {
    distance += delta;
    distance = std::max(2.0f, std::min(100.0f, distance));
    updatePosition();
}

void Camera::pan(float deltaX, float deltaY) {
    glm::vec3 right = glm::normalize(glm::cross(position - target, up));
    glm::vec3 upDir = glm::normalize(glm::cross(right, position - target));
    
    target += right * deltaX * distance * 0.001f;
    target += upDir * deltaY * distance * 0.001f;
    
    updatePosition();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

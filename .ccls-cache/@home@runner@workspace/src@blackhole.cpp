#include "blackhole.h"
#include <cmath>

BlackHole::BlackHole(glm::vec3 pos, float m) {
    position = pos;
    mass = m;
    schwarzschildRadius = getSchwarzschildRadius();
    accretionDiskInnerRadius = schwarzschildRadius * 3.0f;
    accretionDiskOuterRadius = schwarzschildRadius * 8.0f;
}

float BlackHole::getSchwarzschildRadius() {
    const float G = 6.674e-11f;
    const float c = 299792458.0f;
    return (2.0f * G * mass) / (c * c) * 1e10f;
}

glm::vec3 BlackHole::calculateLensing(glm::vec3 rayOrigin, glm::vec3 rayDir, float maxDist) {
    glm::vec3 toBH = position - rayOrigin;
    float distance = glm::length(toBH);
    
    if (distance < schwarzschildRadius) {
        return glm::vec3(0.0f);
    }
    
    float bendingFactor = (schwarzschildRadius / distance) * 2.0f;
    
    glm::vec3 perpendicular = glm::normalize(glm::cross(rayDir, toBH));
    glm::vec3 towardBH = glm::normalize(toBH);
    
    glm::vec3 bentDir = glm::normalize(rayDir + towardBH * bendingFactor);
    
    return bentDir;
}

bool BlackHole::isInsideEventHorizon(glm::vec3 pos) {
    return glm::length(pos - position) < schwarzschildRadius;
}

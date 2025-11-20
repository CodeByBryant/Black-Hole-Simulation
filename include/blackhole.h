#pragma once
#include <glm/glm.hpp>

class BlackHole {
public:
    glm::vec3 position;
    float mass;
    float schwarzschildRadius;
    float accretionDiskInnerRadius;
    float accretionDiskOuterRadius;
    
    BlackHole(glm::vec3 pos, float m);
    
    float getSchwarzschildRadius();
    glm::vec3 calculateLensing(glm::vec3 rayOrigin, glm::vec3 rayDir, float maxDist);
    bool isInsideEventHorizon(glm::vec3 pos);
};

#pragma once
#include <glm/glm.hpp>
#include <vector>

class SimObject {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 color;
    float mass;
    float radius;
    bool hasLight;
    
    std::vector<glm::vec3> trail;
    int maxTrailLength;
    
    SimObject(glm::vec3 pos, glm::vec3 vel, float m, float r, glm::vec3 col);
    
    void update(float dt);
    void addForce(glm::vec3 force, float dt);
    void updateTrail();
};

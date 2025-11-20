#pragma once
#include "object.h"
#include "blackhole.h"
#include <vector>

class PhysicsEngine {
public:
    std::vector<SimObject*> objects;
    BlackHole* blackHole;
    
    float gravitationalConstant;
    
    PhysicsEngine();
    
    void addObject(SimObject* obj);
    void removeObject(int index);
    void update(float dt);
    
private:
    glm::vec3 calculateGravitationalForce(SimObject* obj1, SimObject* obj2);
    glm::vec3 calculateBlackHoleForce(SimObject* obj);
};

#include "physics.h"
#include <glm/glm.hpp>

PhysicsEngine::PhysicsEngine() {
    gravitationalConstant = 0.5f;
    blackHole = nullptr;
}

void PhysicsEngine::addObject(SimObject* obj) {
    objects.push_back(obj);
}

void PhysicsEngine::removeObject(int index) {
    if (index >= 0 && index < static_cast<int>(objects.size())) {
        delete objects[index];
        objects.erase(objects.begin() + index);
    }
}

void PhysicsEngine::update(float dt) {
    // First, update all objects
    for (size_t i = 0; i < objects.size(); i++) {
        glm::vec3 totalForce(0.0f);
        
        if (blackHole) {
            totalForce += calculateBlackHoleForce(objects[i]);
        }
        
        for (size_t j = 0; j < objects.size(); j++) {
            if (i != j) {
                totalForce += calculateGravitationalForce(objects[i], objects[j]);
            }
        }
        
        objects[i]->addForce(totalForce, dt);
        objects[i]->update(dt);
    }
    
    // Then, remove objects that fell into the black hole (iterate backwards to avoid issues)
    if (blackHole) {
        for (int i = static_cast<int>(objects.size()) - 1; i >= 0; i--) {
            if (blackHole->isInsideEventHorizon(objects[i]->position)) {
                removeObject(i);
            }
        }
    }
}

glm::vec3 PhysicsEngine::calculateGravitationalForce(SimObject* obj1, SimObject* obj2) {
    glm::vec3 direction = obj2->position - obj1->position;
    float distance = glm::length(direction);
    
    if (distance < 0.01f) {
        return glm::vec3(0.0f);
    }
    
    direction = glm::normalize(direction);
    float forceMagnitude = gravitationalConstant * obj1->mass * obj2->mass / (distance * distance);
    
    return direction * forceMagnitude;
}

glm::vec3 PhysicsEngine::calculateBlackHoleForce(SimObject* obj) {
    glm::vec3 direction = blackHole->position - obj->position;
    float distance = glm::length(direction);
    
    if (distance < 0.01f) {
        return glm::vec3(0.0f);
    }
    
    direction = glm::normalize(direction);
    float forceMagnitude = gravitationalConstant * obj->mass * blackHole->mass / (distance * distance);
    
    return direction * forceMagnitude;
}

#include "object.h"

SimObject::SimObject(glm::vec3 pos, glm::vec3 vel, float m, float r, glm::vec3 col) {
    position = pos;
    velocity = vel;
    mass = m;
    radius = r;
    color = col;
    hasLight = false;
    maxTrailLength = 200;
}

void SimObject::update(float dt) {
    position += velocity * dt;
    updateTrail();
}

void SimObject::addForce(glm::vec3 force, float dt) {
    glm::vec3 acceleration = force / mass;
    velocity += acceleration * dt;
}

void SimObject::updateTrail() {
    trail.push_back(position);
    
    if (trail.size() > maxTrailLength) {
        trail.erase(trail.begin());
    }
}

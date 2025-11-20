#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "camera.h"
#include "physics.h"
#include "shader.h"

class Renderer {
public:
    GLFWwindow* window;
    int width;
    int height;
    
    Shader* objectShader;
    Shader* skyboxShader;
    Shader* accretionShader;
    
    GLuint sphereVAO;
    GLuint sphereVBO;
    GLuint sphereEBO;
    int sphereIndexCount;
    
    GLuint skyboxVAO;
    GLuint skyboxVBO;
    
    Renderer(int w, int h);
    ~Renderer();
    
    bool initialize();
    void render(Camera& camera, PhysicsEngine& physics);
    void cleanup();
    
private:
    void createSphere();
    void createSkybox();
    void renderObject(SimObject* obj, Camera& camera);
    void renderBlackHole(BlackHole* bh, Camera& camera);
    void renderAccretionDisk(BlackHole* bh, Camera& camera);
    void renderSkybox(Camera& camera);
    void renderTrail(SimObject* obj, Camera& camera);
};

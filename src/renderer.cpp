#include "renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include <vector>

Renderer::Renderer(int w, int h) : width(w), height(h), window(nullptr) {
    objectShader = nullptr;
    skyboxShader = nullptr;
    accretionShader = nullptr;
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(width, height, "Black Hole Simulation", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    objectShader = new Shader("shaders/object.vert", "shaders/object.frag");
    skyboxShader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");
    accretionShader = new Shader("shaders/accretion.vert", "shaders/accretion.frag");
    
    if (objectShader->program == 0 || skyboxShader->program == 0 || accretionShader->program == 0) {
        std::cerr << "ERROR: Failed to initialize shaders" << std::endl;
        std::cerr << "Make sure shader files exist in the 'shaders/' directory" << std::endl;
        return false;
    }
    
    createSphere();
    createSkybox();
    
    std::cout << "Renderer initialized successfully!" << std::endl;
    return true;
}

void Renderer::createSphere() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    const int sectors = 36;
    const int stacks = 18;
    const float radius = 1.0f;
    
    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = M_PI / 2 - i * M_PI / stacks;
        float xy = radius * cosf(stackAngle);
        float z = radius * sinf(stackAngle);
        
        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * 2 * M_PI / sectors;
            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);
            
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            
            float nx = x / radius;
            float ny = y / radius;
            float nz = z / radius;
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);
        }
    }
    
    for (int i = 0; i < stacks; ++i) {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;
        
        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            
            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    
    sphereIndexCount = indices.size();
    
    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);
    
    glBindVertexArray(sphereVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
}

void Renderer::createSkybox() {
    float skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
}

void Renderer::render(Camera& camera, PhysicsEngine& physics) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    renderSkybox(camera);
    
    if (physics.blackHole) {
        renderAccretionDisk(physics.blackHole, camera);
        renderBlackHole(physics.blackHole, camera);
    }
    
    for (auto* obj : physics.objects) {
        renderObject(obj, camera);
        renderTrail(obj, camera);
    }
}

void Renderer::renderObject(SimObject* obj, Camera& camera) {
    objectShader->use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, obj->position);
    model = glm::scale(model, glm::vec3(obj->radius));
    
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    
    objectShader->setMat4("model", glm::value_ptr(model));
    objectShader->setMat4("view", glm::value_ptr(view));
    objectShader->setMat4("projection", glm::value_ptr(projection));
    objectShader->setVec3("objectColor", obj->color.x, obj->color.y, obj->color.z);
    objectShader->setVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);
    objectShader->setVec3("lightPos", obj->position.x, obj->position.y, obj->position.z);
    objectShader->setFloat("hasLight", obj->hasLight ? 1.0f : 0.0f);
    
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLES, sphereIndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::renderBlackHole(BlackHole* bh, Camera& camera) {
    objectShader->use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, bh->position);
    model = glm::scale(model, glm::vec3(bh->schwarzschildRadius));
    
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    
    objectShader->setMat4("model", glm::value_ptr(model));
    objectShader->setMat4("view", glm::value_ptr(view));
    objectShader->setMat4("projection", glm::value_ptr(projection));
    objectShader->setVec3("objectColor", 0.0f, 0.0f, 0.0f);
    objectShader->setVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);
    objectShader->setVec3("lightPos", 0.0f, 0.0f, 0.0f);
    objectShader->setFloat("hasLight", 1.0f);
    
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLES, sphereIndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::renderAccretionDisk(BlackHole* bh, Camera& camera) {
    accretionShader->use();
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, bh->position);
    model = glm::scale(model, glm::vec3(bh->accretionDiskOuterRadius));
    
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    
    accretionShader->setMat4("model", glm::value_ptr(model));
    accretionShader->setMat4("view", glm::value_ptr(view));
    accretionShader->setMat4("projection", glm::value_ptr(projection));
    accretionShader->setVec3("blackHolePos", bh->position.x, bh->position.y, bh->position.z);
    accretionShader->setFloat("innerRadius", bh->accretionDiskInnerRadius);
    accretionShader->setFloat("outerRadius", bh->accretionDiskOuterRadius);
    accretionShader->setFloat("time", (float)glfwGetTime());
    
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLES, sphereIndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer::renderSkybox(Camera& camera) {
    glDepthFunc(GL_LEQUAL);
    skyboxShader->use();
    
    glm::mat4 view = glm::mat4(glm::mat3(camera.getViewMatrix()));
    glm::mat4 projection = camera.getProjectionMatrix();
    
    skyboxShader->setMat4("view", glm::value_ptr(view));
    skyboxShader->setMat4("projection", glm::value_ptr(projection));
    skyboxShader->setVec3("blackHolePos", 0.0f, 0.0f, 0.0f);
    skyboxShader->setFloat("blackHoleMass", 1000.0f);
    
    glBindVertexArray(skyboxVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    
    glDepthFunc(GL_LESS);
}

void Renderer::renderTrail(SimObject* obj, Camera& camera) {
    if (obj->trail.size() < 2) return;
    
    objectShader->use();
    
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    
    for (size_t i = 0; i < obj->trail.size() - 1; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, obj->trail[i]);
        model = glm::scale(model, glm::vec3(obj->radius * 0.2f));
        
        float alpha = (float)i / obj->trail.size();
        
        objectShader->setMat4("model", glm::value_ptr(model));
        objectShader->setMat4("view", glm::value_ptr(view));
        objectShader->setMat4("projection", glm::value_ptr(projection));
        objectShader->setVec3("objectColor", obj->color.x * alpha, obj->color.y * alpha, obj->color.z * alpha);
        objectShader->setVec3("viewPos", camera.position.x, camera.position.y, camera.position.z);
        objectShader->setVec3("lightPos", obj->position.x, obj->position.y, obj->position.z);
        objectShader->setFloat("hasLight", 1.0f);
        
        glBindVertexArray(sphereVAO);
        glDrawElements(GL_TRIANGLES, sphereIndexCount, GL_UNSIGNED_INT, 0);
    }
    
    glBindVertexArray(0);
}

void Renderer::cleanup() {
    if (objectShader) delete objectShader;
    if (skyboxShader) delete skyboxShader;
    if (accretionShader) delete accretionShader;
    
    glDeleteVertexArrays(1, &sphereVAO);
    glDeleteBuffers(1, &sphereVBO);
    glDeleteBuffers(1, &sphereEBO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

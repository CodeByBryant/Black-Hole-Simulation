#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

#include "renderer.h"
#include "camera.h"
#include "physics.h"
#include "blackhole.h"
#include "object.h"

bool leftMousePressed = false;
bool rightMousePressed = false;
bool middleMousePressed = false;
double lastX = 0.0;
double lastY = 0.0;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        leftMousePressed = (action == GLFW_PRESS);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        rightMousePressed = (action == GLFW_PRESS);
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        middleMousePressed = (action == GLFW_PRESS);
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    if (camera) {
        camera->zoom(-yoffset * 0.5f);
    }
}

int main() {
    Renderer renderer(1280, 720);
    
    if (!renderer.initialize()) {
        std::cerr << "Failed to initialize renderer" << std::endl;
        return -1;
    }
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(renderer.window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    Camera camera;
    camera.aspectRatio = (float)renderer.width / (float)renderer.height;
    
    PhysicsEngine physics;
    BlackHole blackHole(glm::vec3(0.0f, 0.0f, 0.0f), 1000.0f);
    physics.blackHole = &blackHole;
    
    SimObject* initialObject = new SimObject(
        glm::vec3(5.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 2.0f),
        1.0f,
        0.3f,
        glm::vec3(0.2f, 0.6f, 1.0f)
    );
    physics.addObject(initialObject);
    
    glfwSetWindowUserPointer(renderer.window, &camera);
    glfwSetMouseButtonCallback(renderer.window, mouseButtonCallback);
    glfwSetScrollCallback(renderer.window, scrollCallback);
    
    float newObjectPosX = 5.0f, newObjectPosY = 0.0f, newObjectPosZ = 0.0f;
    float newObjectVelX = 0.0f, newObjectVelY = 0.0f, newObjectVelZ = 2.0f;
    float newObjectMass = 1.0f;
    float newObjectRadius = 0.3f;
    float newObjectColor[3] = {1.0f, 0.5f, 0.0f};
    bool newObjectHasLight = false;
    
    float timeScale = 1.0f;
    bool paused = false;
    
    double lastTime = glfwGetTime();
    
    while (!glfwWindowShouldClose(renderer.window)) {
        double currentTime = glfwGetTime();
        float deltaTime = (float)(currentTime - lastTime);
        lastTime = currentTime;
        
        glfwPollEvents();
        
        double xpos, ypos;
        glfwGetCursorPos(renderer.window, &xpos, &ypos);
        
        if (leftMousePressed && !io.WantCaptureMouse) {
            double deltaX = xpos - lastX;
            double deltaY = ypos - lastY;
            camera.rotate(deltaX * 0.2f, -deltaY * 0.2f);
        }
        
        if (rightMousePressed && !io.WantCaptureMouse) {
            double deltaX = xpos - lastX;
            double deltaY = ypos - lastY;
            camera.pan(deltaX, -deltaY);
        }
        
        lastX = xpos;
        lastY = ypos;
        
        if (!paused) {
            physics.update(deltaTime * timeScale);
        }
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("Black Hole Simulation Controls");
        
        ImGui::Text("Camera Controls:");
        ImGui::BulletText("Left Mouse: Rotate");
        ImGui::BulletText("Right Mouse: Pan");
        ImGui::BulletText("Scroll: Zoom");
        
        ImGui::Separator();
        
        ImGui::Text("Simulation:");
        if (ImGui::Button(paused ? "Resume" : "Pause")) {
            paused = !paused;
        }
        ImGui::SliderFloat("Time Scale", &timeScale, 0.1f, 5.0f);
        
        ImGui::Separator();
        
        ImGui::Text("Black Hole:");
        ImGui::Text("Mass: %.2f", blackHole.mass);
        ImGui::Text("Schwarzschild Radius: %.2f", blackHole.schwarzschildRadius);
        
        ImGui::Separator();
        
        ImGui::Text("Add New Object:");
        ImGui::InputFloat3("Position", &newObjectPosX);
        ImGui::InputFloat3("Velocity", &newObjectVelX);
        ImGui::SliderFloat("Mass", &newObjectMass, 0.1f, 10.0f);
        ImGui::SliderFloat("Radius", &newObjectRadius, 0.1f, 2.0f);
        ImGui::ColorEdit3("Color", newObjectColor);
        ImGui::Checkbox("Has Light", &newObjectHasLight);
        
        if (ImGui::Button("Add Object")) {
            SimObject* newObj = new SimObject(
                glm::vec3(newObjectPosX, newObjectPosY, newObjectPosZ),
                glm::vec3(newObjectVelX, newObjectVelY, newObjectVelZ),
                newObjectMass,
                newObjectRadius,
                glm::vec3(newObjectColor[0], newObjectColor[1], newObjectColor[2])
            );
            newObj->hasLight = newObjectHasLight;
            physics.addObject(newObj);
        }
        
        ImGui::Separator();
        
        ImGui::Text("Objects in simulation: %d", (int)physics.objects.size());
        
        if (ImGui::Button("Clear All Objects")) {
            while (!physics.objects.empty()) {
                physics.removeObject(0);
            }
        }
        
        ImGui::Separator();
        
        ImGui::Text("FPS: %.1f", io.Framerate);
        
        ImGui::End();
        
        renderer.render(camera, physics);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(renderer.window);
    }
    
    while (!physics.objects.empty()) {
        physics.removeObject(0);
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    return 0;
}

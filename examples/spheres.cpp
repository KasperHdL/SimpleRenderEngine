#include <iostream>
#include <vector>
#include <fstream>

#include "sre/Texture.hpp"
#include "sre/Renderer.hpp"
#include "sre/Material.hpp"
#include "sre/Camera.hpp"
#include "sre/Mesh.hpp"
#include "sre/Shader.hpp"
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include <glm/glm.hpp>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace sre;

int main() {
    std::cout << "Spinning sphere"<<std::endl;
    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags
    );

    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    Renderer r{window};

    Camera camera;
    camera.lookAt({0,0,3},{0,0,0},{0,1,0});
    camera.setPerspectiveProjection(60,640,480,0.1f,100);
    Shader* shader = Shader::getStandard();
    Mesh* mesh = Mesh::create()
            .withSphere()
            .build();

    WorldLights worldLights;
    worldLights.addLight(Light::create()
            .withDirectionalLight(glm::normalize(glm::vec3(1,1,1)))
            .build());

    Material* mat1 = new Material(shader);
    mat1->setColor({1,1,1,1});
    mat1->setSpecularity(50);

    Material* mat2 = new Material(shader);
    mat2->setColor({1,0,0,1});
    mat2->setSpecularity(0);

    float duration = 100000;
    glm::mat4 pos1 = glm::translate(glm::mat4(1), {-1,0,0});
    glm::mat4 pos2 = glm::translate(glm::mat4(1), {1,0,0});
    for (float i=0;i<duration ;i+=16){
        auto rp = r.createRenderPass()
                    .withCamera(camera)
                    .withWorldLights(&worldLights)
                    .withClearColor(true,{1,0,0,1})
                    .build();

        rp.draw(mesh, pos1, mat1);
        rp.draw(mesh, pos2, mat2);

        r.swapWindow();
        SDL_Delay(16);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}


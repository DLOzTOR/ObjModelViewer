#include <iostream>
#include <SFML/Graphics.hpp>
#include "Render/glewInit.h"
#include "Render/Render.h"
#include "Engine/Entity.h"
#include "Engine/Terrain.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void HadwareInfo();
using glm::mat4;
using glm::vec3;

GLuint vao;
GLuint VAOposId;
GLuint colorbuffer;
int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window", sf::Style::Default, settings);
    window.setActive();
    window.setFramerateLimit(30);
    if (glewInit() != GLEW_OK) { std::cout << "Glew init problem" << std::endl; return -1; }
    HadwareInfo();
    Render::Shader shader;
    Engine::Terrain terrain;
    //terrain.modeOfRender = GL_LINES;
    terrain.GenerateTerraine();
    //shader.addAndCompileShader("Shaders/texture.vert", "Shaders/texture.frag");
    shader.addAndCompileShader("Shaders/basic.vert", "Shaders/basic.frag");
    Render::Model model;
    model.texture.LoadTexture("Resources/TexturedCubePaintTexture.png");
    model.LoadFromObj("Resources/TexturedCube.obj");
    Engine::Entity entities[5][5];
    //for (int i = 0; i < 5; i++)
    //{
    //    for (int j = 0; j < 5; j++)
    //    {
    //        entities[i][j].transform = glm::translate(entities[i][j].transform, vec3(i - 2.f, j - 2.f, 0) * vec3(0.25f));
    //        entities[i][j].model = model;
    //    }
    //}
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    mat4 rotationMatrix = mat4(1.0f);
    float angle = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (angle > 360)angle = 0;
        shader.Use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Render
        //glClearColor(0.1f, 0.5f, 0.2f, 1);
        glClearColor(0,0,0,1);
        rotationMatrix = glm::rotate(mat4(1.0f), glm::radians(230.f), vec3(1, 0, 0));
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angle), vec3(0, 0, 1));
        angle++;
        glm::mat4 m = glm::mat4(1);
        //m = glm::translate(m, vec3(0,0,-1.5));
        GLuint location = glGetUniformLocation(shader.shaderHandle, "RotationMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
        location = glGetUniformLocation(shader.shaderHandle, "TransformMatrix");
        glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
        //model.Draw();
        terrain.Draw();
        window.display();//Render end
    }
    std::cout << "SFML window cloased!\n";
    return 0;
}

void HadwareInfo() {
    std::cout << "Vendor " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Hardware platform " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}
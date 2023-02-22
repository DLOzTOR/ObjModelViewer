#include <iostream>
#include <SFML/Graphics.hpp>
#include "Render/glewInit.h"
#include "Render/Render.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
void HadwareInfo();
using glm::mat4;
using glm::vec3;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // Треугольник 1 : начало
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // Треугольник 1 : конец
    1.0f, 1.0f,-1.0f, // Треугольник 2 : начало
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // Треугольник 2 : конец
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};
GLuint vao;
GLuint VAOposId;
GLuint colorbuffer;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    window.setActive();
    window.setFramerateLimit(60);
    if (glewInit() != GLEW_OK) {std::cout << "Glew init problem" << std::endl; return -1;}
    HadwareInfo();
    Render::Shader shader;
    shader.addAndCompileShader("Shaders/basic.vert", "Shaders/basic.frag");
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &VAOposId);
    glBindBuffer(GL_ARRAY_BUFFER, VAOposId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0, (void*)0);
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
        rotationMatrix = glm::rotate(mat4(1.0f), glm::radians(30.f), vec3(0, 1, 1 ));
        GLuint location = glGetUniformLocation(shader.shaderHandle, "RotationMatrix");
        angle++;
        glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Render
        glClearColor(0, 0, 0, 1);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 108);
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
#define GLM_FORCE_CTOR_INIT

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

constexpr auto vertexShader = R"(
#version 330 core
layout (location = 1) in vec3 aPosition;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPosition, 1.0);
}
)";

constexpr auto fragmentShader = R"(
#version 330 core
out vec4 fragColor;

uniform vec3 color;

void main()
{
	fragColor = vec4(color, 1.0);
}
)";

constexpr float vertices[] = {
	-1.0,  1.0, 0.0, // Top Left
	-1.0, -1.0, 0.0, // Bottom Left
	 1.0, -1.0, 0.0, // Bottom Right
	 1.0,  1.0, 0.0, // Top Right
};

int main(int, char**)
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);	
	}

	// window creation	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    auto window = glfwCreateWindow(800, 800, "OpenGL Grid", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(EXIT_FAILURE);
	}

	// create shader
	Shader shader{ vertexShader, fragmentShader };

	// generate vbo and buffer data
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// generate vao and configure attributes
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLint positionIndex = shader.getAttributeLocation("aPosition");
	glVertexAttribPointer(positionIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(positionIndex);

	// setup
	glClearColor(0.2f, 0.3f, 0.2f, 1.0f);
	shader.set("color", vec3{ 1.0, 0.5, 0.5 });
	shader.set("transform", scale(mat4(), vec3{ vec2{0.75f}, 1.0f }));

	// game loop
    while (!glfwWindowShouldClose(window))
    {
		glBindVertexArray(vao);
		shader.use();
		
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


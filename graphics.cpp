#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shaders.h"

float r = 0.0f;
float g = 0.0f;
float b = 0.0f;

bool x = true;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.0f,    0, 3,
		0.5f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,	 5, 3,
		0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f,	 1, 4,
		0.0f, -0.5f, 0.0f,      1.0f, 1.0f, 1.0f,	 5, 4,
		0.25f, 0.0f, 0.0f,      0.0f, 0.0f, 0.0f,	 2,
		-0.25f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f
	};	

	GLuint indices[] =
	{
		0, 3, 5,
		3, 1, 4,
		5, 4, 2
	};

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "AMOOGUS", monitor, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();	

	glViewport(0, 0, 1920, 1080);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Deactivate();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
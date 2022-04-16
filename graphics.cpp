#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_img.h>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shaders.h"
#include "Texture.h"

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
		-0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 0.0f, 1.0f,	   2.0f, 0.0f,
		0.5f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f, 1.0f,	   2.0f, 2.0f,
		-0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 1.0f, 1.0f,    0.0f, 2.0f
	};	

	GLuint indices[] =
	{
		0, 1, 2,
		0, 3, 2
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

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);

	
	Texture samurai("samurai-_-wallpaper.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	samurai.texUni(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		samurai.Bind();

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Deactivate();
	samurai.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
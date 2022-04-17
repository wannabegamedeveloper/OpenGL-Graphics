#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_img.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		-0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f, 0.0f,    0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,       0.0f, 0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,      1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f,

		-0.5f, -0.2f, 0.5f,      0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
		0.5f, -0.2f, 0.5f,       1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		0.5f, -0.2f, -0.5f,      1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,
		-0.5f, -0.2f, -0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f
	};	

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		0, 1, 4,
		4, 5, 1,

		0, 4, 7,
		7, 3, 0,

		3, 2, 6,
		6, 7, 3,

		1, 2, 6,
		6, 5, 1
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
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);

	
	Texture samurai("artworks-eW8o6DtdrA94gBzk-Hi77Eg-t500x500.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	samurai.texUni(shaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1 / 20)
		{
			rotation += 0.05f;
			prevTime = currentTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 1.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -4.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)(1920 / 1080), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProgram.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		samurai.Bind();

		VAO1.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

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
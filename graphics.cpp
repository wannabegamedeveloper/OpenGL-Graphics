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
#include "Camera.h"

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
		-0.5f, -0.5f, 0.5f,     1.0f, 1.0f, 1.0f, 0.0f,    0.0f, 0.0f,    0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 0.0f, 1.0f,	   1.0f, 0.0f,    0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f,    0.0f, -1.0f, 0.0f,

		-0.5f, -0.2f, 0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 1.0f, 0.0f,
		0.5f, -0.2f, 0.5f,      1.0f, 1.0f, 1.0f, 1.0f,	   1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
		0.5f, -0.2f, -0.5f,     1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
		-0.5f, -0.2f, -0.5f,    0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f,

		-0.5f, -0.2f, 0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, 1.0f,
		0.5f, -0.2f, 0.5f,      1.0f, 1.0f, 1.0f, 1.0f,	   1.0f, 0.0f,    0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,      1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f,    0.0f, 0.0f, 1.0f,

		-0.5f, -0.2f, 0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    -1.0f, 0.0f, 0.0f,
		-0.5f, -0.2f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f,	   1.0f, 0.0f,    -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f,    -1.0f, 0.0f, 0.0f,

		-0.5f, -0.2f, -0.5f,    0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f, 1.0f,	   1.0f, 0.0f,    0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 1.0f,    0.0f, 0.0f, -1.0f,
		0.5f, -0.2f, -0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 1.0f,    0.0f, 0.0f, -1.0f,

		0.5f, -0.2f, -0.5f,     0.0f, 0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,     1.0f, 1.0f, 1.0f, 1.0f,	   0.0f, 1.0f,    1.0f, 0.0f, 0.0f,
		0.5f, -0.2f, 0.5f,      1.0f, 1.0f, 1.0f, 1.0f,    1.0f, 0.0f,    1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 0.0f, 1.0f,    1.0f, 1.0f,    1.0f, 0.0f, 0.0f
	};	

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 21
	};

	GLfloat lightVert[] =
	{
		-0.1f, -0.1f, 0.1f, 
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, 0.1f,

		-0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, 0.1f
	};

	GLuint lightInd[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
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

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 12 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 12 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 12 * sizeof(float), (void*)(7 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 12 * sizeof(float), (void*)(9 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);

	Shader lightShader("light.vert", "light.frag");

	VAO vaoLight;
	vaoLight.Bind();

	VBO vboLight(lightVert, sizeof(lightVert));
	EBO eboLight(lightInd, sizeof(lightInd));

	vaoLight.LinkAttrib(vboLight, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	vaoLight.Unbind();
	vboLight.Unbind();
	eboLight.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 cuboidPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 cuboidModel = glm::mat4(1.0f);
	cuboidModel = glm::translate(cuboidModel, cuboidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cuboidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Texture plank("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	plank.texUni(shaderProgram, "tex0", 0);
	Texture plankSpecular("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	plankSpecular.texUni(shaderProgram, "tex1", 1);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	Camera camera(1920, 1080, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		camera.Input(window);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(shaderProgram, "camMatrix");

		plank.Bind();
		plankSpecular.Bind();

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		vaoLight.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightInd) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Deactivate();
	plank.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
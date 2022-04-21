#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	Camera::first_click = false;
}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + orientation, up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Input(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
		if (!first_click)
		{
			glfwSetCursorPos(window, (width / 2), height / 2);
			first_click = true;

			oldPos = Position;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		
		Position = glm::vec3(mouseX / 1920, mouseY / 1080 - oldPos.y, Position.z);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
	{
		first_click = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS) return;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position -= speed * glm::normalize(glm::cross(orientation, up));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position -= speed * orientation;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += speed * glm::normalize(glm::cross(orientation, up));
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		Position -= speed * glm::normalize(glm::cross(orientation, glm::cross(orientation, up)));
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		Position += speed * glm::normalize(glm::cross(orientation, glm::cross(orientation, up)));

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (!first_click)
		{
			glfwSetCursorPos(window, (width / 2), height / 2);
			first_click = true;
		}

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = senstivity * (float)(mouseY - (height / 2)) / height;
		float rotY = senstivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		if ((glm::angle(newOrientation, up) <= 3.0f) and (glm::angle(newOrientation, up) >= 0.5f))
			orientation = newOrientation;

		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		glfwSetCursorPos(window, (width / 2), height / 2);
	}
}

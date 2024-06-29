#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>


class Camera
{
public:
	Camera(glm::vec3 camPos=glm::vec3(0.f,0.f,3.f), float FOV = 50.f, float nearClip = 0.1f, float farClip = 100.f);

	void update(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void setAspectRatio(float aspect_ratio);

	glm::vec3 getPosition() const;
	glm::mat4 getProjMatrix() const;
	glm::mat4 getViewMatrix() const;

private:
	void process_inputs(GLFWwindow* window);

	float FOV, nearClip, farClip;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraDirection = glm::vec3(0.f, 0.f, 0.f);

	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	float yaw = -90.f;
	float pitch = 1.f;
	float lastX = 400, lastY = 300;

	bool mouse_hidden = false;
	bool first_mouse = true;

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
};
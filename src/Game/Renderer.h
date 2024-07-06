#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

#include "Camera.h"
#include "Skybox.h"
#include "Model.h"


class Renderer
{

public:
	void Init();
	void Update();
	void Draw(GLFWwindow* window, Camera cam);

	~Renderer();

private:
	Skybox* skybox;
	Model* monkey;
};
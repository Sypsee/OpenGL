#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

#include "Camera.h"
#include "Chunk.h"


class Renderer
{

public:
	void Init();
	void Update();
	void Draw(GLFWwindow* window, Camera cam);

private:
	std::unordered_map<glm::vec3, Chunk> m_chunks;
};
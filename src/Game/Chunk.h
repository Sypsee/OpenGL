#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <unordered_map>

#include "Cube.h"

class Chunk
{
public:
	Chunk(glm::vec3 pos, glm::vec3 size);

	void Draw(glm::mat4 proj, glm::mat4 view, glm::vec3 camPos);

private:
	std::unordered_map<glm::vec3, Cube> m_cubes;

	glm::vec3 m_pos, m_size;

	Texture m_texture;
	Shader m_shader;
};
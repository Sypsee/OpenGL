#pragma once

#include "Texture.h"
#include "Shader.h"

class Skybox
{
public:
	Skybox(const char* texPath, const char* fragPath, const char* vertPath);
	
	void Draw(glm::mat4 proj, glm::mat4 view);

private:
	unsigned int VAO;
	glm::mat4 m_Model = glm::mat4(1.f);

	Texture m_Texture;
	Shader m_Shader;
};
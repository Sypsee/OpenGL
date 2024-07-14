#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "FrameBuffer.h"
#include "Shader.h"

class Light
{
public:
	glm::vec3 lightPos;
	Light(glm::vec3 pos, float nearPlane = 1.0f, float farPlane = 7.5f, glm::vec3 color = glm::vec3(1));

	inline glm::mat4 getLightSpaceMat() { return lightSpaceMat; }
	inline void bindDepthTex() { glActiveTexture(GL_TEXTURE7); glBindTexture(GL_TEXTURE_2D, depthMap); }

private:
	glm::mat4 view, proj, model, lightSpaceMat = glm::mat4(1.0f);
	FrameBuffer *frameBuffer;
	Shader lightShader;

	unsigned int depthMap;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
};
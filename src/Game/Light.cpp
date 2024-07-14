#include "Light.h"

Light::Light(glm::vec3 pos, float nearPlane, float farPlane, glm::vec3 color)
	:lightPos(pos), lightShader("res/shaders/light.frag", "res/shaders/light.vert")
{
	proj = glm::ortho(-10.f, 10.f, -10.f, 10.f, nearPlane, farPlane);
	view = glm::lookAt(lightPos,
					   glm::vec3(0.0f, 0.0f, 0.0f),
					   glm::vec3(0.0f, 1.0f, 0.0f));

	lightSpaceMat = proj * view;
	model = glm::translate(model, lightPos);

	glGenTextures(1, &depthMap);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	frameBuffer = new FrameBuffer(depthMap);

	lightShader.Bind();
	lightShader.setMat4("lightSpaceMatrix", lightSpaceMat);
	lightShader.setMat4("model", model);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	frameBuffer->Bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	frameBuffer->UnBind();
	glViewport(0, 0, 800, 600);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, depthMap);
}

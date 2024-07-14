#pragma once

#include <glad/glad.h>


class FrameBuffer
{
public:
	FrameBuffer(unsigned int depthMap=0, unsigned int colorAtt=0);

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_FBO = 0;
};
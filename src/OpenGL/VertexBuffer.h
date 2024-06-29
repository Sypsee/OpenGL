#pragma once

#include <glad/glad.h>


class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int vertexBufferID=0;
};
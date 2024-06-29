#pragma once
#include <iostream>
#include <stb_image/stb_image.h>
#include <glad/glad.h>


class Texture
{
public:
	Texture(const char* path, GLenum textureIndex=GL_TEXTURE0, GLenum targetTexType=GL_TEXTURE_2D, const bool isCubemap=false);
	void Bind() const;

private:
	unsigned int texId;
	GLenum targetTexType;
	GLenum textureIndex;
};
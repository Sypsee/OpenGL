#pragma once
#include <iostream>
#include <stb_image/stb_image.h>
#include <glad/glad.h>


class Texture
{
public:
	Texture(const char* path);
	void Bind() const;

private:
	unsigned int texId;
};
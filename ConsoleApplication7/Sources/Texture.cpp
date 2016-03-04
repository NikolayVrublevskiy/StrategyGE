#include "../Headers/Texture.h"
#include "../Utils/TGA.h"
#include <iostream>

Texture::Texture()
{
}

int Texture::Init(const char * _filePath, int _ID)
{
	m_ID = _ID;
	glGenTextures(1, &m_textureHandle);
	glBindTexture(GL_TEXTURE_2D, m_textureHandle);
	int width, height, bpp;

	char * bufferTGA = LoadTGA(_filePath, &width, &height, &bpp);
	if (bufferTGA == nullptr)
	{
		printf("Can't open file with texture!\n");
		return -4;
	}
	else
	{
		if (bpp == 24)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferTGA);
		}

		// free the client memory
		delete[] bufferTGA;

	}
	return 0;
}

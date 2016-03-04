#pragma once
// Include GLEW
#include <GL/glew.h>

class Texture
{
public:
	Texture();
	int Init(const char * _filePath, int _ID);
	//void InitCubeTexture(const char* _fileName, int _ID);
	//char* ExtractFace(char* _wholeTexture, int _width, int _height, int _bpp, int _face);
	GLint m_wrapMode;
	GLuint m_textureHandle;
	int m_ID;
	int width, height, bpp;
};

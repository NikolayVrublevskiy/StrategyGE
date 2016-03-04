#pragma once
#include "Headers/"
// Include GLEW
#include <GL/glew.h>

class  Font
{
public:
	Font();
	~Font();

private:

	GLuint m_fontId;
	GLuint m_fontVBO;
	GLuint m_fontUV;
};
#pragma once
#include <string>
// Include GLEW
#include <GL/glew.h>
#include "../Utils/Shader.h"


class  Font
{
public:
	Font();
	~Font();

	void Init(std::string fontPath, std::string vsPath, std::string fsPath);

	void PrintText(const char * text, int x, int y, int size);

private:

	GLuint LoadFont(const char * imagepath);

private:

	GLuint m_fontId;
	GLuint m_fontVBO;
	GLuint m_fontUV;
	Shader m_shader;
	GLuint m_fontUniformId;
};
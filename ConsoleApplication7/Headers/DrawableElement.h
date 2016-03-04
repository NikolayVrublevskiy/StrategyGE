#pragma once
#include <string>
#include "Texture.h"
#include "../Utils/Shader.h"

class DrawableElement
{

public:

	DrawableElement();
	virtual ~DrawableElement();

	virtual void Init(std::string modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath) = 0;

	virtual void Draw() = 0;
protected:

	GLuint m_VBO;
	GLuint m_IBO;

	Shader m_shader;
	Texture m_texture;

	int m_indicesCount;
	int m_verticiesCount;

	bool m_isInited;
};
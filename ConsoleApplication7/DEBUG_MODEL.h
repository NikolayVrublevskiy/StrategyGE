#pragma once
#pragma once
#include <string>
#include "Headers/DrawableElement.h"

// Include GLM
#include <glm/glm.hpp>

class DEBUG_Model3D : public DrawableElement
{

public:

	DEBUG_Model3D();
	~DEBUG_Model3D();

	void Init(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath);
	void Init(std::string modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath) override;

	void Init(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath);

	void Draw() override;
};
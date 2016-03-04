#pragma once
#include <string>
#include "../Headers/DrawableElement.h"
#include "../Headers/Map.h"

class Element2D : public DrawableElement
{

public:

	Element2D();
	~Element2D();

	void Init(std::string modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath) override;
	void InitCircle(std::string _vShaderPath, std::string _fShaderPath);
	void InitLine(std::string _vShaderPath, std::string _fShaderPath);
	void InitGrid(std::vector<std::vector<Cell>> cells,  std::string _vShaderPath, std::string _fShaderPath);

	void Draw() override;
	void DrawCircle(float x, float y);
	void DrawGrid();

	void SetIsInited(bool value);
};
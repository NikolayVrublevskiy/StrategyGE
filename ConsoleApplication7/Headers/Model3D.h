#pragma once
#include <string>
#include "../Headers/DrawableElement.h"

class Model3D : public DrawableElement
{

public:

	Model3D();
	~Model3D();

	void Init(std::string modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath) override;

	void Draw() override;

	void SetXCoord(float _xCoord);
	void SetYCoord(float _yCoord);

	void IncreaseXCoord(float _xCoord);
	void IncreaseYCoord(float _yCoord);

	float GetXCoord() const;
	float GetYCoord() const;

	void RecalculatePosition();

private:

	float m_xCoord;
	float m_yCoord;

	bool m_positionChanged;
};
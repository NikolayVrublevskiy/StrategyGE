#pragma once

#include <string>

class Model3D;

class Unit
{
public:

	Unit();
	~Unit();

	void Init(std::string modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath);

private:

	int			m_hp;
	int			m_mp;
	int			m_attackRange;
	float		m_attackSpeed;
	float		m_moveSpeed;
	bool		m_isSelected;

	Model3D*	m_model;
};

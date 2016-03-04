#include "Unit.h"
#include "Headers/Model3D.h"
/*
int			m_hp;
int			m_mp;
int			m_attackRange;
double		m_attackSpeed;
double		m_moveSpeed;
bool		m_isSelected;

Model3D*	m_model;
*/
Unit::Unit()
:m_hp(0),
 m_mp(0),
 m_attackRange(0),
 m_attackSpeed(0),
 m_moveSpeed(1.0f),
 m_isSelected(false),
 m_model(new Model3D())
{
}

Unit::~Unit()
{
	if (m_model)
		delete m_model;
}

void Unit::Init(std::string modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath)
{
	m_model->Init(modelPath, _texturePath, _vShaderPath, _fShaderPath);
}

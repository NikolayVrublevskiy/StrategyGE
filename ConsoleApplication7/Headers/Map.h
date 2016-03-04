#pragma once

#include "Model3D.h"
#include <vector>

class Cell
{

private:

	float	m_xCoord;
	float	m_yCoord;
	bool	m_isFree;

	Model3D m_model;

public:

	Cell();
	Cell(float _xCoord, float _yCoord, bool _isFree);

	float GetXCoord() const;
	float GetYCoord() const;

	void SetModel(Model3D _model);
	void SetModel(std::string _modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath);
};

class Map
{

public:
	Map();
	void Init(int _weight, int _height, Model3D _model); 
	void Init(int _weight, int _height, std::string _modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath);

	float GetWeight() const;
	float GetHeight() const;

	void SetWeight(int _weight);
	void SetHeight(int _height);

	std::vector<std::vector<Cell> > GetCells() const;

	void Draw();

private:
	float m_weight;
	float m_height;

	std::vector<std::vector<Cell> > m_cells;

	Model3D m_model;
};
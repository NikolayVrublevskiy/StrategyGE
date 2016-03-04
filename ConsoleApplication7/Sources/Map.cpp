
#include "../Headers/Map.h"

const float cell_size = 0.25;

Cell::Cell()
:m_xCoord(0),
 m_yCoord(0),
m_isFree(false)
{}

Cell::Cell(float _xCoord, float _yCoord, bool _isFree)
:m_xCoord(_xCoord),
 m_yCoord(_yCoord),
 m_isFree(_isFree)
{}

void Cell::SetModel(Model3D _model)
{
	m_model = _model;
}

void Cell::SetModel(std::string _modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath)
{
	m_model.Init(_modelPath, _texturePath, _vShaderPath, _fShaderPath);
}

float Cell::GetXCoord() const
{
	return m_xCoord;
}

float Cell::GetYCoord() const
{
	return m_yCoord;
}

Map::Map()
:m_height(0),
 m_weight(0)
{
}

void Map::Init(int _weight, int _height, Model3D _model)
{
	m_height = _height;
	m_weight = _weight;
	m_model = _model;

	for (float i = 0; i <= m_height; i + m_height / cell_size)
	{
		for (float j = 0; j <= m_weight; j+ m_weight / cell_size)
		{
			m_cells[i][j] = Cell(i, j, false);
		}
	}
}

void Map::Init(int _weight, int _height, std::string _modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath)
{
	m_height = _height;
	m_weight = _weight;
	m_model.Init(_modelPath, _texturePath, _vShaderPath, _fShaderPath);
	
	m_cells.resize((m_height / cell_size) + 1);
	for (int i = 0; i <= m_height / cell_size; i++)
	{
		m_cells[i].resize((m_height / cell_size) + 1);
		for (int j = 0; j <= m_weight / cell_size; j++)
		{
			
			m_cells[i][j] = Cell(i * cell_size, j * cell_size, false);
		}
	}
}

float Map::GetWeight() const
{
	return m_weight;
}

float Map::GetHeight() const
{
	return m_height;
}

void Map::SetWeight(int _weight)
{
	m_weight = _weight;
}

void Map::SetHeight(int _height)
{
	m_height = _height;
}

void Map::Draw()
{
	m_model.Draw();
}

std::vector<std::vector<Cell> > Map::GetCells() const
{
	return m_cells;
}

#include "../Headers/Model3D.h"
#include "../Headers/FileReader.h"
#include "../Headers/Vertex.h"
#include "../Headers/Camera.h"
#include <vector>

extern glm::mat4 world;

Model3D::Model3D()
:m_xCoord(0),
 m_yCoord(0),
 m_positionChanged(false)
{
}

Model3D::~Model3D()
{
}

void Model3D::Init(std::string _modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath)
{
	FileReader::GetInstance()->OpenFile(_modelPath);

	int vertCount = 0;
	FileReader::GetInstance()->ReadInt("NrVertices: %d", vertCount);
	Vertex * verticesData = new Vertex[vertCount];
	
	Vector3 tmp;
	for (int i = 0; i < vertCount; i++)
	{
		FileReader::GetInstance()->ReadFloat5("%*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];", 
											verticesData[i].pos.x, verticesData[i].pos.y, verticesData[i].pos.z, verticesData[i].uv.x, verticesData[i].uv.y
											);
	}

	FileReader::GetInstance()->ReadInt("\nNrIndices: %d", m_indicesCount);
	GLushort * indicesData = new GLushort[m_indicesCount];

	for (int i = 0; i < m_indicesCount / 3; i++)
	{
		FileReader::GetInstance()->ReadUShort3("%*d.    %hu,    %hu,    %hu", indicesData[i + i * 2], indicesData[(i + 1) + i * 2], indicesData[(i + 2) + i * 2]);
	}

	// Buffer object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertCount*sizeof(Vertex), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] verticesData;

	// Index buffer
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount*sizeof(GLushort), indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	delete[] indicesData;

	m_shader.LoadShaders(_vShaderPath.c_str(), _fShaderPath.c_str());
	m_texture.Init(_texturePath.c_str(), 0);

	m_isInited = true;
}



void Model3D::Draw()
{
	if (!m_isInited)
		return;

	glUseProgram(m_shader.ProgramID);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.m_textureHandle);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (m_shader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader.positionAttribute);
		glVertexAttribPointer(m_shader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (m_shader.UV != -1)
	{
		glEnableVertexAttribArray(m_shader.UV);
		glVertexAttribPointer(m_shader.UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 3));
	}

	glm::mat4 matrix;
	matrix.SetTranslation(m_xCoord, 0, m_yCoord);

	if (m_shader.WVPUniform != -1)
	{
		glUniformMatrix4fv(m_shader.WVPUniform, 1, false, (GLfloat*)& (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * matrix));
	}
	GLuint uniformLocation = glGetUniformLocation(m_shader.ProgramID, "myTextureSampler");
	glUniform1i(uniformLocation, 0);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_SHORT, 0);

	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model3D::SetXCoord(float _xCoord)
{
	m_xCoord = _xCoord;
	m_positionChanged = true;
}

void Model3D::SetYCoord(float _yCoord)
{
	m_yCoord = _yCoord;
	m_positionChanged = true;
}

void Model3D::IncreaseXCoord(float _xCoord)
{
	m_xCoord += _xCoord;
}

void Model3D::IncreaseYCoord(float _yCoord)
{
	m_yCoord += _yCoord;
}

float Model3D::GetXCoord() const
{
	return m_xCoord;
}

float Model3D::GetYCoord() const
{
	return m_yCoord;
}

void Model3D::RecalculatePosition()
{

}

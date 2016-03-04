#include "../Headers/Element2D.h"
#include "../Headers/FileReader.h"
#include "../Headers/Vertex.h"
#include "../Headers/Camera.h"
#include <vector>

#define DEGREES_TO_RADIANS(x) (3.14159265358979323846 * x / 180.0)

extern glm::mat4 world;

Element2D::Element2D()
{
}

Element2D::~Element2D()
{
}

void Element2D::Init(std::string _modelPath, std::string _texturePath, std::string _vShaderPath, std::string _fShaderPath)
{
	FileReader::GetInstance()->OpenFile(_modelPath);

	int vertCount = 0;
	FileReader::GetInstance()->ReadInt("NrVertices: %d", vertCount);
	Vertex * verticesData = new Vertex[vertCount];
	
	Vector3 tmp;
	for (int i = 0; i < vertCount; i++)
	{
		FileReader::GetInstance()->ReadFloat5("%*d. pos:[%f, %f, %f]; uv:[%f, %f];", 
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

GLfloat vertices[720];

void Element2D::InitCircle(std::string _vShaderPath, std::string _fShaderPath)
{
	for (int i = 0; i < 720; i += 2) {
		// x value
		vertices[i] = (cos(DEGREES_TO_RADIANS(i)) * 1) / 3.0f;
		// y value
		vertices[i + 1] = (sin(DEGREES_TO_RADIANS(i)) * 1) / 3.0f;
	}

	// Buffer object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_shader.LoadShaders(_vShaderPath.c_str(), _fShaderPath.c_str());
}

void Element2D::InitGrid(std::vector<std::vector<Cell>> cells, std::string _vShaderPath, std::string _fShaderPath)
{
	int size = cells.size() * 4;
	Vertex* verts = new Vertex[size/**/];

	//GLushort indicesData[] = { 0,1,1,2,2,3,3,0, };
	GLushort* indicesData = new GLushort[size];

	size_t colLastElem = cells.size() - 1;
	size_t rowLastElem = cells[0].size() - 1;

	Cell topLeft = cells[0][0];
	Cell topRight = cells[colLastElem][0];
	Cell botLeft = cells[0][rowLastElem];
	Cell botRight = cells[colLastElem][rowLastElem];

	int idx = 0;
	for (int i = 0; i < size / 4; i++)
	{
		verts[idx] = Vertex{ Vector3(cells[0][i].GetXCoord(), cells[0][i].GetYCoord(), 0.0), Vector2(0.0, 0.0) };
		verts[idx + 1] = Vertex{ Vector3(cells[colLastElem][i].GetXCoord(), cells[colLastElem][i].GetYCoord(), 0.0), Vector2(0.0, 0.0) };

		verts[idx + 2] = Vertex{ Vector3(cells[i][0].GetXCoord(), cells[i][0].GetYCoord(), 0.0), Vector2(0.0, 0.0) };
		verts[idx + 3] = Vertex{ Vector3(cells[i][rowLastElem].GetXCoord(), cells[i][rowLastElem].GetYCoord(), 0.0), Vector2(0.0, 0.0) };

		idx += 4;
	}

	for (GLushort i = 0; i < size; i++)
	{
		indicesData[i] = i;
	}

	// Buffer object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	m_indicesCount = size;

	// Index buffer
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLushort), indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_shader.LoadShaders(_vShaderPath.c_str(), _fShaderPath.c_str());
}

void Element2D::DrawGrid()
{
	// Bind shader
	glUseProgram(m_shader.ProgramID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	if (m_shader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_shader.positionAttribute);
		glVertexAttribPointer(m_shader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	glm::mat4 matrix;
	matrix.SetTranslation(0.0, 0.001, 0.0);
	matrix.SetRotationX(DEGREES_TO_RADIANS(90));

	if (m_shader.WVPUniform != -1)
	{
		glUniformMatrix4fv(m_shader.WVPUniform, 1, false, (GLfloat*)& (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * matrix));
	}

	// Draw call
	glDrawElements(GL_LINES, m_indicesCount, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
}

void Element2D::DrawCircle(float x, float y)
{
	if (!m_isInited)
		return;

	// Bind shader
	glUseProgram(m_shader.ProgramID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glm::mat4 matrix;
	//matrix.SetTranslation(x, 0.001, y);
	//matrix.SetRotationZ(DEGREES_TO_RADIANS(90));

	if (m_shader.WVPUniform != -1)
	{
		glUniformMatrix4fv(m_shader.WVPUniform, 1, false, (GLfloat*)& (Camera::GetInstance()->GetProjectionMatrix() * Camera::GetInstance()->GetViewMatrix() * matrix));
	}

	// Draw call
	glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(vertices) / sizeof(GLfloat));

	glDisableVertexAttribArray(0);
}

//GLfloat line_vertices[2];
Vertex line_vertices[4];
//GLushort indicesData[] = { 0,1,1,2,2,3,3,0 };
GLushort indicesData[] = { 0,1,2,3 };

void Element2D::InitLine(std::string _vShaderPath, std::string _fShaderPath)
{

	//for (int i = 0; i < 1; i += 2) {
		
		line_vertices[0] = Vertex{ Vector3(0.0, 0.0, 0.0), Vector2(0.0, 0.0) };
		line_vertices[1] = Vertex{ Vector3(0.0, 0.9, 0.0), Vector2(0.0, 0.0) };
		line_vertices[2] = Vertex{ Vector3(0.9, 0.9, 0.0), Vector2(0.0, 0.0) };
		line_vertices[3] = Vertex{ Vector3(0.9, 0.0, 0.0), Vector2(0.0, 0.0) };

		//line_vertices[ 4] = 0;
	//}

	// Buffer object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

	// Index buffer
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	m_shader.LoadShaders(_vShaderPath.c_str(), _fShaderPath.c_str());
}

void Element2D::Draw()
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
	GLuint uniformLocation = glGetUniformLocation(m_shader.ProgramID, "myTextureSampler");
	glUniform1i(uniformLocation, 0);

	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_SHORT, 0);

	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Element2D::SetIsInited(bool value)
{
	m_isInited = value;
}
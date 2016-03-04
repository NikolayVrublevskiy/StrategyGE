#include "../Headers/FileReader.h"
#include <stdio.h>

FileReader::FileReader()
: m_file(nullptr)
{
}

FileReader::~FileReader()
{
}

void FileReader::ReadVector3(std::string _tmpl, Vector3 & _value)
{
	fscanf_s(m_file, _tmpl.c_str(), &_value.x, &_value.y, &_value.z);
}

void FileReader::ReadFloat(std::string _tmpl, float & _value)
{
	fscanf_s(m_file, _tmpl.c_str(), &_value);
}

void FileReader::ReadFloat5(std::string _tmpl, float & _value1, float & _value2, float & _value3, float & _value4, float & _value5)
{
	fscanf_s(m_file, _tmpl.c_str(), &_value1, &_value2, &_value3, &_value4, &_value5);
}

void FileReader::ReadInt(std::string _tmpl, int & _value)
{
	fscanf_s(m_file, _tmpl.c_str(), &_value);
}

void FileReader::ReadInt3(std::string _tmpl, int & _value1, int & _value2, int & _value3)
{
	fscanf_s(m_file, _tmpl.c_str(), &_value1, &_value2, &_value3);
}

void FileReader::ReadUShort3(std::string _tmpl, GLushort & _value1, GLushort & _value2, GLushort & _value3)
{
	fscanf_s(m_file, _tmpl.c_str(), &_value1, &_value2, &_value3);
}

int FileReader::OpenFile(std::string _path)
{
	fopen_s(&m_file, _path.c_str(), "rb");

	if (!m_file)
		return 0;

	return 1;
}

FILE * FileReader::GetFile() const
{
	return nullptr;
}

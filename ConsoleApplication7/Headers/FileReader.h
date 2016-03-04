#pragma once
#include "ISingleton.h"
#include "../Utils/utilsMath.h"
#include <string>

class FileReader : public ISingleton<FileReader>
{
	friend class ISingleton<FileReader>;

public:

	FileReader();
	~FileReader();

	void ReadVector3(std::string _tmpl, Vector3 & value);
	void ReadFloat(std::string _tmpl, float & value);
	void ReadFloat5(std::string _tmpl, float & _value1, float & _value2, float & _value3, float & _value4, float & _value5);
	void ReadInt(std::string _tmpl, int & value);
	void ReadInt3(std::string _tmpl, int & value1, int & value2, int & value3);
	void ReadUShort3(std::string _tmpl, GLushort & value1, GLushort & value2, GLushort & value3);

	int OpenFile(std::string _path);

	FILE* GetFile() const;

private:

	FILE * m_file;

};
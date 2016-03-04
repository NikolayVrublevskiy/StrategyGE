#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
// Include GLEW

class Shader
{
public:
	GLuint ProgramID;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint WVPUniform;
	GLint UV;

	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	~Shader();
};

#endif

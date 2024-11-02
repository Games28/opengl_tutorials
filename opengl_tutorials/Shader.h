#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>


class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();

	void UseShader();
	void ClearShader();
private:
	GLuint shaderID, uniformProjection, uniformModel;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderTypes);

};
#endif // !SHADER_H



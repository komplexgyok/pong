#pragma once

#include <fstream>
#include <glad/glad.h>
#include <string>
#include <vector>

/***********************************************************************************************************************
 * Shader class.
 *
 * Representation of a shader. It supports vertex and fragment shaders. Contains utility methods to manipulate the
 * shader uniform values.
 **********************************************************************************************************************/
class Shader
{
public:
	Shader(const std::string &vertexSourceFile, const std::string &fragmentSourceFile);
	~Shader();

	void use() const;

private:
	static std::string readFile_(const std::string &filePath);
	static unsigned int compile_(const std::string &vertexSource, const std::string &fragmentSource);

	unsigned int id_;   // Shader program object ID
};

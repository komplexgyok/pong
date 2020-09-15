#pragma once

#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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

	// Uniform setters
	void setInteger(const std::string &name, int value) const;
	void setVector4(const std::string &name, const glm::vec4 &vector) const;
	void setMatrix4(const std::string &name, const glm::mat4 &matrix) const;
	void setUniform1iv(const std::string &name, int *value, int count) const;

private:
	static std::string readFile_(const std::string &filePath);
	static unsigned int compile_(const std::string &vertexSource, const std::string &fragmentSource);

	unsigned int id_;   // Shader program object ID
};

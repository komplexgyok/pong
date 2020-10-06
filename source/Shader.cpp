#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <vector>
#include "Shader.h"

/***********************************************************************************************************************
 * Constructor.
 **********************************************************************************************************************/
Shader::Shader()
	: id_ {0}
{}

/***********************************************************************************************************************
 * Compiles the GLSL shader sources and links them into a shader program.
 *
 * @param const std::string &vertexSource     Vertex shader source code.
 * @param const std::string &fragmentSource   Fragment shader source code.
 *
 * @return void
 **********************************************************************************************************************/
void Shader::compile(const std::string &vertexSource, const std::string &fragmentSource)
{
	unsigned int shaders[2];

	// Create and compile the vertex shader
	shaders[0] = glCreateShader(GL_VERTEX_SHADER);
	const char *vSource = vertexSource.c_str();
	glShaderSource(shaders[0], 1, &vSource, nullptr);
	glCompileShader(shaders[0]);

	// Create and compile the fragment shader
	shaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fSource = fragmentSource.c_str();
	glShaderSource(shaders[1], 1, &fSource, nullptr);
	glCompileShader(shaders[1]);

	// Check for shader compile errors
	for (auto shader : shaders) {
		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

		if (!isCompiled) {
			int maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(shader);
			throw std::runtime_error("Failed to compile shader");
		}
	}

	// Create the shader program
	id_ = glCreateProgram();

	// Attach the compiled shaders to the program object
	for (auto shader : shaders) {
		glAttachShader(id_, shader);
	}

	// Link the shaders
	glLinkProgram(id_);

	// Check for linking errors
	int isLinked = 0;
	glGetProgramiv(id_, GL_LINK_STATUS, &isLinked);

	if (!isLinked) {
		int maxLength = 0;
		glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(id_, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(id_);

		for (auto shader : shaders) {
			glDeleteShader(shader);
		}

		throw std::runtime_error("Failed to link shaders");
	}

	// Delete the shader objects
	for (auto shader : shaders) {
		glDetachShader(id_, shader);
		glDeleteShader(shader);
	}
}

/***********************************************************************************************************************
 * Deletes the shader.
 *
 * @return void
 **********************************************************************************************************************/
void Shader::destroy() const
{
	glDeleteProgram(id_);
}

/***********************************************************************************************************************
 * Use the current shader program.
 *
 * @return void
 **********************************************************************************************************************/
void Shader::use() const
{
	glUseProgram(id_);
}

/***********************************************************************************************************************
 * Sets an integer uniform inside the shader.
 *
 * @param const std::string &name   Name of the uniform to set.
 * @param int value                 Value.
 *
 * @return void
 **********************************************************************************************************************/
void Shader::setInteger(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

/***********************************************************************************************************************
 * Sets a 4D vector uniform inside the shader.
 *
 * @param const std::string &name   Name of the uniform to set.
 * @param const glm::mat4 &vector   Value.
 *
 * @return void
 **********************************************************************************************************************/
void Shader::setVector4(const std::string &name, const glm::vec4 &vector) const
{
	glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, glm::value_ptr(vector));
}

/***********************************************************************************************************************
 * Sets a 4D matrix uniform inside the shader.
 *
 * @param const std::string &name   Name of the uniform to set.
 * @param const glm::mat4 &matrix   Value.
 *
 * @return void
 **********************************************************************************************************************/
void Shader::setMatrix4(const std::string &name, const glm::mat4 &matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

/***********************************************************************************************************************
 * Sets an integer array uniform inside the shader.
 *
 * @param const std::string &name   Name of the uniform to set.
 * @param int *value                Value.
 * @param int count                 Array element count.
 *
 * @return void
 **********************************************************************************************************************/
void Shader::setUniform1iv(const std::string &name, int *value, int count) const
{
	glUniform1iv(glGetUniformLocation(id_, name.c_str()), count, value);
}

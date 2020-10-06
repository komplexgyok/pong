#pragma once

#include <glm/glm.hpp>
#include <string>

/***********************************************************************************************************************
 * Shader class.
 *
 * Representation of a shader. It supports vertex and fragment shaders. Contains utility methods to manipulate the
 * shader uniform values.
 **********************************************************************************************************************/
class Shader
{
public:
	// Constructor
	Shader();

	void compile(const std::string &vertexSource, const std::string &fragmentSource);
	void destroy() const;
	void use() const;

	// Getter
	[[nodiscard]] inline unsigned int getId() const { return id_; }

	// Uniform setters
	void setInteger(const std::string &name, int value) const;
	void setVector4(const std::string &name, const glm::vec4 &vector) const;
	void setMatrix4(const std::string &name, const glm::mat4 &matrix) const;
	void setUniform1iv(const std::string &name, int *value, int count) const;

private:
	unsigned int id_;   // Shader program object ID
};

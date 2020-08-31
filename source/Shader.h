#pragma once

#include <array>
#include <string>
#include <unordered_map>

// Possible shader types
enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

// Representation of an OpenGL shader
class Shader
{
public:
	// Constructor and destructor
	Shader(const std::string &filepath);
	~Shader();

	void use() const;

private:
	static std::string readFile_(const std::string &filePath);
	static std::unordered_map<ShaderType, std::string> parse_(const std::string &source);
	static std::array<unsigned int, 2> compile_(const std::unordered_map<ShaderType, std::string> &shaderSources);
	static unsigned int create_(const std::array<unsigned int, 2> &shaders);

	unsigned int id_;   // Shader program object ID
};

#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <vector>
#include "Shader.h"

/***********************************************************************************************************************
 * Constructor.
 *
 * @param const std::string &filepath   Path of the GLSL source file.
 **********************************************************************************************************************/
Shader::Shader(const std::string &filepath)
	: id_ {0}
{
	// Read the GLSL file
	std::string fileContent = readFile_(filepath);
	// Parse the file into 2 separate shader sources
	std::unordered_map<ShaderType, std::string> shaderSources = parse_(fileContent);
	// Compile the shaders
	std::array<unsigned int, 2> shaders = compile_(shaderSources);
	// Create the shader program object
	id_ = create_(shaders);
}

/***********************************************************************************************************************
 * Destructor.
 **********************************************************************************************************************/
 Shader::~Shader()
{
 	glDeleteProgram(id_);
}

/***********************************************************************************************************************
 * Use the current shader program.
 **********************************************************************************************************************/
void Shader::use() const
{
	glUseProgram(id_);
}

/***********************************************************************************************************************
 * Reads the given file's content into a string.
 *
 * @param const std::string &filepath   Path of the file to read in.
 *
 * @return std::string   File content.
 **********************************************************************************************************************/
std::string Shader::readFile_(const std::string &filepath)
{
	std::string fileContent;
	std::ifstream sourceFile(filepath, std::ios::in | std::ios::binary);

	if (!sourceFile) {
		throw std::runtime_error("Failed to open shader file");
	}

	sourceFile.seekg(0, std::ios::end);
	size_t size = sourceFile.tellg();

	if (size == -1) {
		throw std::runtime_error("Failed to read shader file");
	}

	fileContent.resize(size);
	sourceFile.seekg(0, std::ios::beg);
	sourceFile.read(&fileContent[0], size);

	return fileContent;
}

/***********************************************************************************************************************
 * Parses the shader source file and splits it into vertex shader and fragment shader sources.
 *
 * @param const std::string &source   The combined shader source string.
 *
 * @return std::unordered_map<ShaderType, std::string>   Unordered map containing the 2 separate shader sources.
 **********************************************************************************************************************/
std::unordered_map<ShaderType, std::string> Shader::parse_(const std::string &source)
{
	std::unordered_map<ShaderType, std::string> shaderSources;
	ShaderType type = ShaderType::NONE;
	std::stringstream buffer[2];
	std::stringstream stream(source);
	std::string line;

	while (getline(stream, line)) {
		if (line.find("#VertexShader") != std::string::npos) {
			type = ShaderType::VERTEX;
		}
		else if (line.find("#FragmentShader") != std::string::npos) {
			type = ShaderType::FRAGMENT;
		}
		else {
			buffer[static_cast<int>(type)] << line << '\n';
		}
	}

	shaderSources[ShaderType::VERTEX]   = buffer[0].str();
	shaderSources[ShaderType::FRAGMENT] = buffer[1].str();

	return shaderSources;
}

/***********************************************************************************************************************
 * Compiles the given GLSL shader sources.
 *
 * @param const std::unordered_map<ShaderType, std::string> &shaderSources   GLSL shader sources.
 *
 * @return std::array<unsigned int, 2>   Array containing the shader object IDs.
 **********************************************************************************************************************/
std::array<unsigned int, 2> Shader::compile_(const std::unordered_map<ShaderType, std::string> &shaderSources)
{
	std::array<unsigned int, 2> shaders{};
	int index = 0;

	for (auto &shaderSource : shaderSources) {
		ShaderType type    = shaderSource.first;
		const char *source = shaderSource.second.c_str();

		unsigned int shader = 0;

		// Create the shader
		switch (type) {
			case ShaderType::VERTEX:
				shader = glCreateShader(GL_VERTEX_SHADER);
				break;

			case ShaderType::FRAGMENT:
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				break;

			default:
				break;
		}

		// Compile the shader
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		// Check for shader compile errors
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

		shaders[index++] = shader;
	}

	return shaders;
}

/***********************************************************************************************************************
 * Creates an OpenGL shader program object from the shaders.
 *
 * @param const std::array<unsigned int, 2> &shaders   Array of shader object IDs.
 *
 * @return unsigned int   ID of the OpenGL shader program object.
 **********************************************************************************************************************/
unsigned int Shader::create_(const std::array<unsigned int, 2> &shaders)
{
	// Create the shader program
	unsigned int program = glCreateProgram();

	// Attach the compiled shaders to the program object
	for (auto shader : shaders) {
		glAttachShader(program, shader);
	}

	// Link the shaders
	glLinkProgram(program);

	// Check for linking errors
	int isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

	if (!isLinked) {
		int maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(program);

		for (auto shader : shaders) {
			glDeleteShader(shader);
		}

		throw std::runtime_error("Failed to link shaders");
	}

	// Delete the shader objects
	for (auto shader : shaders) {
		glDetachShader(program, shader);
		glDeleteShader(shader);
	}

	return program;
}

#include "Shader.h"

/***********************************************************************************************************************
 * Constructor. Creates a shader program from the shader source codes.
 *
 * @param const std::string &vertexSourceFile     Path of the vertex shader source code file.
 * @param const std::string &fragmentSourceFile   Path of the fragment shader source code file.
 **********************************************************************************************************************/
Shader::Shader(const std::string &vertexSourceFile, const std::string &fragmentSourceFile)
	: id_ {0}
{
	// Read the vertex and fragment shader source codes from file
	std::string vertexSource   = readFile_(vertexSourceFile);
	std::string fragmentSource = readFile_(fragmentSourceFile);

	// Compile and link the shaders into a shader program
	id_ = compile_(vertexSource, fragmentSource);
}

/***********************************************************************************************************************
 * Destructor. Deletes the shader program.
 **********************************************************************************************************************/
 Shader::~Shader()
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
 * Compiles the GLSL shader sources and links them into a shader program.
 *
 * @param const std::string &vertexSource     Vertex shader source code.
 * @param const std::string &fragmentSource   Fragment shader source code.
 *
 * @return unsigned int   Shader program ID.
 **********************************************************************************************************************/
unsigned int Shader::compile_(const std::string &vertexSource, const std::string &fragmentSource)
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

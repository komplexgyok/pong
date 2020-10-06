#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "ResourceManager.h"

// Instantiate static variables
std::map<std::string, Shader*> ResourceManager::shaders;
std::map<std::string, Texture*> ResourceManager::textures;
std::map<std::string, Font*> ResourceManager::fonts;

/***********************************************************************************************************************
 * Loads a shader from the given source files and stores it in a map.
 *
 * @param const std::string &vertexShaderFile     Path of the vertex shader source file.
 * @param const std::string &fragmentShaderFile   Path of the fragment shader source file.
 * @param const std::string &name                 Unique name for identifying the shader.
 *
 * @return Shader*   The loaded shader.
 **********************************************************************************************************************/
Shader * ResourceManager::loadShader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile, const std::string &name)
{
	// Read the source files
	std::string vertexShaderSource   = readFile_(vertexShaderFile);
	std::string fragmentShaderSource = readFile_(fragmentShaderFile);

	// Create and compile the shader
	Shader *shader = new Shader();
	shader->compile(vertexShaderSource, fragmentShaderSource);

	// Store the shader
	shaders[name] = shader;
	return shader;
}

/***********************************************************************************************************************
 * Shader getter.
 *
 * @param const std::string &name   Name of the shader.
 *
 * @return Shader*   Requested shader.
 **********************************************************************************************************************/
Shader * ResourceManager::getShader(const std::string &name)
{
	return shaders[name];
}

/***********************************************************************************************************************
 * Loads a texture from the given image file and stores it in a map.
 *
 * @param const std::string &textureFile   Path of the image file.
 * @param const std::string &name          Unique name for identifying the texture.
 *
 * @return Texture*   The loaded texture.
 **********************************************************************************************************************/
Texture * ResourceManager::loadTexture(const std::string &textureFile, const std::string &name)
{
	// Load the image file
	int width, height, channels;
	unsigned char *buffer = stbi_load(textureFile.c_str(), &width, &height, &channels, 4);

	if (!buffer) {
		throw std::runtime_error("Failed to load image");
	}

	// Generate the texture
	Texture *texture = new Texture();
	texture->generate(buffer, width, height, GL_RGBA);

	// Free the allocated resources
	stbi_image_free(buffer);

	// Store the texture
	textures[name] = texture;
	return texture;
}

/***********************************************************************************************************************
 * Texture getter.
 *
 * @param const std::string &name   Name of the texture.
 *
 * @return Texture*   Requested texture.
 **********************************************************************************************************************/
Texture * ResourceManager::getTexture(const std::string &name)
{
	return textures[name];
}

/***********************************************************************************************************************
 * Loads a font from the given truetype font file and stores it in a map.
 *
 * @param const std::string &fontFile   Path of the font file.
 * @param const unsigned int fontSize   Font size.
 * @param const std::string &name       Unique name for identifying the font.
 *
 * @return Font*   The loaded font.
 **********************************************************************************************************************/
Font * ResourceManager::loadFont(const std::string &fontFile, unsigned int fontSize, const std::string &name)
{
	// Create a texture atlas
	Font *font = new Font();
	font->generateAtlas(fontFile, fontSize);

	// Store the font
	fonts[name] = font;
	return font;
}

/***********************************************************************************************************************
 * Font getter.
 *
 * @param const std::string &name   Name of the font.
 *
 * @return Font*   Requested font.
 **********************************************************************************************************************/
Font * ResourceManager::getFont(const std::string &name)
{
	return fonts[name];
}

/***********************************************************************************************************************
 * Cleans up all the allocated resources.
 *
 * @return void
 **********************************************************************************************************************/
void ResourceManager::clear()
{
	// Shaders
	for (const auto & shader : shaders) {
		shader.second->destroy();
	}

	// Textures
	for (const auto & texture : textures) {
		texture.second->destroy();
	}

	// Fonts
	for (const auto & font : fonts) {
		font.second->destroy();
	}
}

/***********************************************************************************************************************
 * Reads the given file's content into a string.
 *
 * @param const std::string &filepath   Path of the file to read in.
 *
 * @return std::string   File content.
 **********************************************************************************************************************/
std::string ResourceManager::readFile_(const std::string &filepath)
{
	std::string fileContent;
	std::ifstream sourceFile(filepath, std::ios::in | std::ios::binary);

	if (!sourceFile) {
		throw std::runtime_error("Failed to open file");
	}

	sourceFile.seekg(0, std::ios::end);
	size_t size = sourceFile.tellg();

	if (size == -1) {
		throw std::runtime_error("Failed to read file");
	}

	fileContent.resize(size);
	sourceFile.seekg(0, std::ios::beg);
	sourceFile.read(&fileContent[0], size);

	return fileContent;
}

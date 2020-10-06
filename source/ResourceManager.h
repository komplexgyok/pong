#pragma once

#include <map>
#include "Font.h"
#include "Shader.h"
#include "Texture.h"

/***********************************************************************************************************************
 * ResourceManager class.
 *
 * It is static class responsible for loading and getting various resources: shaders, textures, fonts.
 **********************************************************************************************************************/
class ResourceManager
{
public:
	// Constructor, we don't want to instantiate
	ResourceManager() = delete;

	// Shader
	static Shader * loadShader(const std::string &vertexShaderFile, const std::string &fragmentShaderFile, const std::string &name);
	static Shader * getShader(const std::string &name);
	// Texture
	static Texture * loadTexture(const std::string &textureFile, const std::string &name);
	static Texture * getTexture(const std::string &name);
	// Font
	static Font * loadFont(const std::string &fontFile, unsigned int fontSize, const std::string &name);
	static Font * getFont(const std::string &name);

	static void clear();

	static std::map<std::string, Shader*> shaders;
	static std::map<std::string, Texture*> textures;
	static std::map<std::string, Font*> fonts;

private:
	static std::string readFile_(const std::string &filepath);
};

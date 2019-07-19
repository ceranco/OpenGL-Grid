#ifndef _SHADER_HEADER
#define _SHADER_HEADER

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include <unordered_map>

class Shader
{
public:
	static Shader fromFile(const std::string &vertexFile, const std::string &fragmentFile);

public:
	Shader(const std::string &vertexSource, const std::string &fragmentSource);

	~Shader();
	
	void use();

	void set(const std::string &name, int value);

	void set(const std::string &name, bool value);

	void set(const std::string &name, float value);

	void set(const std::string &name, const glm::vec2& value);

	void set(const std::string &name, const glm::vec3& value);

	void set(const std::string &name, const glm::vec4& value);

	void set(const std::string &name, const glm::mat4& value);

	GLint getAttributeLocation(const std::string &name);

private:
	GLuint program;
	std::unordered_map<std::string, GLint> uniforms;
};

#endif
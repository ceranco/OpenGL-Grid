#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Shader
{
public:
	static Shader fromFile(const std::filesystem::path& vertexFile, const std::filesystem::path& fragmentFile)
	{
		if (!std::filesystem::exists(vertexFile))
		{
			throw std::invalid_argument("Vertex file does not exist");
		}
		if (!std::filesystem::exists(fragmentFile))
		{
			throw std::invalid_argument("Fragment file does not exist");
		}
		return Shader{ readFile(vertexFile), readFile(fragmentFile) };
	}

public:
	Shader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		// generate the shaders and load the source
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vertexStr = vertexSource.c_str();
		const char* fragmentStr = fragmentSource.c_str();
		glShaderSource(vertexShader, 1, &vertexStr, NULL);
		glShaderSource(fragmentShader, 1, &fragmentStr, NULL);

		// compile the shaders
		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		auto logShaderInfo = [](GLuint shader, const std::string& name)
		{
			int  success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				std::cout << "Error: '" << name << "' compilation failed with the following message: " << infoLog << std::endl;
			}
		};
		logShaderInfo(vertexShader, "Vertex Shader");
		logShaderInfo(fragmentShader, "Fragment Shader");

		// link the program
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		auto logProgramInfo = [](GLuint program, const std::string& name)
		{
			int  success;
			char infoLog[512];
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(program, 512, NULL, infoLog);
				std::cout << "Error: '" << name << "' linking failed with the following message: " << infoLog << std::endl;
			}
		};
		logProgramInfo(program, "Program");

		// cache the uniforms location
		GLint numUniforms;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUniforms);
		for (GLint i = 0; i < numUniforms; i++)
		{
			const GLsizei bufSize = 32; // maximum name length
			GLchar name[bufSize]; // variable name in GLSL
			GLsizei length; // name length
			GLint size; // size of the variable
			GLenum type; // type of the variable (float, vec3 or mat4, etc)

			// get the name of this uniform
			glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);

			// cache for later use
			uniforms[std::string(name)] = i;
		}

		// clean-up shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	~Shader()
	{
		// free program
		glDeleteProgram(program);
	}

	void use()
	{
		glUseProgram(program);
	}

	template <typename T>
	void set(const std::string& name, T value)
	{
		static_assert(false, "Cant set uniform for this type.");
	}

	template <>
	void set(const std::string& name, int value)
	{
		use();
		glUniform1i(uniforms[name], value);
	}

	template <>
	void set(const std::string& name, bool value)
	{
		set(name, value ? 1 : 0);
	}

	template <>
	void set(const std::string& name, float value)
	{
		use();
		glUniform1f(uniforms[name], value);
	}

	template <>
	void set(const std::string& name, glm::vec2 value)
	{
		use();
		glUniform2fv(uniforms[name], 1, glm::value_ptr(value));
	}


	template <>
	void set(const std::string& name, glm::vec3 value)
	{
		use();
		glUniform3fv(uniforms[name], 1, glm::value_ptr(value));
	}

	template <>
	void set(const std::string& name, glm::vec4 value)
	{
		use();
		glUniform4fv(uniforms[name], 1, glm::value_ptr(value));
	}

	template <>
	void set(const std::string& name, glm::mat4 value)
	{
		use();
		glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
	}

	GLint getAttributeLocation(const std::string& name)
	{
		return uniforms[name];
	}

private:
	GLuint program;
	std::unordered_map<std::string, GLint> uniforms;

private:
	static std::string readFile(const std::filesystem::path& path)
	{
		std::ifstream t(path);
		std::stringstream buffer;
		buffer << t.rdbuf();
		return buffer.str();
	}
};
#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader {
public:
	Shader(const std::string& vert, const std::string& frag);
	Shader(const Shader& other);

	virtual ~Shader();

	void Use();

	void Set(const std::string& name, int value);
	void Set(const std::string& name, glm::mat4 value);

private:
	GLuint GetUniformLocation(const std::string& name);
	void Initialize();

	struct ShaderSources {
		std::string vertex;
		std::string fragment;
	}sources;

	GLuint program;

	struct Shaders {
		GLuint vertex;
		GLuint fragment;
	}shaders;

	std::unordered_map<std::string, GLuint> uniformLocations;

};

#endif // SHADER_H
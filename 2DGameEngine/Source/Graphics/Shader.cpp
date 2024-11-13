#include "Graphics/Shader.h"
#include <iostream>

Shader::Shader(const std::string& vert, const std::string& frag) {
	sources.vertex = vert;
	sources.fragment = frag;

	Initialize();
}

Shader::Shader(const Shader& other) {
	sources.vertex = other.sources.vertex;
	sources.fragment = other.sources.fragment;

	Initialize();
}

Shader::~Shader() {
	glDetachShader(program, shaders.vertex);
	glDeleteShader(shaders.vertex);

	glDetachShader(program, shaders.fragment);
	glDeleteShader(shaders.fragment);

	glDeleteProgram(program);

	uniformLocations.clear();
}

void Shader::Use() {
	glUseProgram(program);
}

void Shader::Set(const std::string& name, int value){
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::Set(const std::string& name, float value){
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::Set(const std::string& name, glm::mat4 value){
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

GLuint CreateShader(const std::string& source, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	assert(shader != 0); // "Error: Shader creation failed!"

	const GLchar* shaderSourceStrings = source.c_str(); // Convert string to C string
	GLint shaderSourceStringLengths = (GLint)source.size();

	glShaderSource(shader, 1,
		&shaderSourceStrings, &shaderSourceStringLengths
	);
	glCompileShader(shader);

	//Check if there is Shader Error
	GLint success = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLchar error[1024] = { 0 };
		glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << "Error: Shader compilation failed!1" << error << '\n';
		exit(-1); // "Error: Shader compilation failed!"
	}
	return shader;
}

GLuint Shader::GetUniformLocation(const std::string& name) {
	auto it = uniformLocations.find(name);
	if (it != uniformLocations.end()) {
		return it->second;
	}

	GLuint location = glGetUniformLocation(program, name.c_str());
	uniformLocations[name] = location;
	return location;
}

void Shader::Initialize() {
	program = glCreateProgram();

	shaders.vertex   = CreateShader(sources.vertex,   GL_VERTEX_SHADER);
	shaders.fragment = CreateShader(sources.fragment, GL_FRAGMENT_SHADER);

	// Attach Shaders to the Program
	glAttachShader(program, shaders.vertex);
	glAttachShader(program, shaders.fragment);

	GLint success = 0;
	
	glGetShaderiv(shaders.vertex, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLchar error[1024];
		glGetShaderInfoLog(shaders.vertex, sizeof(error), NULL, error);
		std::cerr << "Error compiling vertex shader:\n" << error << std::endl;
	}

	glGetShaderiv(shaders.fragment, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLchar error[1024];
		glGetShaderInfoLog(shaders.fragment, sizeof(error), NULL, error);
		std::cerr << "Error compiling fragment shader:\n" << error << std::endl;
	}
	
	// Linking the Program
	glLinkProgram(program);

	//Check if there is Linking Error
	glGetShaderiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		GLchar error[1024] = { 0 };
		glGetShaderInfoLog(program, sizeof(error), NULL, error);
		std::cerr << "Error: Shader linking failed!" << error << '\n';
		exit(-1); // "Error: Shader linking failed!"
	}

	// Validating the Program
	glValidateProgram(program);
	glGetShaderiv(program, GL_VALIDATE_STATUS, &success);
	if (success == GL_FALSE) {
		GLchar error[1024] = { 0 };
		glGetShaderInfoLog(program, sizeof(error), NULL, error);
		std::cerr << "Error: Shader validation failed!" << error << '\n';
		exit(-1); // "Error: Shader validation failed!"
	}
}

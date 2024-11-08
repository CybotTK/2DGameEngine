#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>


struct TextureParamaters {
	int wrapX = GL_CLAMP_TO_BORDER; // GL_TEXTURE_WRAP_S
	int wrapY = GL_CLAMP_TO_BORDER; // GL_TEXTURE_WRAP_T

	int minFilter = GL_NEAREST; // GL_TEXTURE_MIN_FILTER
	int magFilter = GL_NEAREST; // GL_TEXTURE_MAG_FILTER

	glm::vec4 borderColor = { 0.f, 0.f, 0.f, 1.f }; // GL_TEXTURE_BORDER_COLOR
};

class Texture {
public:
	Texture();
	Texture(int width, int height, GLint format = GL_RGBA8, GLenum pixelFormat=GL_UNSIGNED_INT);
	virtual ~Texture();

	void Use(int slot = 0) const;
	static void UseDefault(int slot = 0);

	unsigned int GetTextureID() const;

	inline int GetHeight() const { return m_width; }
	inline int GetWidth() const { return m_height; }
	inline glm::ivec2 GetResolution() const;

	float GetAspectRatio();
protected:

	void GenerateOGLTexture();

	TextureParamaters m_texParams;

	bool m_initialized = false;

	unsigned int m_texture;
	unsigned char*  m_data = nullptr;

	int m_width = 32;
	int m_height = 32;

	GLenum m_textureMode = GL_TEXTURE_2D;
};

#endif // TEXTURE_H
#include "Graphics/Texture.h"

Texture::Texture()
{
}

Texture::Texture(int width, int height, GLint format, GLenum pixelFormat)
{
	m_width = width;
	m_height = height;

	GenerateOGLTexture();

	glTexImage2D(GL_TEXTURE_2D, 0 , format, m_width, m_height, 0, GL_RGBA, pixelFormat, m_data);
}

Texture::~Texture()
{
	if (m_data != nullptr)
	{
		delete[] m_data;
	}

	glDeleteTextures(1, &m_texture);
}

void Texture::Use(int slot) const
{
	assert(m_initialized);

	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_textureMode, m_texture);
}

void Texture::UseDefault(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::GetTextureID() const
{
	return m_texture;
}

glm::ivec2 Texture::GetResolution() const
{
	return glm::ivec2(m_width, m_height);
}

float Texture::GetAspectRatio()
{
	return float(m_width)/float(m_height);
}

void Texture::GenerateOGLTexture()
{
	m_initialized = true;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Updating the Texture Parrameters:
	{
		// Texdture Wrap (out of bounds)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texParams.wrapX);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texParams.wrapY);

		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &m_texParams.borderColor[0]);

		//Texels
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texParams.minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texParams.magFilter);
	}
}

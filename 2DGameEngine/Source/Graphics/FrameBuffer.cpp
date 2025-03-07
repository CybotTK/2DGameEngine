#include "Graphics/FrameBuffer.h"

FrameBuffer::FrameBuffer() {
}

FrameBuffer::FrameBuffer(int width, int height, int texCount) {
	m_resolution = { width, height };

	Initialize(texCount);
}

FrameBuffer::~FrameBuffer() {
	for (auto tex : m_textures)
	{
		delete tex;
	}

	m_textures.clear();
	m_attachments.clear();

	glDeleteFramebuffers(1, &m_fbo);
}

void FrameBuffer::Use() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void FrameBuffer::UseDefault() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::UseTexture(int textureNumber, int position) {
	assert(textureNumber >= 0 && textureNumber <= m_textures.size());
	m_textures[textureNumber]->Use(position);
}

void FrameBuffer::UseAllTextures(int offset) {
	int i = offset;
	for (auto& tex : m_textures)
	{
		tex->Use(i);
		++i;
	}
}

void FrameBuffer::Resize(int width, int height) {
	assert(m_initialized);

	auto newRes = glm::ivec2(width, height);

	if (newRes == m_resolution) { return; }
	m_resolution = newRes;

	auto texCount = m_textures.size();
	assert(texCount > 0);

	for (auto tex : m_textures)
	{
		delete tex;
	}

	m_textures.clear();
	m_attachments.clear();

	AddTextures(texCount);
}

glm::ivec2 FrameBuffer::GetResolution() {
	return m_resolution;
}

float FrameBuffer::GetAspect() const {
	if (forceAspect > 0.f) {
		return forceAspect;
	}

	return (float)m_resolution.x / (float)m_resolution.y;
}

Texture* FrameBuffer::GetTexture(int index) {
	return m_textures[index];
}

void FrameBuffer::Initialize(int texCount) {
	assert(texCount > 0);
	assert(m_resolution.x > 0 && m_resolution.y > 0);

	m_initialized = true;

	// Generating FBO
	glGenFramebuffers(1, &m_fbo);

	AddTextures(texCount);
}

void FrameBuffer::AddTextures(int texCount) {
	// Using it
	Use();

	for (int i = 0; i < texCount; i++)
	{
		auto tex = new Texture(m_resolution.x, m_resolution.y);

		//Texture Wrap (out of bnounds)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLenum attach = GL_COLOR_ATTACHMENT0 + i;
		glFramebufferTexture2D(GL_FRAMEBUFFER, attach, GL_TEXTURE_2D, tex->GetTextureID(), 0);

		m_textures.emplace_back(tex);
		m_attachments.emplace_back(attach);
	}

	glDrawBuffers((GLint)texCount, &m_attachments[0]);
}

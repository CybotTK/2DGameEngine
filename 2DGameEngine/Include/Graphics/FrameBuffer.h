// Offscreen rendering used for the editor
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics/Texture.h"

class FrameBuffer {
public:
	FrameBuffer();
	FrameBuffer(int width, int height, int texCount);
	virtual ~FrameBuffer();

	void Use();
	void static UseDefault();

	void UseTexture(int textureNumber, int position);
	void UseAllTextures(int offset = 0);

	void Resize(int width, int height);

	glm::ivec2 GetResolution();
	float GetAspect() const;

protected:
	void Initialize(int texCount);
	void AddTextures(int texCount);

	bool m_initialized = false;

	glm::ivec2 m_resolution;

	unsigned int m_fbo;

	std::vector<GLenum> m_attachments;
	std::vector<Texture*> m_textures;
};

#endif // !FRAME_BUFFER_H

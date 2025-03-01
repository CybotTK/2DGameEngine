#include "Graphics/Textures/ImageTexture.h"

#include "System/FileUtils.h"

#include "Editor/UI/Props.h"

#ifndef STB_IMAGE_IMPLEMENTANTION
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#endif // STB_IMAGE_IMPLEMENTATION

ImageTexture::ImageTexture() {
}

ImageTexture::ImageTexture(const std::string& file) {
	m_source = file::DumpToMemory(file, m_sourceLength);

	GenerateImageFromSource();

	debug.name = file;
	debug.description = std::to_string(m_width) + "x" + std::to_string(m_height);
	debug.thumbnail = this;
}

ImageTexture::~ImageTexture() {
	if (m_source) {
		delete[] m_source;
	}
}

void ImageTexture::DrawUI() {
	ui::ObjectHeader(&debug.name, "ImageTexture");

	ui::Text("Preview:");
	ui::Image(this, { 0.f, 0.f }, false);
}

void ImageTexture::GenerateImageFromSource() {
	// We need to parse the RAW file into an "usable" image format. 
	// That's why this step is necessary.
	int comp = 0;
	m_data = (unsigned char*)stbi_load_from_memory(
		m_source, int(m_sourceLength / sizeof(unsigned char)),
		&m_width, &m_height, &comp,
		STBI_rgb_alpha // 4
	); 
	assert(m_data); // If data is null, something wrong happened when loading it from mem


#pragma region Generating the Texture:

	//Provide different params to Images
	m_texParams = {
		GL_REPEAT, GL_REPEAT,
		GL_NEAREST, GL_NEAREST,
		//GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR,
		{0.f, 0.f, 0.f, 0.f}
	};

	GenerateOGLTexture();

	//RGBA8 gives more control
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
	glGenerateMipmap(GL_TEXTURE_2D);

#pragma endregion

	//Freeing data
	//we don't need to keep this since we already
	//sent the data to the GPU
	stbi_image_free(m_data);
	m_data = nullptr;

}

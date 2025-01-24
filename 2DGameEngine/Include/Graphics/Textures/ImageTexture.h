#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "Graphics/Texture.h"
#include <string>

#include "Asset/Object.h"

class ImageTexture : public Object, public Texture {
public:
	ImageTexture();
	ImageTexture(const std::string& file);
	virtual ~ImageTexture();

private:
	void GenerateImageFromSource();

	size_t m_sourceLength;
	unsigned char* m_source = nullptr;
};

#endif // IMAGE_TEXTURE_H
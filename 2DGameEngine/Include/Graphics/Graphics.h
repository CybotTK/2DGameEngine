#ifndef GRAPHICS_H
#define GRAPHICS_H

namespace graphics {
	void ShowMouse(bool show);

	void ClearBuffers(float r, float g, float b, float a);

	void SetViewport(int x, int y, int width, int height);
}

#endif // GRAPHICS_H
#include <Graphics/Graphics.h>

#include <GL/glew.h>
#include "SDL2/SDL.h"

void graphics::ShowMouse(bool show){
	SDL_ShowCursor(show);
}

void graphics::ClearBuffers(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void graphics::SetViewport(int x, int y, int width, int height){
	glViewport(x, y, width, height);
}

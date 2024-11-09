#ifndef BASIC_SHADERS_H
#define BASIC_SHADERS_H

#include <string>

namespace shader {
static const std::string BasicVertex = R"(
#version 460 core

layout(location = 0) in vec2 aPosition; // attribute Position
layout(location = 1) in vec2 aUV;

out VS_OUT {
	vec2 position;
	vec2 UV;
} vsOut;

void main(){
	//Passing the vertex position to the fragment shader
	vsOut.position  = aPosition * 0.5f;
	vsOut.UV = aUV;
	vsOut.UV.y = 1.0f - vsOut.UV.y; //Flipping OpenGL Y
	
	gl_Position.xy = vsOut.position;
}
)";

static const std::string BasicFragment = R"(
#version 460 core

layout(location = 0) out vec4 gColor;

in VS_OUT{
	vec2 position;
	vec2 UV;
} vsOut;

uniform sampler2D testImage;

void main(){
	//gColor = vec4(1.f, 0.f, 0.f, 1.f);
	gColor = texture2D(testImage, vsOut.UV);
}
)";
}

#endif
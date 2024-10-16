#ifndef BASIC_SHADERS_H
#define BASIC_SHADERS_H

namespace shader {
static const std::string BasicVertex = R"(
#version 460 core

layout(location = 0) in vec2 aPosition; // attribute Position
layout(location = 1) in vec2 aTexCoords;

out VS_OUT {
	vec2 position;
	vec2 texCoords;
} vs_out;

void main(){
	vs_out.position  = aPosition;
	vs_out.texCoords = aTexCoords;

	gl_Position.xy = vs_out.position * 0.5f;
}
)";

static const std::string BasicFragment = R"(
#version 460 core

layout(location = 0) out vec4 gColor;

//out vec4 gColor;

in VS_OUT {
	vec2 position;
	vec2 texCoords;
} vs_in;

void main(){
	gColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";
}

#endif

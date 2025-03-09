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

struct Sprite{
	vec4 color;
	sampler2D texture;
};

uniform mat4 transform; //Model
uniform mat4 viewProjection;

void main(){
	//Passing the vertex position to the fragment shader
	vsOut.position  = (viewProjection * transform * vec4(aPosition, 0.f, 1.f)).xy;
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

struct Sprite{
	vec4 color;
	sampler2D texture;
	bool useTexture;
};

struct Layer{
	vec4 tint;
};

uniform Sprite sprite;
uniform Layer  layer;

uniform bool isSelected = false;
uniform vec4 selectedColor = vec4(0.207f, 0.1176f, 0.30196f, 1.f);

void main(){
	gColor = vec4( 1.f, 1.f, 1.f, 1.f );

	if (sprite.useTexture == true)
		gColor = texture2D(sprite.texture, vsOut.UV);
	
	gColor  *= sprite.color;	
	gColor  *= layer.tint;	

	if (isSelected){
		gColor = selectedColor;
	}
}
)";

//--------------------------------------------------------//

static const std::string PostVertex = R"(
#version 460 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aUV;

out VS_OUT {
	vec2 position;
	vec2 UV;
} vsOut;

void main(){
	vsOut.position  = aPosition;
	vsOut.UV = aUV;
	
	gl_Position.xy = vsOut.position;
}
)";

static const std::string PostFragment = R"(
#version 460 core

layout(location = 0) out vec4 gColor;

in VS_OUT{
	vec2 position;
	vec2 UV;
} vsOut;

uniform sampler2D renderedTexture;
uniform float aspect = 1.f;

void main(){
	vec2 uv = vsOut.UV * vec2(aspect, 1.f);
	gColor = texture2D(renderedTexture, uv);
}
)";


}

#endif // !BASIC_SHADERS_H
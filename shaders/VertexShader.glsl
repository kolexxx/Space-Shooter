#version 330 core

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in float textureID;

uniform mat4 u_Projection;

out vec3 color;
out vec2 UV;
out float texture;

void main()
{
	gl_Position = u_Projection * vec4(vertexPosition, 0, 1);

	color = vertexColor;
	UV = vertexUV;
	texture = textureID;
}
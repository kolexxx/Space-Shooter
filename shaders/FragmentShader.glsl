#version 330 core

uniform sampler2D u_Texture;

in vec3 color;
in vec2 UV;
out vec3 fragmentColor;

void main()
{
	fragmentColor = color * texture(u_Texture, UV).rgb;
}
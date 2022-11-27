#version 330 core

uniform sampler2D u_Textures[32];

in vec3 color;
in vec2 UV;
in float texture;

out vec3 fragmentColor;

void main()
{
	int index = int(texture);
	fragmentColor = texture(u_Textures[index], UV).rgb * color;
}
#version 410
out vec4 frag_colour;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	frag_colour = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
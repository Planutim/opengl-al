#version 410
out vec4 frag_colour;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	frag_colour = mix(texture(texture1, TexCoord), texture(texture2,TexCoord), 0.2);
//	frag_colour = vec4(0.5, 0.3 ,0.2, 1.0);
}

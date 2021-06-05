#version 410

out vec4 frag_colour;
in vec3 color;

void main()
{
	frag_colour = color.xyyz;
	
}
#version 410

layout (location = 0) in vec3 aPos;

out vec3 color;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;
void main()
{
	gl_Position = projection * view * world * vec4(aPos, 1.0);
	color = aPos;
}
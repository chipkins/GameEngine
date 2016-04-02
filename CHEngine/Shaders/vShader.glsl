#version 430

layout (location = 0) in vec3 loc;
layout (location = 1) in vec2 uv;

out vec2 fragUV;

void main()
{
	fragUV = uv;

	gl_Position = vec4(loc,1);
}
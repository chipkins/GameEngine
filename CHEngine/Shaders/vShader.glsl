#version 430

layout (location = 0) in vec3 loc;
layout (location = 1) in vec2 uv;
layout (location = 2) uniform mat4 modelToWorld;
layout (location = 3) uniform mat4 cameraMat;

out vec2 fragUV;

void main()
{
	fragUV = uv;

	gl_Position = cameraMat * modelToWorld * vec4(loc,1);
}
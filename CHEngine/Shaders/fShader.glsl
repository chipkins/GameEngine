#version 430

uniform sampler2D myTexture;

in vec2 fragUV;

out vec4 fragColor;

void main()
{
	fragColor = texture(myTexture, fragUV);
}
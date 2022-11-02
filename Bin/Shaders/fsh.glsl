#version 330 core

//Inputs must match vsh
in vec2 iUV;
in vec4 iColor;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
	//FragColor = iColor;
	FragColor = texture(ourTexture, iUV);
}
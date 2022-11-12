#version 330 core

//Inputs must match vsh
in vec2 iUV;
in vec4 iColor;

uniform sampler2D mainTex;
uniform sampler2D overlayTex;

void main()
{
	//FragColor = iColor;
	vec4 kirbo = texture(mainTex, iUV);
	vec4 overlay = texture(overlayTex, iUV);
	gl_FragColor = overlay * kirbo;
}
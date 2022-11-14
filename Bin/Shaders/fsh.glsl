#version 330 core

//Inputs must match vsh
in vec2 iUV;
in vec3 iNormal;

uniform sampler2D mainTex;
uniform sampler2D overlayTex;

void main()
{
	//FragColor = iColor;
	vec3 normal = normalize(iNormal);
	
	vec4 main = texture(mainTex, iUV);
	//vec4 overlay = texture(overlayTex, iUV);
	//float light = dot(iNormal, vec3(1.0f,0.0f,0.0f)) * 0.5f + 0.5f;
	//gl_FragColor = vec4(iNormal,1.0f);
	gl_FragColor = main;
}
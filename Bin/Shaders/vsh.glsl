#version 330 core

layout (location=0) in vec3 vPos;
layout (location=1) in vec2 vUV;
layout (location=2) in vec4 vColor;

out vec2 iUV;
out vec4 iColor;

void main()
{
	gl_Position = vec4(vPos.xyz, 1.0);
	iUV = vUV;
	iColor = vColor;
}
#version 330 core

layout (location=0) in vec3 vPos;
layout (location=1) in vec2 vUV;
layout (location=2) in vec3 vNormal;

out vec2 iUV;
out vec3 iWorldPos;
out vec3 iNormal;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(vPos.xyz, 1.0);
	iWorldPos = vPos.xyz;
	iUV = vUV;
	iNormal = vNormal;
}
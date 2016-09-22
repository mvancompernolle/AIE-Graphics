#version 430

out vec4 outColor;

in vec4 vPosition;
in vec4 vNormal;
in vec2 vUV;

layout(location = 3) uniform sampler2D diffuseMap;
layout(location = 4) uniform sampler2D normalMap;
layout(location = 5) uniform sampler2D specularMap;

uniform L = normalize(vec3(1, 0, 1));

void main()
{
	float lamb = -dot(vNormal, L);

	outColor = texture(diffuseMap, vUV) +
			   lamb;

}
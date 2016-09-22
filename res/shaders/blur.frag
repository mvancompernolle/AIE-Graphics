#version 430

layout(location = 0) out vec4 outNormal;

in vec2 vUV;

layout(location = 0) uniform sampler2D normalMap;

vec4 crossblur(in sampler2D map, in vec2 UV);

void main()
{
	outNormal = crossblur(normalMap, vUV);
}

vec4 crossblur(in sampler2D map, in vec2 UV)
{
	vec2 sDim = textureSize(map,0).xy;
	vec4 retval = vec4(0,0,0,0);
	for(int i = -9; i <= 9; ++i)
	{
		retval += texture(map, UV + vec2( i, 0)/sDim);
		retval += texture(map, UV + vec2( 0, i)/sDim);
	}
	return retval / 36;
}

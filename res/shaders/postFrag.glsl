#version 430

in vec2 UV;

layout(location = 0)uniform mat4 proj;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

layout(location = 3)uniform sampler2D colorMap;
layout(location = 4)uniform sampler2D diffuseMap;
layout(location = 5)uniform sampler2D specularMap;

out vec4 outColor;

void main()
{ 
	outColor = texture(colorMap, UV);
}

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

uniform float xOffset;
uniform mat4  transform;

out	vec3 ourColor;
out vec2 ourTexCoord;

void main()
{
	gl_Position = transform * vec4(position.x + xOffset, position.y, position.z, 1.0);
	ourColor	= color;
	ourTexCoord = vec2( texCoord.x, 1.0 - texCoord.y );
}
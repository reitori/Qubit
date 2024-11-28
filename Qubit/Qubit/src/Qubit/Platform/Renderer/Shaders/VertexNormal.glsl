#version 330 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoords;
layout (location = 3) in vec3 inNormals;

uniform mat4 model;
uniform mat4 mvp;

out vec4 vertColor;
out vec2 texCoords;
out vec3 normals;

void main(){
	gl_Position = mvp * vec4(inPos, 1.0);
	normals = mat3(model) * inNormals;
	vertColor = inColor;
	texCoords = inTexCoords;
}
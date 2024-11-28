#version 330 core
layout (location = 0) in vec4 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoords;
layout (location = 3) in vec4 inColor;
layout (location = 4) in mat4 inModelTranslation;

uniform mat4 model;
uniform mat3 normalMat;

uniform projectionView{
	mat4 projection;
	mat4 view;
};

uniform UniformBlock {mat4 instanceMatrix[]; };


out vec4 vertColor;
out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;

void main(){
	gl_Position = projection * view * inModelTranslation * inPos;
	normal = normalMat * inNormal;
	fragPos = vec3(model * inPos);
	vertColor = inColor;
	texCoords = inTexCoords;
}
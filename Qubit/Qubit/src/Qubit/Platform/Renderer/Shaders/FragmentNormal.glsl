#version 330 core
out vec4 FragColor;

in vec4 vertColor;
in vec2 texCoords;

struct Object{
	sampler2D m_Texture;
};

uniform Object object;

void main(){
	
	FragColor = vertColor * texture2D(object.m_Texture, texCoords);
}	
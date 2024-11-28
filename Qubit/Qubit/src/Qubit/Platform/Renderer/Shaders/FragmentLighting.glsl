#version 330 core
out vec4 FragColor;

struct Material{
    sampler2D colorTexture;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec4 vertColor;
in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform float time;
uniform Material material;

uniform int lightCount;
uniform PointLight pointLights[32];
uniform DirLight directionLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = CalcDirLight(directionLight, norm, viewDir);

    for(int i = 0; i < lightCount; i++){
        result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);
    }


    FragColor = vec4(result, 1.0) * vertColor;
} 

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
   
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
   
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float distance = length(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);


    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords)) * attenuation;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords)) * attenuation;
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords)) * attenuation;
    

    return (ambient + diffuse + specular);
}

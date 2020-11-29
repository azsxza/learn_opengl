#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Position;

struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_reflection1;
	float shininess;
};

struct dirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct pointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform vec3 viewPos;

uniform Material material;

uniform dirLight dLight;
uniform pointLight pLight[4];
uniform samplerCube skybox;


vec3 calDirLight(dirLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient = light.ambient*vec3(texture(material.texture_diffuse1, TexCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.texture_diffuse1, TexCoords));

	vec3 halfWayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(halfWayDir, normal),0.0),material.shininess);
	vec3 specular = light.specular*spec*vec3(texture(material.texture_specular1,TexCoords));

	return diffuse+ambient+specular;
}

vec3 calPointLight(pointLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient = light.ambient*vec3(texture(material.texture_diffuse1, TexCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position-FragPos);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.texture_diffuse1, TexCoords));

	vec3 halfWayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(halfWayDir, normal),0.0),material.shininess);
	vec3 specular = light.specular*spec*vec3(texture(material.texture_specular1,TexCoords));

	float distance = length(light.position-FragPos);
	float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*(distance*distance));

	return (diffuse+ambient+specular)*attenuation;
}


void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos-FragPos);
	vec3 re = calDirLight(dLight, norm, viewDir);
	for(int i=0;i<4;i++)
		re+=calPointLight(pLight[i], norm, viewDir);
	FragColor = vec4(re,1.0);

	vec3 I = normalize(Position - viewPos);
	vec3 reflectMap = vec3(texture(material.texture_reflection1, TexCoords));
    vec3 R = reflect(I, normalize(Normal));
	vec3 reflection = vec3(texture(skybox, R).rgb)*reflectMap;
    FragColor = vec4(re+reflection, 1.0);
}
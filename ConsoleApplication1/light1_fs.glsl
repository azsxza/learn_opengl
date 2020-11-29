#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Position;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
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
	vec3 ambient = light.ambient*vec3(texture(material.diffuse, TexCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, TexCoords));

	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(reflectDir, viewDir),0.0),material.shininess);
	vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords));

	return diffuse+ambient+specular;
}

vec3 calPointLight(pointLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambient = light.ambient*vec3(texture(material.diffuse, TexCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position-FragPos);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, TexCoords));

	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(reflectDir, viewDir),0.0),material.shininess);
	vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoords));

	float distance = length(light.position-FragPos);
	float attenuation = 1.0/(light.constant+light.linear*distance+light.quadratic*(distance*distance));

	return (diffuse+ambient+specular)*attenuation;
}


void main()
{
	vec4 texColor = texture(material.diffuse, TexCoords);
//    if(texColor.a < 0.1)
//        discard;
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos-FragPos);
	vec3 re = calDirLight(dLight, norm, viewDir);
	for(int i=0;i<4;i++)
		re+=calPointLight(pLight[i], norm, viewDir);
	//FragColor = vec4(re,texColor.a);
	float ratio = 1.00 / 1.52;
	vec3 I = normalize(Position - viewPos);
    vec3 R = refract(I, normalize(Normal),ratio);
    FragColor = vec4(texture(skybox, R).rgb*0.1+re*0.9, 1.0);
}
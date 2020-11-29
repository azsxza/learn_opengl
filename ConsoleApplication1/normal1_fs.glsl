#version 330 core
out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
uniform sampler2D normalMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float shadowCal(vec4 fragPosLightSpace)
{
	vec3 projCoords = fragPosLightSpace.xyz/fragPosLightSpace.w;
	projCoords = projCoords*0.5+0.5;
	float closestDepth = texture(shadowMap,projCoords.xy).r;
	float currentDepth = projCoords.z;

	//float shadow = currentDepth-0.05>closestDepth?1.0:0.0;
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	vec3 normal = texture(normalMap, projCoords.xy).rgb;
	normal = normalize(normal * 2.0 - 1.0); 
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.05);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;
	if(projCoords.z > 1.0)
        shadow = 0.0;
	return shadow;
}

void main()
{
	vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
	vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);   
	vec3 lightColor = vec3(1.0);

	vec3 ambient = 0.15*color;

	vec3 lightDir = normalize(lightPos-fs_in.FragPos);
	float diff = max(dot(lightDir,normal),0.0);
	vec3 diffuse = diff*lightColor;

	vec3 viewDir = normalize(viewPos-fs_in.FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	vec3 halfwayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(normal,halfwayDir),0.0),64.0);
	vec3 specular = spec*lightColor;

	float shadow = shadowCal(fs_in.FragPosLightSpace);


	vec3 light = (ambient+(1.0-shadow)*(diffuse+specular))*color;

	FragColor = vec4(light, 1.0f);
}

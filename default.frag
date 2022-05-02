#version 330 core
out vec4 FragColor;

in vec4 color;
in vec2 texCoord;
in vec3 normal;
in vec3 currentPos;

uniform float scale;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform vec3 camPos;

vec4 pointLight()
{	
	vec3 lightVec = lightPos - currentPos;
	float distance = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * distance * distance + b * distance + 1.0f);

	float ambient = 0.2f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return texture2D(tex0, texCoord) * lightColor * (diffuse * inten + ambient) + texture2D(tex1, texCoord).r * specular * inten;
}

vec4 directionalLight()
{	
	vec3 lightVec = lightPos - currentPos;
	float distance = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * distance * distance + b * distance + 1.0f);

	float ambient = 0.2f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(vec3(0.1f, 1.0f, 0.0f));

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return texture2D(tex0, texCoord) * lightColor * (diffuse * inten + ambient) + texture2D(tex1, texCoord).r * specular * inten;
}

vec4 spotLight()
{	
	float outerCone = 0.9f;
	float innerCone = 0.95f;

	float ambient = 0.2f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currentPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return texture2D(tex0, texCoord) * lightColor * (diffuse * intensity + ambient) + texture2D(tex1, texCoord).r * specular * intensity;
	
}
 
void main()
{
	FragColor = pointLight();
}
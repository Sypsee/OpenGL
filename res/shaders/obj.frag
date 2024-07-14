#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform vec3 viewPos;
uniform vec3 lightPos;

vec3 lightColor = vec3(1,1,1);
vec3 specularReflectionColor = vec3(1,1,1);
float lightIntensity = 1;
float ambientIntensity = .5;
float shininess = .2;
float alpha = 80;

void main()
{
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 diffuseColor = max(dot(normalize(Normal), normalize(lightDir)), 0) * vec3(texture(ourTexture, TexCoord));
	vec3 reflectedVector = -reflect(normalize(lightDir), normalize(Normal));
	vec3 specularReflection = max(pow(dot(reflectedVector, normalize(viewDir)), alpha), shininess) * specularReflectionColor;
	
	vec3 outputColor = lightIntensity * (diffuseColor + specularReflection) + (ambientIntensity * diffuseColor);
	
	FragColor = texture(ourTexture, TexCoord) * max(vec4(outputColor * lightColor, 1.0), ambientIntensity);
}
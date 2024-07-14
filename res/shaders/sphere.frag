#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;
uniform samplerCube skybox;
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
    vec3 baseColor = vec3(0.3, 0.5, 0.8);
    vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 diffuseColor = max(dot(normalize(Normal), normalize(lightDir)), 0) * baseColor;

    FragColor = vec4(diffuseColor * lightColor, 1.0);
}
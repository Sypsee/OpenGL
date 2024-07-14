#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 LightSpaceMatrix;

uniform sampler2D ourTexture;
uniform sampler2D shadowMap;
uniform samplerCube skybox;
uniform vec3 viewPos;
uniform vec3 lightPos;

vec3 lightColor = vec3(1,1,1);
vec3 specularReflectionColor = vec3(1,1,1);
float lightIntensity = 1;
float ambientIntensity = .5;
float shininess = .2;
float alpha = 80;

float ShadowCalculation(vec4 lightSpaceMatrix)
{
    vec3 projCoords = lightSpaceMatrix.xyz / lightSpaceMatrix.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    vec3 baseColor = vec3(0.5, 0.4, 0.7);
    vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 diffuseColor = max(dot(normalize(Normal), normalize(lightDir)), ambientIntensity) * baseColor;
    float shadow = ShadowCalculation(LightSpaceMatrix);
    vec3 outputColor = ((1 - shadow) * (diffuseColor * lightColor));

    FragColor = vec4(outputColor, 1.0);
}
#version 330 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform Light lightMoon;

uniform sampler2D texture_diffuse;

void main()
{
    // Ambient
    vec3 ambient = light.ambient *material.diffuse;
    
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);


     // AmbientMoon
    vec3 ambientMoon = lightMoon.ambient *material.diffuse;
    
    // DiffuseMoon
    vec3 lightDirMoon = normalize(lightMoon.position - FragPos);
    float diffMoon = max(dot(norm, lightDirMoon), 0.0);
    vec3 diffuseMoon = lightMoon.diffuse * diffMoon * material.diffuse;
    
    // SpecularMoon
    vec3 reflectDirMoon = reflect(-lightDirMoon, norm);
    float specMoon = pow(max(dot(viewDir, reflectDirMoon), 0.0), material.shininess);
    vec3 specularMoon = lightMoon.specular * (specMoon * material.specular);
    
    vec3 result = (ambient + diffuse + specular) + (ambientMoon + diffuseMoon + specularMoon);
    color = vec4(result, 1.0f)*texture(texture_diffuse,TexCoords);
}
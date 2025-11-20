#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float hasLight;

void main()
{
    if (hasLight > 0.5) {
        FragColor = vec4(objectColor, 1.0);
    } else {
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * objectColor;
        
        vec3 ambient = 0.3 * objectColor;
        
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = 0.5 * spec * vec3(1.0);
        
        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    }
}

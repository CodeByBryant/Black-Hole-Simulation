#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform vec3 blackHolePos;
uniform float blackHoleMass;

vec3 generateStarfield(vec3 dir) {
    float n = fract(sin(dot(dir.xy, vec2(12.9898, 78.233))) * 43758.5453);
    
    if (n > 0.998) {
        return vec3(1.0);
    } else if (n > 0.995) {
        return vec3(0.8, 0.8, 1.0);
    } else if (n > 0.992) {
        return vec3(1.0, 0.9, 0.7);
    }
    
    return vec3(0.01, 0.01, 0.05);
}

void main()
{
    vec3 color = generateStarfield(normalize(TexCoords));
    FragColor = vec4(color, 1.0);
}

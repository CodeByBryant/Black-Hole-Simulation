#version 330 core
out vec4 FragColor;

in vec3 FragPos;

uniform vec3 blackHolePos;
uniform float innerRadius;
uniform float outerRadius;
uniform float time;

void main()
{
    vec3 toPoint = FragPos - blackHolePos;
    float dist = length(toPoint.xz);
    
    if (dist < innerRadius || dist > outerRadius) {
        discard;
    }
    
    float t = (dist - innerRadius) / (outerRadius - innerRadius);
    
    float angle = atan(toPoint.z, toPoint.x);
    float rotation = time * (1.0 - t * 0.5);
    
    float brightness = 1.0 - t;
    brightness *= (sin(angle * 8.0 + rotation) * 0.3 + 0.7);
    brightness *= (sin(dist * 20.0 - time * 2.0) * 0.2 + 0.8);
    
    vec3 color = vec3(1.0, 0.6, 0.2) * brightness;
    
    FragColor = vec4(color, brightness * 0.6);
}

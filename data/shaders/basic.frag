#version 330 core

in vec3 normal;
in vec2 texCoord;

out vec4 outBuffer;

uniform sampler2D textureSampler;

void main(){
    vec3 color = texture( textureSampler, texCoord ).rgb; 

    float light = 0.5 + max(dot(normalize(normal), normalize(vec3(1.0, 0.5, 0.3))), 0.0);
    
    outBuffer=vec4(color*light, 1.0);
}
 

#version 330 core

in vec3 normal;
in vec2 texCoord;

out vec4 outBuffer;

uniform sampler2D textureSampler;

void main(){
    vec3 color = texture( textureSampler, texCoord ).rgb; 
    
    outBuffer=vec4(color, 1.0);
}
 

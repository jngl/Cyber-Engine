#version 150

in vec3 position;
in vec2 texCoord;

uniform mat4 MVP; 

out vec3 color;

void main() {

    gl_Position = MVP*vec4(position,1);
    color = vec3(texCoord, 1.0);
}
 

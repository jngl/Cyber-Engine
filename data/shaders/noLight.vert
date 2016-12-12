#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;

uniform mat4 MVP; 

out vec3 normal;
out vec2 texCoord;

void main() {

    gl_Position = MVP*vec4(inPosition,1);
    normal = inNormal;
    texCoord = inTexCoord;
}
 

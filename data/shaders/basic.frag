#version 150

in vec3 color;

out vec4 outBuffer;

void main(){
    outBuffer=vec4(color, 1.0);
}
 

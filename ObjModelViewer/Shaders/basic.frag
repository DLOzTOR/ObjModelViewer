#version 460
in vec3 Color;
out vec4 FragColor;
void main() {
FragColor = vec4(vec3(Color[2]/3,Color[2]/4,0.1), 1);
}
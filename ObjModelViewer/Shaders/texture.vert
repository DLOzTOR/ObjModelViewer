#version 460
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform mat4 RotationMatrix;
out vec2 TexCoord;

void main()
{
    gl_Position = RotationMatrix * vec4(aPos / 2, 1.0);
    TexCoord = aTexCoord;
}
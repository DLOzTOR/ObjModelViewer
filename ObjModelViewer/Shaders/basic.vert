#version 460
in vec3 VertexPosition;
layout(location = 1) in vec3 vertexColor;
out vec3 Color;
uniform mat4 RotationMatrix;
void main()
{
	Color = vertexColor;
	gl_Position = RotationMatrix * vec4( VertexPosition/2, 1.0 );
}
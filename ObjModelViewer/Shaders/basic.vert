#version 460
in vec3 VertexPosition;
out vec3 Color;
uniform mat4 RotationMatrix;
uniform mat4 TransformMatrix;
void main(){
	Color = VertexPosition;
	gl_Position =  TransformMatrix  * RotationMatrix *  vec4( VertexPosition / 70, 1.0 );
}
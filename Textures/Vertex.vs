#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 TexCord;

out vec2 T;
out vec3 fColor;

void main(){
	gl_Position = vec4(apos, 1.0);
	T = TexCord;
	fColor = color;
}

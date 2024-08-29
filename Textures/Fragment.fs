#version 330 core

out vec4 fragColor;

in vec2 T;
in vec3 fColor;

uniform sampler2D outTex;

void main(){
	fragColor = texture(outTex, T) * vec4(fColor, 1.0);
}


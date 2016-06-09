#version 140

out vec4 fragment;
in vec4 color;

void main() {
	fragment = vec4(color.xyz, 1.0);
}
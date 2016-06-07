#version 140

out vec4 fragment;
in vec4 color;

void main() {
	fragment = vec4(1 - color.x, 1 - color.y, 1 - color.x + color.y, 1.0);
}
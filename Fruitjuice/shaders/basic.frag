#version 140

out vec4 fragment;
in vec4 color;
in vec3 outNormal;
in vec3 light;

void main() {
	float diffuse = max(0, dot(normalize(outNormal), normalize(light)));

	fragment = vec4(diffuse, diffuse, diffuse, 1);
}
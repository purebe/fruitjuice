#version 140

varying vec4 color;
out vec3 outNormal;
out vec3 light;

uniform mat4 projection;
uniform mat4 modelView;

attribute vec3 position;
attribute vec3 normal;

void main() {
	gl_Position = projection * modelView * vec4(position.xyz, 1);
	color = gl_Position;
	outNormal = (modelView * vec4(normal, 0)).xyz;
	light = vec4(0, 0, 5, 1).xyz;
}
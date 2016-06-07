#version 140

varying vec4 color;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

attribute vec3 position;

void main() {
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position.xyz, 1);
	color = gl_Position;
}
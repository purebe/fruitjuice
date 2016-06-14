#version 140

out vec4 fragment;
in vec4 color;
in vec3 outNormal;
in vec3 light;
in vec3 ambient;
in vec3 diffuse;
in float outOpacity;

void main() {
	float diffuseCoeff = max(0, dot(normalize(light), normalize(outNormal)));

	vec3 fragColor = vec3(1 - ambient.x, 1 - ambient.y, 1 - ambient.z) + vec3(diffuseCoeff) * diffuse;

	fragment = vec4(fragColor.xyz, outOpacity);
}